
#include <iostream>
#include "helper.h"
#include "edge.h"
#include "wire.h"
#include "face.h"
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

Nan::Persistent<v8::Function> mox::Wire::constructor;

mox::Wire::Wire(const TopTools_ListOfShape& edgelist)
{
  BRepBuilderAPI_MakeWire mkwire;
  mkwire.Add(edgelist);
  m_wire = mkwire.Wire();
}

mox::Wire::~Wire()
{
}

void mox::Wire::Init(v8::Local<v8::Object> namespc)
{
  Nan::HandleScope scope;
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Wire").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "makeFace", makeFace);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Wire").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(mox::Wire::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  TopTools_ListOfShape edgeList;
  for(int i=0; i<info.Length(); i++) {
    mox::Edge *edge = Nan::ObjectWrap::Unwrap<mox::Edge>(info[i]->ToObject());
    edgeList.Append(edge->toOCC());
  }
  Wire *obj = new Wire(edgeList);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(mox::Wire::makeFace)
{
  mox::Wire *wire = ObjectWrap::Unwrap<mox::Wire>(info.Holder());
  TopoDS_Face topoFace = BRepBuilderAPI_MakeFace(wire->toOCC());

  // Packacge the face in a Javascript Face object
  v8::Local<v8::Object> faceInstance = mox::Face::NewInstance();
  mox::Face *face = ObjectWrap::Unwrap<mox::Face>(faceInstance);
  face->setOCC(topoFace);

  info.GetReturnValue().Set(faceInstance);
}
