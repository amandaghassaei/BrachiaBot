/**
 * Created by aghassaei on 11/24/15.
 */

function initGraphs(){

    $(document).bind('keyup', {}, _onKeyUp);

    function _onKeyUp(e){

        if (!$("input").is(":focus")&& !$("textarea").is(':focus')){

//            console.log(e.keyCode);
            switch(e.keyCode){
                case 71://g key - hide graphs
                    e.preventDefault();
                    _toggleVisibility();
                    break;
                default:
                    break;
            }
        }
    }

    function _toggleVisibility(){
        if ($("#graphs").css("left") == "0px") _hide();
        else _show();
    }

    function _hide(){
        $("#graphs").animate({left: "-430"});
    }

    function _show(){
        $("#graphs").animate({left: "0"});
    }

    var theta1Graph = new SmoothieChart({labels:{disabled:false}});
    theta1Graph.streamTo(document.getElementById("theta1"));

    var dtheta1Graph = new SmoothieChart({labels:{disabled:false}});
    dtheta1Graph.streamTo(document.getElementById("dtheta1"));

    var theta2Graph = new SmoothieChart({labels:{disabled:false}});
    theta2Graph.streamTo(document.getElementById("theta2"));

    var dtheta2Graph = new SmoothieChart({labels:{disabled:false}});
    dtheta2Graph.streamTo(document.getElementById("dtheta2"));


    // Data
    var theta1 = new TimeSeries();
    var dtheta1 = new TimeSeries();
    var theta2 = new TimeSeries();
    var dtheta2 = new TimeSeries();

    // Add to SmoothieChart
    theta1Graph.addTimeSeries(theta1,
        { strokeStyle:'rgb(0, 255, 0)', lineWidth:3 });
    dtheta1Graph.addTimeSeries(dtheta1,
        { strokeStyle:'rgb(255, 0, 255)', lineWidth:3 });

    theta2Graph.addTimeSeries(theta2,
        { strokeStyle:'rgb(0, 255, 0)', lineWidth:3 });
    dtheta2Graph.addTimeSeries(dtheta2,
        { strokeStyle:'rgb(255, 0, 255)', lineWidth:3 });

    return {th1:theta1, dth1: dtheta1, th2: theta2, dth2: dtheta2};

}