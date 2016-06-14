
#include "vertex.h"

Nan::Persistent<v8::Function> mox::Vertex::constructor;

mox::Vertex::Vertex(const TopoDS_Vertex occVertex) : m_vertex(occVertex)
{
}

mox::Vertex::~Vertex()
{
}

void mox::Vertex::setOCCVertex(TopoDS_Vertex occVertex)
{
  m_vertex = occVertex;
}

void mox::Vertex::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Vertex").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Vertex").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Vertex::New)
{
  if(info.IsConstructCall()) {
    Vertex *obj = new Vertex();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 0;
    v8::Local<v8::Value> argv[] = {};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc,argv));
  }
}

v8::Local<v8::Object> mox::Vertex::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);

}
