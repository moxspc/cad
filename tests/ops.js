var assert = require('assert');
var moxcad = require('../build/Debug/moxcad');

describe('Ops', function() {
  it('Extrude a Square', function () {
    var point1 = new moxcad.geom.Point(0,0,0);
    var point2 = new moxcad.geom.Point(1,0,0);
    var point3 = new moxcad.geom.Point(1,1,0);
    var point4 = new moxcad.geom.Point(0,1,0);
    var lineseg1 = new moxcad.geom.LineSegment(point1, point2);
    var lineseg2 = new moxcad.geom.LineSegment(point2, point3);
    var lineseg3 = new moxcad.geom.LineSegment(point3, point4);
    var lineseg4 = new moxcad.geom.LineSegment(point4, point1);
    var edge1 = lineseg1.makeEdge();
    var edge2 = lineseg2.makeEdge();
    var edge3 = lineseg3.makeEdge();
    var edge4 = lineseg4.makeEdge();
    var wire = new moxcad.topo.Wire(edge1, edge2, edge3, edge4);
    var face = wire.makeFace();
    var dir = new moxcad.geom.Vector(0,0,1);
    var solid = moxcad.ops.extrude(face, dir);
    assert(!!solid);
    assert.equal(solid.numFaces(), 6);
    assert.equal(solid.numEdges(), 12);
    assert.equal(solid.numVertices(), 8);
    assert.equal(solid.numShells(), 1); // ?

    solid.eachVertex(function (vtx) {
      console.log(vtx.toString());
    });

    solid.eachFace(function (face) {
      console.log(face.toString());
    });

    solid.eachEdge(function (edge) {
      console.log(edge.toString());
    });
  });

  it('Extrude a Pentagon', function () {
    var point1 = new moxcad.geom.Point(0,0,0);
    var point2 = new moxcad.geom.Point(1,0,0);
    var point3 = new moxcad.geom.Point(1,1,0);
    var point4 = new moxcad.geom.Point(0,1,0);
    var point5 = new moxcad.geom.Point(-1,0.5,0);
    var lineseg1 = new moxcad.geom.LineSegment(point1, point2);
    var lineseg2 = new moxcad.geom.LineSegment(point2, point3);
    var lineseg3 = new moxcad.geom.LineSegment(point3, point4);
    var lineseg4 = new moxcad.geom.LineSegment(point4, point5);
    var lineseg5 = new moxcad.geom.LineSegment(point5, point1);
    var edge1 = lineseg1.makeEdge();
    var edge2 = lineseg2.makeEdge();
    var edge3 = lineseg3.makeEdge();
    var edge4 = lineseg4.makeEdge();
    var edge5 = lineseg5.makeEdge();
    var wire = new moxcad.topo.Wire(edge1, edge2, edge3, edge4, edge5);
    var face = wire.makeFace();
    var dir = new moxcad.geom.Vector(0,0,1);
    var solid = moxcad.ops.extrude(face, dir);
    assert(!!solid);
    assert.equal(solid.numFaces(), 7);
    assert.equal(solid.numEdges(), 15);
    assert.equal(solid.numVertices(), 10);
    assert.equal(solid.numShells(), 1); // ?

    solid.eachVertex(function (vtx) {
      console.log(vtx.toString());
    });

    solid.eachFace(function (face) {
      console.log(face.toString());
    });

    solid.eachEdge(function (edge) {
      console.log(edge.toString());
    });

  });
});
