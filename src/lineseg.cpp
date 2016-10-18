
#include "helper.h"
#include "lineseg.h"
#include "point.h"
#include "edge.h"

#include <GC_MakeSegment.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

Nan::Persistent<v8::Function> moxcad::LineSegment::constructor;

moxcad::LineSegment::LineSegment(const gp_Pnt &from, const gp_Pnt &to)
{
  m_curveHandle = GC_MakeSegment(from, to);
}

moxcad::LineSegment::~LineSegment()
{
}

void moxcad::LineSegment::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("LineSegment", tpl);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "makeEdge", makeEdge);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("LineSegment").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(moxcad::LineSegment::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  CHECK_NUM_ARGUMENTS(info, 2);

  moxcad::Point *pntFrom = ObjectWrap::Unwrap<moxcad::Point>(info[0]->ToObject());
  moxcad::Point *pntTo = ObjectWrap::Unwrap<moxcad::Point>(info[1]->ToObject());

  LineSegment *obj = new LineSegment(pntFrom->toOCC(), pntTo->toOCC());

  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::LineSegment::makeEdge)
{
  GET_SELF(moxcad::LineSegment, self);

  TopoDS_Edge topoEdge = BRepBuilderAPI_MakeEdge(self->toOCC());

  // Package the edge in Javascript object
  v8::Local<v8::Object> edgeInstance = moxcad::Edge::NewInstance();
  moxcad::Edge *edge = ObjectWrap::Unwrap<moxcad::Edge>(edgeInstance);
  edge->setOCC(topoEdge);

  info.GetReturnValue().Set(edgeInstance);
}
