/**
 * Created by aghassaei on 6/2/15.
 */


function MenuParentView(){

    return Backbone.View.extend({

        el: "#controls",

        initialize: function(){

            _.bindAll(this, "render");

            if (this._initialize) this._initialize();//call subclass
            this.render();
        },

        getPropertyOwner: function($target){
            return null;//override in subclasses
        },

        render: function(){
            if ($("input[type=text]").is(":focus")) return;
            if (this._preRender) this._preRender();
            this.$el.html(this.template(this._makeTemplateJSON()));
            if (this._render) this._render();
        },

        destroy: function(){
            if (this._destroy) this._destroy();
            this.stopListening();
            this.undelegateEvents();
            this.$el.removeData().unbind();
//            this.remove();//todo not convinced I have this right yet
//            Backbone.View.prototype.remove.call(this);
        }

    });
}