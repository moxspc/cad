
#include <iostream>
#include "helper.h"
#include "edge.h"
#include "wire.h"
#include "face.h"
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

Nan::Persistent<v8::Function> moxcad::Wire::constructor;

moxcad::Wire::Wire(const TopTools_ListOfShape& edgelist)
{
  BRepBuilderAPI_MakeWire mkwire;
  mkwire.Add(edgelist);
  m_wire = mkwire.Wire();
}

moxcad::Wire::~Wire()
{
}

void moxcad::Wire::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Wire", tpl);

  Nan::SetPrototypeMethod(tpl, "makeFace", makeFace);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Wire").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(moxcad::Wire::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);

  TopTools_ListOfShape edgeList;
  for(int i=0; i<info.Length(); i++) {
    moxcad::Edge *edge = Nan::ObjectWrap::Unwrap<moxcad::Edge>(info[i]->ToObject());
    edgeList.Append(edge->toOCC());
  }
  Wire *obj = new Wire(edgeList);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::Wire::makeFace)
{
  GET_SELF(moxcad::Wire, self);
  TopoDS_Face topoFace = BRepBuilderAPI_MakeFace(self->toOCC());

  // Packacge the face in a Javascript Face object
  v8::Local<v8::Object> faceInstance = moxcad::Face::NewInstance();
  moxcad::Face *face = ObjectWrap::Unwrap<moxcad::Face>(faceInstance);
  face->setOCC(topoFace);

  info.GetReturnValue().Set(faceInstance);
}
