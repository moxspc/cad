var assert = require('assert');
var mox = require('../build/Debug/mox');

describe('Wire', function() {
  it('Constructor', function () {
    var point1 = new mox.geom.Point(0,0,0);
    var point2 = new mox.geom.Point(1,0,0);
    var point3 = new mox.geom.Point(1,1,0);
    var lineseg1 = new mox.geom.LineSegment(point1, point2);
    var lineseg2 = new mox.geom.LineSegment(point2, point3);
    var edge1 = new mox.topo.Edge(lineseg1);
    var edge2 = new mox.topo.Edge(lineseg2);
    var wire = new mox.topo.Wire(edge1, edge2);
    assert(!!wire);
  });
});
