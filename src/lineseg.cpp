
#include "helper.h"
#include "lineseg.h"
#include "point.h"
#include "edge.h"

#include <GC_MakeSegment.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>


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
  Nan::SetPrototypeMethod(tpl, "makeEdge", makeEdge);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("LineSegment").ToLocalChecked(), tpl->GetFunction());

}

NAN_METHOD(mox::LineSegment::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  if(info.Length() != 2) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }
  mox::Point *pntFrom = ObjectWrap::Unwrap<mox::Point>(info[0]->ToObject());
  mox::Point *pntTo = ObjectWrap::Unwrap<mox::Point>(info[1]->ToObject());
  LineSegment *obj = new LineSegment(pntFrom->toOCC(), pntTo->toOCC());
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::LineSegment::makeEdge)
{
  GET_SELF(mox::LineSegment, self);

  TopoDS_Edge topoEdge = BRepBuilderAPI_MakeEdge(self->toOCC());

  // Package the edge in Javascript object
  v8::Local<v8::Object> edgeInstance = mox::Edge::NewInstance();
  mox::Edge *edge = ObjectWrap::Unwrap<mox::Edge>(edgeInstance);
  edge->setOCC(topoEdge);

  info.GetReturnValue().Set(edgeInstance);
}
