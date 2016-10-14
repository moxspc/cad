

var assert = require('assert');
var moxcad = require('../build/Debug/moxcad');

describe('Fitter', function() {
  it('approximate2d', function () {
    var answer = moxcad.ops.approximate2d([0,0],[20,30],[127,124],[210,150],[211,151],[25,170],[120,180],[200,200]);
    console.log(answer);
  });

  it('interpolate2d', function () {
    var answer = moxcad.ops.interpolate2d(
      [ [0,0], [100,150], [150,50], [200, 400], [250,-200] ],
      true);
    console.log(answer);
  });
});
