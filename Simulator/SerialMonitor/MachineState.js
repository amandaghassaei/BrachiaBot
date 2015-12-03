/**
 * Created by aghassaei on 9/11/15.
 */


define(['underscore', 'backbone'], function(_, Backbone){

    var MachineState = Backbone.Model.extend({

        defaults:{
            th1: null,
            dth1: null,
            th2: null,
            dth2: null,
            k1: null,
            d1: null,
            k2: null,
            d2: null
        },

        setData: function(data){
            var self = this;
            _.each(this.attributes, function(attribute, key){
                var val = data["pos" + key];
                if (val !== null && val !== undefined) self.set(key, val);
            });
        },

        refresh: function(){
            this.set(this.defaults);
        }


    });

    return new MachineState();

});