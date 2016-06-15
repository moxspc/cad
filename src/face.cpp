
#include "helper.h"
#include "face.h"
#include "wire.h"
#include <BRepBuilderAPI_MakeFace.hxx>

Nan::Persistent<v8::Function> mox::Face::constructor;

mox::Face::Face(const TopoDS_Wire& occWire)
{
  m_face = BRepBuilderAPI_MakeFace(occWire);
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

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Face").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Face::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  mox::Wire *wire = Nan::ObjectWrap::Unwrap<mox::Wire>(info[0]->ToObject());
  Face *obj = new Face(wire->toOCC());
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}
