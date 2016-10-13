
#include "helper.h"
#include <iostream>
#include "ops.h"

#include "vector.h"
#include "face.h"
#include "solid.h"

#include <TopAbs_ShapeEnum.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <Geom2dAPI_PointsToBSpline.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Geom2dConvert_BSplineCurveToBezierCurve.hxx>


void mox::ops::Init(v8::Local<v8::Object> namespc)
{
  NODE_SET_METHOD(namespc, "extrude", mox::ops::extrude);
  NODE_SET_METHOD(namespc, "approximate2d", mox::ops::approximate2d);
}

void mox::ops::extrude(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  mox::Face *face = Nan::ObjectWrap::Unwrap<mox::Face>(info[0]->ToObject());
  mox::Vector *dir = Nan::ObjectWrap::Unwrap<mox::Vector>(info[1]->ToObject());

  TopoDS_Shape occSolid = BRepPrimAPI_MakePrism(face->toOCC(), dir->toOCC());
  if(occSolid.ShapeType() != TopAbs_SOLID) {
    Nan::ThrowError("Extrude didn't generate Solid");
    return;
  }

  v8::Local<v8::Object> jsSolid = mox::Solid::NewInstance();
  mox::Solid *solid = Nan::ObjectWrap::Unwrap<mox::Solid>(jsSolid);
  assert(solid != NULL);
  solid->setOCC(occSolid);

  info.GetReturnValue().Set(jsSolid);
}


void mox::ops::approximate2d(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  uint nPoints = info.Length();
  TColgp_Array1OfPnt2d arrPoints(1, nPoints);
  for(uint i=0; i<nPoints; i++) {
    v8::Local<v8::Array> coord = v8::Handle<v8::Array>::Cast(info[i]);
    arrPoints.SetValue(i+1,
      gp_Pnt2d(coord->Get(0)->NumberValue(), coord->Get(1)->NumberValue()));
  }

  Geom2dAPI_PointsToBSpline api(arrPoints, 3,3,GeomAbs_G1, 1e-6);

  Geom2dConvert_BSplineCurveToBezierCurve convapi(api.Curve());

  v8::Local<v8::Array> bezArray = Nan::New<v8::Array>(convapi.NbArcs());

  for(uint i=1; i<=convapi.NbArcs(); i++) {
    assert(convapi.Arc(i)->Degree() == 3);
    v8::Local<v8::Array> cpointsArray = Nan::New<v8::Array>(4);
    for(uint j=1; j<=convapi.Arc(i)->NbPoles(); j++) {
      v8::Local<v8::Array> cpoint = Nan::New<v8::Array>(2);
      gp_Pnt2d pole = convapi.Arc(i)->Pole(j);
      cpoint->Set(0, Nan::New<v8::Number>(pole.X()));
      cpoint->Set(1, Nan::New<v8::Number>(pole.Y()));

      cpointsArray->Set(j-1, cpoint);
    }
    bezArray->Set(i-1, cpointsArray);
  }
  info.GetReturnValue().Set(bezArray);
}
