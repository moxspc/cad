
#include "helper.h"
#include "point.h"
#include <iostream>

Nan::Persistent<v8::Function> mox::Point::constructor;

mox::Point::Point(double x, double y, double z) : m_point(x,y,z)
{
}

mox::Point::~Point()
{
}

void mox::Point::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Point", tpl);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "x", GetX);
  Nan::SetPrototypeMethod(tpl, "y", GetY);
  Nan::SetPrototypeMethod(tpl, "z", GetZ);
  Nan::SetPrototypeMethod(tpl, "set", SetXYZ);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Point").ToLocalChecked(), tpl->GetFunction());
}

void mox::Point::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
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
  Point* obj = new Point(x,y,z);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void mox::Point::GetX(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Point* obj = ObjectWrap::Unwrap<Point>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->m_point.X()));
}

void mox::Point::GetY(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Point* obj = ObjectWrap::Unwrap<Point>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->m_point.Y()));
}

void mox::Point::GetZ(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Point* obj = ObjectWrap::Unwrap<Point>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->m_point.Z()));
}

void mox::Point::SetXYZ(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Point* obj = ObjectWrap::Unwrap<Point>(info.Holder());
  if(info.Length() != 3) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }
  obj->m_point.SetX(info[0]->NumberValue());
  obj->m_point.SetY(info[1]->NumberValue());
  obj->m_point.SetZ(info[2]->NumberValue());
  info.GetReturnValue().Set(info.This());
}
