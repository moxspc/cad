
#include "edge.h"
#include "lineseg.h"
#include "BRepBuilderAPI_MakeEdge.hxx"

Nan::Persistent<v8::Function> mox::Edge::constructor;

mox::Edge::Edge(const TopoDS_Edge &occEdge) : m_edge(occEdge)
{
}

mox::Edge::~Edge()
{
}

void mox::Edge::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Edge").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Edge").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Edge::New)
{
  if(info.IsConstructCall()) {
    if(info.Length() >= 1) {
      mox::LineSegment *lineseg =
        Nan::ObjectWrap::Unwrap<mox::LineSegment>(info[0]->ToObject());
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(lineseg->toOCC());
      Edge *obj = new Edge(edge);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }
  } else {
    const int argc = 0;
    v8::Local<v8::Value> argv[] = {};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc,argv));
  }

}

