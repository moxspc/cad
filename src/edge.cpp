
#include "helper.h"
#include "edge.h"
#include "lineseg.h"

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
  info.GetReturnValue().Set(Nan::New("E").ToLocalChecked());
}

