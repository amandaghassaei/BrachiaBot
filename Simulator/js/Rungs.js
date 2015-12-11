/**
 * Created by aghassaei on 11/24/15.
 */


function Rungs(three){

    var rungSpacing = 350;
    var rungRadius = 11;

    var rungsMaterial = new THREE.MeshLambertMaterial({color:"#ff0000"});
    for (var i=-1;i<2;i++){
        for (var j=-1;j<2;j++){
            var mesh = this.buildMesh(rungsMaterial);
            mesh.scale.set(rungRadius, 1, rungRadius);
            mesh.position.set(i*rungSpacing, 0, j*rungSpacing);
            three.sceneAdd(mesh);
        }
    }

}

Rungs.prototype.buildMesh = function(material){
    return new THREE.Mesh(new THREE.CylinderGeometry(1, 1, 50, 30), material);
};