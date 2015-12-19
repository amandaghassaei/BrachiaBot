/**
 * Created by aghassaei on 9/17/15.
 */

function three(animationLoopCallback){

    var $el = $("#threeContainer");

    var camera = new THREE.PerspectiveCamera(60, window.innerWidth/window.innerHeight, 0.1, 5000);
    var scene = new THREE.Scene();
    var renderer = new THREE.WebGLRenderer({antialias:true});//antialiasing is not supported in ff and on mac+chrome
//    renderer.shadowMapType = THREE.PCFSoftShadowMap;

    var depthMaterial, depthTarget, composer;
    var effectSSAO, effectFXAA;

    var animationLoopRunning = false;
    var stopAnimationFlag = false;

    var controls;

    var initialCameraPosition = new THREE.Vector3(0, -1000, -0);

    var threeView = null;

    var dpr = 1;
    if (window.devicePixelRatio !== undefined) {
      dpr = window.devicePixelRatio;
    }

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
        renderer.setSize(window.innerWidth*dpr, window.innerHeight*dpr);

        window.addEventListener('resize', onWindowResize, false);

        $el.append(renderer.domElement);

        controls = new THREE.OrbitControls(camera, $el.get(0));
        controls.minDistance = 10;
	    controls.maxDistance = 1000;
//        controls.noPan = true;


        // depth

        var depthShader = THREE.ShaderLib[ "depthRGBA" ];
        var depthUniforms = THREE.UniformsUtils.clone( depthShader.uniforms );

        depthMaterial = new THREE.ShaderMaterial( { fragmentShader: depthShader.fragmentShader, vertexShader: depthShader.vertexShader, uniforms: depthUniforms } );
        depthMaterial.blending = THREE.NoBlending;

        // postprocessing
        var parameters = { minFilter: THREE.LinearFilter, magFilter: THREE.LinearFilter,
                   format: THREE.RGBFormat, stencilBuffer: false };
        var renderTarget = new THREE.WebGLRenderTarget( window.innerWidth*dpr, window.innerHeight*dpr, parameters );
        composer = new THREE.EffectComposer(renderer);
        composer.addPass( new THREE.RenderPass( scene, camera ) );

        depthTarget = new THREE.WebGLRenderTarget( window.innerWidth*dpr, window.innerHeight*dpr, { minFilter: THREE.NearestFilter, magFilter: THREE.NearestFilter, format: THREE.RGBAFormat } )

        effectSSAO = new THREE.ShaderPass( THREE.SSAOShader );
        effectSSAO.uniforms[ 'tDepth' ].value = depthTarget;
        effectSSAO.uniforms[ 'size' ].value.set( window.innerWidth*dpr, window.innerHeight*dpr );
        effectSSAO.uniforms[ 'cameraNear' ].value = camera.near;
        effectSSAO.uniforms[ 'cameraFar' ].value = camera.far;
//        effectSSAO.renderToScreen = true;
        composer.addPass( effectSSAO );

        effectFXAA = new THREE.ShaderPass(THREE.FXAAShader);
        effectFXAA.uniforms['resolution'].value.set(1 /(window.innerWidth*dpr), 1 /(window.innerHeight*dpr));
        effectFXAA.renderToScreen = true;
        composer.addPass( effectFXAA );

//        var effectCopy = new THREE.ShaderPass(THREE.CopyShader);
//        effectCopy.renderToScreen = true;
//        composer.addPass( effectCopy );

        startAnimationLoop();
    }

    function resetCameraPosition(){
        camera.position.x = initialCameraPosition.x;
        camera.position.y = initialCameraPosition.y;
        camera.position.z = initialCameraPosition.z;
    }

    function onWindowResize(){
        camera.aspect = window.innerWidth*dpr/window.innerHeight*dpr;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth*dpr, window.innerHeight*dpr);
        effectSSAO.uniforms[ 'size' ].value.set( window.innerWidth*dpr, window.innerHeight*dpr );
        effectFXAA.uniforms['resolution'].value.set(1 / (window.innerWidth * dpr), 1 / (window.innerHeight * dpr));
        composer.setSize(window.innerWidth*dpr, window.innerHeight*dpr);
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
        scene.overrideMaterial = depthMaterial;
        renderer.render( scene, camera, depthTarget );
        scene.overrideMaterial = null;
        composer.render();
//        renderer.render(scene, camera);
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

