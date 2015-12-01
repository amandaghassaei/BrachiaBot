/**
 * Created by aghassaei on 1/26/15.
 */


function MenuWrapper(innerMenu){

    var MenuWrapperView = Backbone.View.extend({

        el: "#menuWrapper",

        events: {
            "click .dropdownSelector":                     "_makeDropdownSelection",
            "focusout .floatInput":                        "_softRenderTab",//force rounding if needed
            "focusout .intInput":                          "_softRenderTab",
            "change input:checkbox":                       "_clickCheckbox",
            "click input:radio":                           "_radioSelection"
        },

        initialize: function(){

            _.bindAll(this, "_onKeyUp");
            $(document).bind('keyup', {}, this._onKeyUp);

            this.menu = innerMenu;
        },

        _onKeyUp: function(e){

            if (!$("input").is(":focus")&& !$("textarea").is(':focus')){

//                console.log(e.keyCode);
                switch(e.keyCode){
                case 8://delete key - causes back nav in chrome, super annoying
                    e.preventDefault();
                    e.stopPropagation();
                    break;
                case 77://m key - hide menu
                    e.preventDefault();
                    this._toggleVisibility();
                    break;
                default:
                    break;
                }
            }

            if ($(".unresponsiveInput").is(":focus")) return;
            if ($("input").is(":focus") && e.keyCode == 13) {//enter key
                $(e.target).blur();
                this._softRenderTab();
                return;
            }

            if ($(".floatInput").is(":focus")) this._updateFloat(e);
            else if ($(".intInput").is(":focus")) this._updateInt(e);
            else if ($(".textInput").is(":focus")) this._updateString(e);
            else if ($(".hexInput").is(":focus")) this._updateHex(e);

        },

         _softRenderTab: function(){
            if (this.menu) this.menu.render();
            else console.warn("no menu found");
        },

        _updateString: function(e){
            e.preventDefault();
            var $target = $(e.target);
            var property = $target.data("property");
            if (!property) {
                console.warn("no property associated with string input");
                return;
            }
            this._setProperty($target, property, $target.val());
        },

        _updateHex: function(e){
            e.preventDefault();
            var $target = $(e.target);
            var hex = $target.val();
            if (!this._isValidHex(hex)) return;
            var property = $target.data("property");
            if (!property) {
                console.warn("no property associated with string input");
                return;
            }
            this._setProperty($target, property, hex);
            if (this.menu.updateHex) this.menu.updateHex(hex, $target);//no render when input in focus, this forces update of the inputs color
        },

        _isValidHex: function(hex){
            return hex.match(/(^#[0-9A-F]{6}$)|(^#[0-9A-F]{3}$)/i) !== null;
        },

        _updateFloat: function(e){
            e.preventDefault();
            var $target = $(e.target);
            var newVal = parseFloat($target.val());
            if (isNaN(newVal)) {
                if (newVal == "") return;
                console.warn("value is not float");
                return;
            }
            newVal = parseFloat(newVal.toFixed(parseInt(4)));
            this._setNumber($target, newVal);
        },

        _updateInt: function(e){
            e.preventDefault();
            var $target = $(e.target);
            var val = $target.val();
            if (val == "") return;
            var newVal = parseInt(val);
            if (isNaN(newVal)) {
                console.warn("value is NaN");
                return;
            }
            this._setNumber($target, newVal);
        },

        _setNumber: function($target, newVal){
            var min = $target.data("min");
            var max = $target.data("max");
            if (min !== undefined && (min > newVal)) newVal = min;
            else if (max !== undefined && (max < newVal)) newVal = max;

            var property = $target.data("property");
            if (!property) {
                console.warn("no property associated with number input");
                return;
            }
            var key = $target.data("key");

            //some numbers are relative
            var owner = this._getPropertyOwner($target);//todo not great here
            if (property == "stockPosition" && owner.get(property + "Relative")){
                if (key) newVal = parseFloat((newVal + owner.get("originPosition")[key]).toFixed(4));
                else console.warn("no key found for " + property);
            } else if (property == "rapidHeight" && !owner.get(property + "Relative")){
                newVal = parseFloat((newVal - owner.get("originPosition")["z"]).toFixed(4));
            }

            //remove trailing zeros
            newVal = newVal.toString();
            newVal = parseFloat(newVal);
            this._setProperty($target, property, newVal, key);
        },

        _makeDropdownSelection: function(e){
            var $target = $(e.target);
            var property = $target.data("property");
            var value = $target.data("value");
            if (!property || !value) return;
            this._setProperty($target, property, value);
        },

        _clickCheckbox: function(e){
            e.preventDefault();
            var $target = $(e.target);
            $target.blur();
            var property = $target.data("property");
            if (!property) {
                console.warn("no property associated with checkbox input");
                return;
            }
            this._toggleProperty($target, property);
        },

        _radioSelection: function(e){
            e.preventDefault();
            var $target = $(e.target);
            var property = $target.attr("name");
            var newVal = $target.val();
            this._setProperty($target, property, newVal);
            $target.blur();
        },


        _getPropertyOwner: function($target){
            if (this.menu) {
                var owner = this.menu.getPropertyOwner($target);
                if (owner) return owner;
            }
            else console.warn("no menu found for ui change");
            console.warn("no owner found for target");
            console.warn($target);
            return null;
        },

        _toggleProperty: function($target, property){ //val = !val
            var owner = this._getPropertyOwner($target);
            if (owner) this._setOwnerProperty(owner, property, !(this._getOwnerProperty(owner, property)));
        },

        _setProperty: function($target, property, newVal, key){
            var owner = this._getPropertyOwner($target);
            if (!owner) return;
            if (owner.setProperty){
                owner.setProperty(property, newVal, key);
                return;
            }
            if (key){
                var propObject = this._getOwnerProperty(owner, property);
                if (propObject.clone) propObject = propObject.clone();
                else propObject = _.clone(propObject);
                propObject[key] = newVal;
                this._setOwnerProperty(owner, property, propObject);
            } else {
                this._setOwnerProperty(owner, property, newVal);
            }
        },

        _getOwnerProperty: function(owner, property){
            if (owner instanceof Backbone.Model) return owner.get(property);
            return owner[property];
        },

        _setOwnerProperty: function(owner, property, value){
            if (owner instanceof Backbone.Model) owner.set(property, value);
            else {
                owner[property] = value;
                this.menu.render();
            }
        },

        _toggleVisibility: function(){
            if ($("#controls").css("right") == "-430px") this._show();
            else this._hide();
        },

        _hide: function(){
            $("#controls").animate({right: "-430"});
        },

        _show: function(){
            $("#controls").animate({right: "0"});
        }

    });

    return new MenuWrapperView();
}