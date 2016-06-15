
#include "helper.h"
#include "solid.h"
#include "vertex.h"
#include "edge.h"
#include "face.h"

#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>

Nan::Persistent<v8::Function> mox::Solid::constructor;

mox::Solid::Solid()
{
}

mox::Solid::~Solid()
{
}

void mox::Solid::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Solid").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "numFaces", numFaces);
  Nan::SetPrototypeMethod(tpl, "numEdges", numEdges);
  Nan::SetPrototypeMethod(tpl, "numVertices", numVertices);

  Nan::SetPrototypeMethod(tpl, "eachVertex", eachVertex);
  Nan::SetPrototypeMethod(tpl, "eachEdge", eachEdge);
  Nan::SetPrototypeMethod(tpl, "eachFace", eachFace);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Solid").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Solid::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  Solid *obj = new Solid();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Solid::numFaces)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_FACE);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(mox::Solid::numEdges)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_EDGE);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(mox::Solid::numVertices)
{
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_VERTEX);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(mox::Solid::eachVertex)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over vertices
  mox::Solid* obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_VERTEX);
  while(exp.More()) {
    TopoDS_Vertex topoVtx = TopoDS::Vertex(exp.Current());

    // Package the vertex into Javascript object and invoke callback with it
    v8::Local<v8::Object> vtxInstance = mox::Vertex::NewInstance();
    mox::Vertex *vtx = ObjectWrap::Unwrap<mox::Vertex>(vtxInstance);
    vtx->setOCC(topoVtx);

    // Invoke callback
    const unsigned int argc = 1;
    v8::Local<v8::Value> argv[] = { vtxInstance };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Solid::eachEdge)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over edges
  mox::Solid *obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_EDGE);
  while(exp.More()) {
    TopoDS_Edge topoEdge = TopoDS::Edge(exp.Current());

    // Package the edge into Javascript object and invoke callback with it
    v8::Local<v8::Object> edgeInstance = mox::Edge::NewInstance();
    mox::Edge *edge = ObjectWrap::Unwrap<mox::Edge>(edgeInstance);
    edge->setOCC(topoEdge);

    // Invoke callback
    const unsigned int argc = 1;
    v8::Local<v8::Value> argv[] = { edgeInstance };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Solid::eachFace)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over faces
  mox::Solid *obj = ObjectWrap::Unwrap<mox::Solid>(info.Holder());
  TopExp_Explorer exp(obj->m_solid, TopAbs_FACE);
  while(exp.More()) {
    TopoDS_Face topoFace = TopoDS::Face(exp.Current());

    // Package the face into Javascript object and invoke callback with it
    v8::Local<v8::Object> faceInstance = mox::Face::NewInstance();
    mox::Face *face = ObjectWrap::Unwrap<mox::Face>(faceInstance);
    face->setOCC(topoFace);

    // Invoke callback
    const unsigned int argc = 1;
    v8::Local<v8::Value> argv[] = { faceInstance };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> mox::Solid::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}
