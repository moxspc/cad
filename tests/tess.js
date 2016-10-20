
var assert = require('assert');
var moxcad = require('../build/Debug/moxcad');

describe('Tess', function() {
  it('tessellate', function () {
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

    var bufferMesh = solid.tessellate();
    assert(!!bufferMesh);
    assert(bufferMesh.faceBuffers.length, 6);
    assert(bufferMesh.edgeBuffers.length, 12);
  });
});
