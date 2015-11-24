/**
 * Created by aghassaei on 9/17/15.
 */


$( document ).ready(function() {

    var threeModel = three(function(){
        //animation loop
        if (!arm1 || !arm2) return;

        arm1.setTheta(arm1.getTheta() + 0.001);
        arm2.setPosition(arm1.getPosition());
        arm2.setTheta(arm2.getTheta() - 0.001);

    });

    var arm1 = new Arm1(threeModel);
    var arm2 = new Arm1(threeModel);

});