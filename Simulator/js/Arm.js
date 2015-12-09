/**
 * Created by aghassaei on 11/24/15.
 */


var armMaterial = new THREE.MeshLambertMaterial({color:"#999999"});

function Arm(three){

    this.object3D = new THREE.Object3D;
//    this.object3D.add(this.buildMesh());

    three.sceneAdd(this.object3D);
}

Arm.prototype.setPosition = function(position){
    this.object3D.position.set(position.x, position.y, position.z);
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