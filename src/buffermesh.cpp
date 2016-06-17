
#include "helper.h"
#include "buffermesh.h"

Nan::Persistent<v8::Function> mox::BufferMesh::constructor;

mox::BufferMesh::BufferMesh()
{
}

mox::BufferMesh::~BufferMesh()
{
}

void mox::BufferMesh::addVertex(TopoDS_Vertex vertex)
{
}

void mox::BufferMesh::addEdge(TopoDS_Edge edge)
{
}

void mox::BufferMesh::addFace(TopoDS_Face face)
{
}

void mox::BufferMesh::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("BufferMesh", tpl);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("BufferMesh").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::BufferMesh::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  BufferMesh *obj = new BufferMesh();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> mox::BufferMesh::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}
