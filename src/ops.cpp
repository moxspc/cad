
#include <iostream>
#include "ops.h"

#include "vector.h"
#include "face.h"

#include <TopAbs_ShapeEnum.hxx>
#include <BRepPrimAPI_MakePrism.hxx>


void mox::ops::Init(v8::Local<v8::Object> namespc)
{
  NODE_SET_METHOD(namespc, "extrude", mox::ops::extrude);
}

void mox::ops::extrude(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  mox::Face *face = Nan::ObjectWrap::Unwrap<mox::Face>(info[0]->ToObject());
  mox::Vector *dir = Nan::ObjectWrap::Unwrap<mox::Vector>(info[1]->ToObject());

  TopoDS_Shape solid = BRepPrimAPI_MakePrism(face->toOCC(), dir->toOCC());

}

