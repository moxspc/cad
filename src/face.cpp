
#include "helper.h"
#include "face.h"
#include "wire.h"

Nan::Persistent<v8::Function> mox::Face::constructor;

mox::Face::Face()
{
}

mox::Face::Face(TopoDS_Face occFace) : m_face(occFace)
{
}

mox::Face::~Face()
{
}

void mox::Face::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Face").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "toString", toString);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Face").ToLocalChecked(), tpl->GetFunction());
}

v8::Local<v8::Object> mox::Face::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}

NAN_METHOD(mox::Face::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  //mox::Wire *wire = Nan::ObjectWrap::Unwrap<mox::Wire>(info[0]->ToObject());
  //Face *obj = new Face(wire->toOCC());
  Face *obj = new Face();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Face::toString)
{
  info.GetReturnValue().Set(Nan::New("F").ToLocalChecked());
}
