
var assert = require('assert');
var mox = require('../build/Debug/mox');

describe('Point', function() {
  it('Empty Constructor', function () {
    var point = new mox.geom.Point();
    assert.equal(point.x(), 0);
    assert.equal(point.y(), 0);
    assert.equal(point.z(), 0);
  });
  it('Constructor', function () {
    var point = new mox.geom.Point(22.3,4.509,90);
    assert.equal(point.x(), 22.3);
    assert.equal(point.y(), 4.509);
    assert.equal(point.z(), 90);
  });
  it('Set', function () {
    var point = new mox.geom.Point();
    point.set(9,3,5);
    assert.equal(point.x(), 9);
    assert.equal(point.y(), 3);
    assert.equal(point.z(), 5);
  });
});
