
#include "helper.h"
#include "circarc.h"
#include "point.h"
#include "edge.h"

#include <GC_MakeArcOfCircle.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

Nan::Persistent<v8::Function> moxcad::CircularArc::constructor;

moxcad::CircularArc::CircularArc(
  const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3)
{
  m_curveHandle = GC_MakeArcOfCircle(p1, p2, p3);
}

moxcad::CircularArc::~CircularArc()
{
}

void moxcad::CircularArc::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("CircularArc", tpl);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "makeEdge", makeEdge);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("CircularArc").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(moxcad::CircularArc::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  CHECK_NUM_ARGUMENTS(info, 3);

  moxcad::Point *p1 = ObjectWrap::Unwrap<moxcad::Point>(info[0]->ToObject());
  moxcad::Point *p2 = ObjectWrap::Unwrap<moxcad::Point>(info[1]->ToObject());
  moxcad::Point *p3 = ObjectWrap::Unwrap<moxcad::Point>(info[2]->ToObject());

  CircularArc *obj = new CircularArc(p1->toOCC(), p2->toOCC(), p3->toOCC());

  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::CircularArc::makeEdge)
{
  GET_SELF(moxcad::CircularArc, self);

  TopoDS_Edge topoEdge = BRepBuilderAPI_MakeEdge(self->toOCC());

  v8::Local<v8::Object> edgeInstance = moxcad::Edge::NewInstance();
  moxcad::Edge *edge = ObjectWrap::Unwrap<moxcad::Edge>(edgeInstance);
  edge->setOCC(topoEdge);

  info.GetReturnValue().Set(edgeInstance);
}
