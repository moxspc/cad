
#include "helper.h"
#include "buffermesh.h"

Nan::Persistent<v8::Function> moxcad::BufferMesh::constructor;

moxcad::BufferMesh::BufferMesh()
{
}

moxcad::BufferMesh::~BufferMesh()
{
}

void moxcad::BufferMesh::addVertex(TopoDS_Vertex vertex)
{
}

void moxcad::BufferMesh::addEdge(TopoDS_Edge edge)
{
}

void moxcad::BufferMesh::addFace(TopoDS_Face face)
{
}

void moxcad::BufferMesh::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("BufferMesh", tpl);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("BufferMesh").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(moxcad::BufferMesh::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  BufferMesh *obj = new BufferMesh();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> moxcad::BufferMesh::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[1] = {Nan::New("xxx").ToLocalChecked()};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}
