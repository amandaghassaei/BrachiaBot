/**
 * Created by aghassaei on 11/24/15.
 */


define(['underscore', 'backbone', 'socketio', 'machineState'],
    function(_, Backbone, io, machineState){

    var SerialComm = Backbone.Model.extend({

        defaults: {
            connected: false,
            portConnected: false,
            availablePorts: [],
            portName: "Select Port",
            baudRate: 200,
            error: null,
            lastMessageReceived: null,
            lastMessageSent: "",
            isStreaming: false,
            singleStepMode: true
        },

        initialize: function(){
            this.machineState = machineState;
    //        this.listenTo(machineState, "change", this._updateVirtualMachine);
            this.attemptToConnectToNode();
        },

        attemptToConnectToNode: function(){
            if (!this.get("connected")) {
                this.socket = io.connect('http://localhost:8080', {'forceNew':true});
                addEventHandlers(this.socket);//if we're not in the serial monitor window
            }
        },

        connectionFailed: function(){
            this.set("connected", false);
            this.socket.disconnect();
            this.socket = null;
        },

        refreshPorts: function(){
            this.socket.emit('refreshPorts');
        },

        send: function(data){
            this.socket.emit("dataOut", data);
        },

        flushBuffer: function(){
            this.socket.emit("flush");
        },

        startStream: function(){
            this.socket.emit("startStream");
        },

        pauseStream: function(){
            this.socket.emit("pauseStream");
        },

        stopStream: function(){
            this.socket.emit("stopStream");
        },

        _updateVirtualMachine: function(){
        },

        refreshMachineState: function(){//when updating connection, create a new instance of machine state
            this.machineState.refresh();
        },

        getMachineState: function(){
            return this.machineState;
        },

        setProperty: function(property, value){//portName, baudRate
            if (property === null || property === undefined || value === null || value === undefined) return;
            this.socket.emit(property, value);//always pass user interaction on
        },

        openSerialMonitor: function(){
            if (!this.get("connected")) {
                console.warn("can't open serial monitor if not connected to node server");
                return;
            }
            var serialMonitorController = SerialMonitorController();
            serialMonitorController.open();
        }

    });

    var serialComm = new SerialComm();

    function addEventHandlers(socket){

        socket.on('connected', function(data){
            serialComm.set("connected", true, {silent:true});
            _.each(_.keys(data), function(key){
                if (data[key] !== null) serialComm.set(key, data[key]);
            });
        });

        socket.on('dataIn', function(data){
            if (data == "" || data == '\n' || data == "\r") return;
            serialComm.set("lastMessageReceived", data, {silent:true});

            try {
                var json = JSON.parse(data);
                if (json.th1 === undefined) serialComm.trigger("change:lastMessageReceived");
                machineState.setData(json);
            } catch(err) {
                serialComm.trigger("change:lastMessageReceived");
    //                console.warn(err);
            }
        });

        socket.on('dataSent', function(data){
            serialComm.set("lastMessageSent", data, {silent:true});
            serialComm.trigger("change:lastMessageSent");
        });

        socket.on('isStreaming', function(data){
            serialComm.set("isStreaming", data);
            if (data == true) serialComm.sendGCode();
        });

        socket.on('portConnected', function(data){
            console.log("connected port " + data.portName + " at " + data.baudRate);
            serialComm.set("baudRate", data.baudRate);
            serialComm.set("portName", data.portName);
            serialComm.set("portConnected", true);
            serialComm.set("error", false);
    //        serialComm.refreshMachineState();
        });

        socket.on('portDisconnected', function(data){
            console.log("disconnected port " + data.portName + " at " + data.baudRate);
            if (serialComm.get("baudRate") != data.baudRate) return;
            if (serialComm.get("portName") != data.portName) return;
            serialComm.set("portConnected", false);
        });

        socket.on("errorMsg", function(data){
            console.warn(data);
            serialComm.set("error", data.error);
        });

        socket.on("error", function(error){
            console.warn(error);
        });

        socket.on("connect_error", function(){
            serialComm.connectionFailed();
        });
    }

    return serialComm;
});
