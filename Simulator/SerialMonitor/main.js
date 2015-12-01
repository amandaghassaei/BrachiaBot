/**
 * Created by aghassaei on 9/9/15.
 */


require.config({

    paths: {
        jquery: '../dependencies/jquery-2.1.3.min',
        underscore: '../dependencies/underscore-min',
        backbone: '../dependencies/backbone-min',
        text: '../dependencies/text',
        three: '../dependencies/three',
        socketio: '../dependencies/socket.io-1.3.5',

        serialMonitor: 'SerialMonitor',
        serialMonitorView: 'SerialMonitorView',
        positionControlPanelView: 'PositionControlPanelView',

        menuParent: '../menus/MenuParentView',
        commParentMenu: '../menus/CommParentMenu',
        plist: '../plists/PList',
        commPlist: '../plists/commPlist',
        serialComm: 'SerialComm',
        machineState: '../models/MachineState',
        cam: 'fakeCam'

    },

    shim: {
        three: {
            exports: 'THREE'
        },
        'socketio': {
            exports: 'io'
        }
    }

});

require(['serialMonitorView', 'serialMonitor'],
    function(SerialMonitorView, serialMonitor){

    new SerialMonitorView({model: serialMonitor});
});