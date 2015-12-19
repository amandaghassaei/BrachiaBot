/**
 * Created by aghassaei on 11/24/15.
 */


function Arm2(three){

    Arm.call(this, three);
}
Arm2.prototype = Object.create(Arm.prototype);


Arm2.prototype.setGeo = function(geo){
    geo.applyMatrix(new THREE.Matrix4().makeRotationX(Math.PI/2));
    geo.applyMatrix(new THREE.Matrix4().makeRotationY(Math.PI));
    var geometry = new THREE.Geometry().fromBufferGeometry(geo);
    this.assignUVs(geometry);
    var mesh = new THREE.Mesh(geometry, this.getMaterial());
    this.object3D.add(mesh);
};