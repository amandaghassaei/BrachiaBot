/**
 * Created by aghassaei on 11/24/15.
 */


function Arm1(three){

    Arm.call(this, three);
}
Arm1.prototype = Object.create(Arm.prototype);

Arm1.prototype.buildMesh = function(){
    var mesh = new THREE.Mesh(new THREE.BoxGeometry(40, 40, 200), armMaterial);
    mesh.position.set(0,0,-100);
    return mesh;
};

Arm1.prototype.getPosition = function(){
    return this.applyRotation(new THREE.Vector3(0,0,-200));
};