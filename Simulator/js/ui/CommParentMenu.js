/**
 * Created by aghassaei on 8/28/15.
 */

function CommParentMenu(serialComm){

    var _MenuParentView = MenuParentView();

    return _MenuParentView.extend({

        parentEvents: {
            "change #sendSerialMessage":                        "_sendMessage"
        },


        _initialize: function(){

            _.extend(this.events, this.parentEvents);

            this.listenTo(serialComm, "change", this.render);
            this.listenTo(serialComm, "change:lastMessageReceived", this._updateIncomingMessage);

            this.inTimeout = false;
            if (this.__initialize) this.__initialize();
        },

        getPropertyOwner: function($target){
            if ($target.hasClass("serialComm")) return serialComm;
            return null;
        },

        _sendMessage: function(e){
            e.preventDefault();
            var message = $("#sendSerialMessage").val();
            $("#sendSerialMessage").val("");
            if (message == "") return;
            serialComm.send(message);
        },

        _updateIncomingMessage: function(){
            var message = serialComm.get("lastMessageReceived");
            var $message = $("#incomingSerialMessage");
            $message.html(message);
            $message.css("background", "#ffff99");
            $message.css('display', 'inline-block');
            if (!this.inTimeout) {
                this.inTimeout = true;
                var self = this;
                setTimeout(function(){
                    $message.css("background", "white");
                    self.inTimeout = false;
                }, 100);
            }
        }

    });
}