
#include "mox.h"

#include "point.h"
#include "lineseg.h"

#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "wire.h"

#include <gp.hxx>
#include "gp_XYZ.hxx"

void mox::doOCCMath(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  gp_XYZ xyz(3,4,1);
  v8::Local<v8::Number> answer = v8::Number::New(isolate, xyz.Modulus());
  args.GetReturnValue().Set(answer);
}

void mox::doSomething(const FunctionCallbackInfo<Value>& args)
{
  v8::Local<v8::Object> vtxObject = mox::Vertex::NewInstance();
  mox::Vertex* vtx = Nan::ObjectWrap::Unwrap<mox::Vertex>(vtxObject);
}

void mox::init(Local<Object> exports)
{
  v8::Isolate *isolate = v8::Isolate::GetCurrent();

  v8::Handle<Object> geom = v8::Object::New(isolate);
  mox::Point::Init(geom);
  mox::LineSegment::Init(geom);

  v8::Handle<Object> topo = v8::Object::New(isolate);
  mox::Vertex::Init(topo);
  mox::Edge::Init(topo);
  mox::Wire::Init(topo);

  exports->Set(Nan::New("geom").ToLocalChecked(), geom);
  exports->Set(Nan::New("topo").ToLocalChecked(), topo);

  NODE_SET_METHOD(exports, "doOCCMath", doOCCMath);
  NODE_SET_METHOD(exports, "doSomething", doSomething);
}

NODE_MODULE(mox, mox::init)


