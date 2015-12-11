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
            swingUpK: null,
            swingUpD: null,
            desiredThetaP: null,
            softLimitsP: null,
            targetingK: null,
            targetingD: null
        },

        setData: function(data){
            var self = this;
            _.each(this.attributes, function(attribute, key){
                var val = data[key];
                if (val !== null && val !== undefined) self.set(key, val);
            });
        },

        refresh: function(){
            this.set(this.defaults);
        }


    });

    return new MachineState();

});