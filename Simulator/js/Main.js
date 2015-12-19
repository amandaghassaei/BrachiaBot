/**
 * Created by aghassaei on 9/17/15.
 */


$( document ).ready(function() {

    var graphData = initGraphs();

    var threeModel = three(function(){
        //animation loop
        if (!arm1 || !arm2) return;

        arm1.setTheta(arm1.getTheta() + 0.001);
        arm2.setPosition(arm1.getPosition());
        arm2.setTheta(arm2.getTheta() - 0.001);

    });

    var loader = new THREE.STLLoader();
    var arm1 = new Arm1(threeModel);
    var arm2 = new Arm2(threeModel);
    loader.load( 'Simulator/assets/stls/arm1.stl', function ( geometry ) {
        arm1.setGeo(geometry);
    } );
    loader.load( 'Simulator/assets/stls/arm2.stl', function ( geometry ) {
        arm2.setGeo(geometry);
    } );


    new Rungs(threeModel);

    var serialComm = SerialComm(arm1, arm2, graphData);

    var templateURL = 'Simulator/js/ui/SetupCommMenuView.html';

    $.ajax({
        url: templateURL,
        method: 'GET',
        success: function(template) {
            var CommMenu = SetupCommMenuView(serialComm, template);
            var menu = new CommMenu();
            MenuWrapper(menu);
        }
    });



});