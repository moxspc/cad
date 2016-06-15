
#include "helper.h"
#include "solid.h"
#include <TopExp_Explorer.hxx>

Nan::Persistent<v8::Function> mox::Solid::constructor;

mox::Solid::Solid()
{
}

mox::Solid::~Solid()
{
}

void mox::Solid::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Solid").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "numFaces", numFaces);
  Nan::SetPrototypeMethod(tpl, "numEdges", numEdges);
  Nan::SetPrototypeMethod(tpl, "numVertices", numVertices);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Solid").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Solid::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  Solid *obj = new Solid();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Solid::numFaces)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_FACE);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(mox::Solid::numEdges)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_EDGE);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(mox::Solid::numVertices)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_VERTEX);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

v8::Local<v8::Object> mox::Solid::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}
