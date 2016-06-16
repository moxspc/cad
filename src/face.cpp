
#include "helper.h"
#include "face.h"
#include "wire.h"

Nan::Persistent<v8::Function> mox::Face::constructor;

mox::Face::Face()
{
}

mox::Face::Face(TopoDS_Face occFace) : m_face(occFace)
{
}

mox::Face::~Face()
{
}

void mox::Face::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Face", tpl);

  Nan::SetPrototypeMethod(tpl, "toString", toString);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Face").ToLocalChecked(), tpl->GetFunction());
}

v8::Local<v8::Object> mox::Face::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}

NAN_METHOD(mox::Face::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  Face *obj = new Face();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Face::toString)
{
  GET_SELF(mox::Face, self);
  std::stringstream ss;
  TopAbs_Orientation orientation = self->m_face.Orientation();
  ss << " Orientation: ";
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
