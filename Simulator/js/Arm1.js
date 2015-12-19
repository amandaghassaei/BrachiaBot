/**
 * Created by aghassaei on 11/24/15.
 */


function Arm1(three){

    Arm.call(this, three);
}
Arm1.prototype = Object.create(Arm.prototype);

Arm1.prototype.getPosition = function(){
    return this.applyRotation(new THREE.Vector3(0,0,-275));
};


Arm1.prototype.setGeo = function(geo){
    geo.applyMatrix(new THREE.Matrix4().makeRotationX(Math.PI/2));
//    var geometry = new THREE.SphereGeometry(100);
    var geometry = new THREE.Geometry().fromBufferGeometry(geo);
    this.assignUVs(geometry);
    var mesh = new THREE.Mesh(geometry, this.getMaterial());
    mesh.position.set(0,0,-275);
    this.object3D.add(mesh);
};