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