/**
 * Created by aghassaei on 11/24/15.
 */

function initGraphs(){

    var smoothie = new SmoothieChart({labels:{disabled:false}});
    var canvas = document.getElementById("graphsCanvas");
    smoothie.streamTo(canvas);


    // Data
    var line1 = new TimeSeries();
    var line2 = new TimeSeries();

    // Add a random value to each line every second
    setInterval(function() {
      line1.append(new Date().getTime(), Math.random());
      line2.append(new Date().getTime(), Math.random());
    }, 1000);

    // Add to SmoothieChart
    smoothie.addTimeSeries(line1,
        { strokeStyle:'rgb(0, 255, 0)', lineWidth:3 });
    smoothie.addTimeSeries(line2,
        { strokeStyle:'rgb(255, 0, 255)', lineWidth:3 });

}