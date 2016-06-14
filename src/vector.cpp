
#include "helper.h"
#include "vector.h"

Nan::Persistent<v8::Function> mox::Vector::constructor;

mox::Vector::Vector(double x, double y, double z) : m_vector(x,y,z)
{
}

mox::Vector::~Vector()
{
}

void mox::Vector::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Vector").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Vector").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Vector::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  double x=0,y=0,z=0;
  if(info.Length() == 1) {
    x = info[0]->NumberValue();
  } else if(info.Length() == 2) {
    x = info[0]->NumberValue();
    y = info[1]->NumberValue();
  } else if(info.Length() >= 3) {
    x = info[0]->NumberValue();
    y = info[1]->NumberValue();
    z = info[2]->NumberValue();
  }
  Vector *obj = new Vector(x,y,z);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}
