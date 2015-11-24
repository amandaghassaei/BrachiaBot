/**
 * Created by aghassaei on 9/17/15.
 */

function three(animationLoopCallback){

    var $el = $("#threeContainer");

    var camera = new THREE.PerspectiveCamera(60, window.innerWidth/window.innerHeight, 0.01, 5000);
    var scene = new THREE.Scene();
    var renderer = new THREE.WebGLRenderer({antialias:true});//antialiasing is not supported in ff and on mac+chrome

    var animationLoopRunning = false;
    var stopAnimationFlag = false;

    var controls;

    var initialCameraPosition = new THREE.Vector3(0, -1000, -0);

    var threeView = null;

    initialize();

    function initialize(){

        resetCameraPosition();
        camera.up.set(0,0,1);//set z axis as "up"

        var fogColor = 0xcccccc;
//        scene.fog = new THREE.FogExp2(fogColor, 0.001);

        // lights
        var color = 0x888888;
        var light = new THREE.DirectionalLight(color);
        light.position.set(0, 10, 0);
        scene.add(light);
        var light = new THREE.DirectionalLight(color);
        light.position.set(0, -10, 0);
        scene.add(light);
        var light = new THREE.DirectionalLight(color);
        light.position.set(0, 0, 300);
        scene.add(light);
        var light = new THREE.DirectionalLight(0xaaaaaa);
        light.position.set(-1, -1, -1);
        scene.add(light);
        var light = new THREE.DirectionalLight(0xaaaaaa);
        light.position.set(1, 1, -1);
        scene.add(light);
        var light = new THREE.AmbientLight(0x222222);
        scene.add(light);


        // renderer
        renderer.setClearColor(fogColor, 1);
        renderer.setSize(window.innerWidth, window.innerHeight);

        window.addEventListener('resize', onWindowResize, false);

        $el.append(renderer.domElement);

        controls = new THREE.OrbitControls(camera, $el.get(0));
        controls.minDistance = 5;
	    controls.maxDistance = 1000;
//        controls.noPan = true;

        startAnimationLoop();
    }

    function resetCameraPosition(){
        camera.position.x = initialCameraPosition.x;
        camera.position.y = initialCameraPosition.y;
        camera.position.z = initialCameraPosition.z;
    }

    function onWindowResize(){
        camera.aspect = window.innerWidth/window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
    }

    function setThreeView(view){
        threeView = view;
    }

    function sceneAdd(object){
        scene.add(object);
    }

    function sceneRemove(object){
        scene.remove(object);
    }

    function startAnimationLoop(){
        if (animationLoopRunning) return;
        stopAnimationFlag = false;
        animationLoopRunning = true;
        console.log("animation started");
        _loop();
    }

    function stopAnimationLoop(){
        if (!animationLoopRunning) return;
        stopAnimationFlag = true;
    }

    function _loop(){
        animationLoopCallback();
        _render();
        if (stopAnimationFlag) {
            animationLoopRunning = false;
            console.log("animation stopped");
            return;
        }
        requestAnimationFrame(_loop);
    }

    function _render(){
        renderer.render(scene, camera);
    }

    return {//return public properties/methods
        startAnimationLoop: startAnimationLoop,
        stopAnimationLoop: stopAnimationLoop,
        sceneRemove: sceneRemove,
        sceneAdd: sceneAdd,
        camera: camera,
        resetCameraPosition: resetCameraPosition,
        setThreeView: setThreeView
    }
}

