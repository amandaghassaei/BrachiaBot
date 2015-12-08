/**
 * Created by aghassaei on 11/24/15.
 */


function Arm2(three){

    Arm.call(this, three);
}
Arm2.prototype = Object.create(Arm.prototype);

Arm2.prototype.buildMesh = function(){
    var mesh = new THREE.Mesh(new THREE.BoxGeometry(40, 40, 200), armMaterial);
    mesh.position.set(0,0,-100);
    return mesh;
};


Arm2.prototype.setGeo = function(geo){
    geo.applyMatrix(new THREE.Matrix4().makeRotationX(Math.PI/2));
    geo.applyMatrix(new THREE.Matrix4().makeRotationY(Math.PI));
//    geo.applyMatrix(new THREE.Matrix4().makeTranslation(0,0,-73));
    var mesh = new THREE.Mesh(geo, armMaterial);
//    mesh.position.set(0,0,-275);
    this.object3D.add(mesh);
};