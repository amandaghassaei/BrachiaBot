/**
 * Created by aghassaei on 11/24/15.
 */


//var armMaterial = new THREE.MeshLambertMaterial({color:"#999999"});
var urlPrefix = "Simulator/assets/cubeMap/";
var urls = [ urlPrefix + "posx.png", urlPrefix + "negx.png",
    urlPrefix + "posy.png", urlPrefix + "negy.png",
    urlPrefix + "posz.png", urlPrefix + "negz.png" ];
var textureCube = THREE.ImageUtils.loadTextureCube( urls );

var texture = THREE.ImageUtils.loadTexture('Simulator/assets/metalNormal.jpg');
texture.wrapS = texture.wrapT = THREE.RepeatWrapping;

var armMaterial = new THREE.MeshPhongMaterial({
    color:0xdddddd,
    envMap:textureCube,
    normalMap: texture,
    reflectivity: 0.9,
    normalScale: new THREE.Vector2(0.2, 0.2)
});



function Arm(three){

    this.object3D = new THREE.Object3D;
    three.sceneAdd(this.object3D);
}

Arm.prototype.setPosition = function(position){
    this.object3D.position.set(position.x, position.y, position.z);
};

Arm.prototype.getMaterial = function(){
    return armMaterial;
};

Arm.prototype.setTheta = function(theta){
    this.object3D.rotation.set(0, -theta, 0);
};

Arm.prototype.getTheta = function(){
    return -this.object3D.rotation.y;
};

Arm.prototype.getRotation = function(){
    return this.object3D.quaternion;
};

Arm.prototype.applyRotation = function(vector){
    vector.applyQuaternion(this.getRotation());
    return vector;
};

Arm.prototype.assignUVs = function( geometry ){

    geometry.computeBoundingBox();

    var max     = geometry.boundingBox.max;
    var min     = geometry.boundingBox.min;

    var offset  = new THREE.Vector2(0 - min.x, 0 - min.y);
    var range   = new THREE.Vector2(max.x - min.x, max.y - min.y);

    geometry.faceVertexUvs[0] = [];
    var faces = geometry.faces;

    for (i = 0; i < geometry.faces.length ; i++) {

      var v1 = geometry.vertices[faces[i].a];
      var v2 = geometry.vertices[faces[i].b];
      var v3 = geometry.vertices[faces[i].c];

      geometry.faceVertexUvs[0].push([
        new THREE.Vector2( ( v1.x + offset.x ) / range.x , ( v1.y + offset.y ) / range.y ),
        new THREE.Vector2( ( v2.x + offset.x ) / range.x , ( v2.y + offset.y ) / range.y ),
        new THREE.Vector2( ( v3.x + offset.x ) / range.x , ( v3.y + offset.y ) / range.y )
      ]);

    }

    geometry.uvsNeedUpdate = true;

}