
#include "mox.h"

#include "point.h"
#include "vector.h"
#include "lineseg.h"

#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "wire.h"
#include "ops.h"
#include "solid.h"
#include "buffermesh.h"

void moxcad::init(Local<Object> exports)
{
  v8::Handle<Object> geom = Nan::New<v8::Object>();
  moxcad::Point::Init(geom);
  moxcad::Vector::Init(geom);
  moxcad::LineSegment::Init(geom);

  v8::Handle<Object> topo = Nan::New<v8::Object>();
  moxcad::Vertex::Init(topo);
  moxcad::Edge::Init(topo);
  moxcad::Face::Init(topo);
  moxcad::Wire::Init(topo);
  moxcad::Solid::Init(topo);

  v8::Handle<Object> ops = Nan::New<v8::Object>();
  moxcad::ops::Init(ops);

  v8::Handle<Object> tess = Nan::New<v8::Object>();
  moxcad::BufferMesh::Init(tess);

  exports->Set(Nan::New("geom").ToLocalChecked(), geom);
  exports->Set(Nan::New("topo").ToLocalChecked(), topo);
  exports->Set(Nan::New("ops").ToLocalChecked(), ops);
  exports->Set(Nan::New("tess").ToLocalChecked(), tess);

}

NODE_MODULE(moxcad, moxcad::init)


