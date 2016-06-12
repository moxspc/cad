
var assert = require('assert');
var mox = require(process.env.HOME+'/moxspc/mox/build/Release/mox');

describe('Point', function() {
  it('Empty Constructor', function () {
    var point = new mox.Point();
    assert.equal(point.x(), 0);
    assert.equal(point.y(), 0);
    assert.equal(point.z(), 0);
  });
  it('Constructor', function () {
    var point = new mox.Point(22.3,4.509,90);
    assert.equal(point.x(), 22.3);
    assert.equal(point.y(), 4.509);
    assert.equal(point.z(), 90);
  });
  it('Empty Function', function () {
    var point = mox.Point();
    assert.equal(point.x(), 0);
    assert.equal(point.y(), 0);
    assert.equal(point.z(), 0);
  });
  it('Function', function () {
    var point = mox.Point(22.3,4.509,90);
    assert.equal(point.x(), 22.3);
    assert.equal(point.y(), 4.509);
    assert.equal(point.z(), 90);
  });
  it('Set', function () {
    var point = new mox.Point();
    point.set(9,3,5);
    assert.equal(point.x(), 9);
    assert.equal(point.y(), 3);
    assert.equal(point.z(), 5);
  });
});
