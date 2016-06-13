
#include "geom.h"
#include "point.h"

Nan::Persistent<v8::Function> mox::Geom::constructor;

mox::Geom::Geom()
{
}

mox::Geom::~Geom()
{
}

void mox::Geom::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("geom").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  mox::Point::Init(tpl);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("geom").ToLocalChecked(), tpl->GetFunction());
}

void mox::Geom::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    Nan::ThrowError("Instantiation of namespace is not defined");
    return;
  }
}
