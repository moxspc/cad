
#include "lineseg.h"
#include "point.h"

#include <GC_MakeSegment.hxx>

Nan::Persistent<v8::Function> mox::LineSegment::constructor;

mox::LineSegment::LineSegment(const gp_Pnt &from, const gp_Pnt &to)
{
  m_curveHandle = GC_MakeSegment(from, to);
}

mox::LineSegment::~LineSegment()
{
}

void mox::LineSegment::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("LineSegment").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  //Nan::SetPrototypeMethod(tpl, "set", SetXYZ);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("LineSegment").ToLocalChecked(), tpl->GetFunction());

}

void mox::LineSegment::New(const Nan::FunctionCallbackInfo<v8::Value> &info)
{
  if(info.Length() != 2) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }
  if(info.IsConstructCall()) {
    mox::Point *pntFrom = Nan::ObjectWrap::Unwrap<mox::Point>(info[0]->ToObject());
    mox::Point *pntTo = Nan::ObjectWrap::Unwrap<mox::Point>(info[1]->ToObject());
    LineSegment *obj = new LineSegment(pntFrom->toOCC(), pntTo->toOCC());
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 2;
    v8::Local<v8::Value> argv[2] = { info[0], info[1] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

