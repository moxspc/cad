
#include "helper.h"
#include "edge.h"
#include "lineseg.h"

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>

Nan::Persistent<v8::Function> mox::Edge::constructor;

mox::Edge::Edge()
{
}

mox::Edge::Edge(TopoDS_Edge occEdge) : m_edge(occEdge)
{
}

mox::Edge::~Edge()
{
}

void mox::Edge::setOCC(TopoDS_Edge occEdge)
{
  m_edge = occEdge;
}

void mox::Edge::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Edge", tpl);

  Nan::SetPrototypeMethod(tpl, "toString", toString);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Edge").ToLocalChecked(), tpl->GetFunction());
}

v8::Local<v8::Object> mox::Edge::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}

NAN_METHOD(mox::Edge::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  Edge *obj = new Edge();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Edge::toString)
{
  GET_SELF(mox::Edge, self);

  std::stringstream ss;

  TopExp_Explorer exp(self->m_edge, TopAbs_VERTEX);
  while(exp.More()) {
    TopoDS_Vertex topoVtx = TopoDS::Vertex(exp.Current());
    gp_Pnt pnt = BRep_Tool::Pnt(topoVtx);
    ss << "(" << pnt.X() << "," << pnt.Y() << "," << pnt.Z() << ")";
    exp.Next();
  }
  ss << " ";
  ss << "SamRange: " << BRep_Tool::SameRange(self->m_edge) << " ";
  ss << "SamParam: " << BRep_Tool::SameParameter(self->m_edge) << " ";
  ss << "Checked: " << self->m_edge.Checked() << " ";
  TopAbs_Orientation orientation = self->m_edge.Orientation();
  ss << "Orientation: ";
  switch(orientation) {
  case TopAbs_FORWARD:
    ss << "FWD";
    break;
  case TopAbs_REVERSED:
    ss << "RVS";
    break;
  case TopAbs_INTERNAL:
    ss << "INT";
    break;
  case TopAbs_EXTERNAL:
    ss << "EXT";
    break;
  default:
    ss << "UNK";
    break;
  }

  info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}

