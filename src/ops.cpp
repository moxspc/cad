
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
#include <Geom2dAPI_Interpolate.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_BezierCurve.hxx>

#include <Geom2dConvert_BSplineCurveToBezierCurve.hxx>

void moxcad::ops::Init(v8::Local<v8::Object> namespc)
{
  NODE_SET_METHOD(namespc, "extrude", moxcad::ops::extrude);
  NODE_SET_METHOD(namespc, "approximate2d", moxcad::ops::approximate2d);
  NODE_SET_METHOD(namespc, "interpolate2d", moxcad::ops::interpolate2d);
}

void moxcad::ops::extrude(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  moxcad::Face *face = Nan::ObjectWrap::Unwrap<moxcad::Face>(info[0]->ToObject());
  moxcad::Vector *dir = Nan::ObjectWrap::Unwrap<moxcad::Vector>(info[1]->ToObject());

  TopoDS_Shape occSolid = BRepPrimAPI_MakePrism(face->toOCC(), dir->toOCC());
  if(occSolid.ShapeType() != TopAbs_SOLID) {
    Nan::ThrowError("Extrude didn't generate Solid");
    return;
  }

  v8::Local<v8::Object> jsSolid = moxcad::Solid::NewInstance();
  moxcad::Solid *solid = Nan::ObjectWrap::Unwrap<moxcad::Solid>(jsSolid);
  assert(solid != NULL);
  solid->setOCC(occSolid);

  info.GetReturnValue().Set(jsSolid);
}


void moxcad::ops::approximate2d(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  CHECK_NUM_ARGUMENTS(info, 2);
  v8::Local<v8::Array> coordList = v8::Handle<v8::Array>::Cast(info[0]);
  v8::Local<v8::Object> options = info[1]->ToObject();

  uint nPoints = coordList->Length();
  TColgp_Array1OfPnt2d arrPoints(1, nPoints);
  for(uint i=0; i<nPoints; i++) {
    v8::Local<v8::Array> coord = v8::Handle<v8::Array>::Cast(coordList->Get(i));
    arrPoints.SetValue(i+1,
      gp_Pnt2d(coord->Get(0)->NumberValue(), coord->Get(1)->NumberValue()));
  }

  double tolerance = 10.0;
  if(options->HasRealNamedProperty(Nan::New("tolerance").ToLocalChecked())) {
    tolerance = options->Get(
                Nan::New("tolerance").ToLocalChecked())->NumberValue();
  }

  Geom2dAPI_PointsToBSpline api(arrPoints, 3,3,GeomAbs_G1, tolerance);

  if(!api.IsDone()) {
    Nan::ThrowError("Geom2dAPI_PointsToBSpline not done");
    return;
  }

  Geom2dConvert_BSplineCurveToBezierCurve convapi(api.Curve());

  v8::Local<v8::Array> bezArray = Nan::New<v8::Array>(convapi.NbArcs());

  for(int i=1; i<=convapi.NbArcs(); i++) {
    assert(convapi.Arc(i)->Degree() == 3);
    v8::Local<v8::Array> cpointsArray = Nan::New<v8::Array>(4);
    for(int j=1; j<=convapi.Arc(i)->NbPoles(); j++) {
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

void moxcad::ops::interpolate2d(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  CHECK_NUM_ARGUMENTS(info, 2);
  v8::Local<v8::Array> coordList = v8::Handle<v8::Array>::Cast(info[0]);
  v8::Local<v8::Object> options = info[1]->ToObject();

  bool isClosed = true;
  if(options->HasRealNamedProperty(Nan::New("isClosed").ToLocalChecked())) {
    isClosed = options->Get(
                Nan::New("isClosed").ToLocalChecked())->BooleanValue();
  }
  double tolerance = 1e-6;
  if(options->HasRealNamedProperty(Nan::New("tolerance").ToLocalChecked())) {
    tolerance = options->Get(
                Nan::New("tolerance").ToLocalChecked())->NumberValue();
  }

  uint nPoints = coordList->Length();
  Handle(TColgp_HArray1OfPnt2d) arrPoints = new TColgp_HArray1OfPnt2d(1, nPoints);

  for(uint i=0; i<nPoints; i++) {
    v8::Local<v8::Array> coord = v8::Handle<v8::Array>::Cast(coordList->Get(i));
    arrPoints->SetValue(i+1,
      gp_Pnt2d(coord->Get(0)->NumberValue(), coord->Get(1)->NumberValue()));
  }

  Geom2dAPI_Interpolate api(arrPoints, isClosed, tolerance);

  api.Perform();

  if(!api.IsDone()) {
    Nan::ThrowError("Geom2dAPI_Interpolate not done");
    return;
  }

  Geom2dConvert_BSplineCurveToBezierCurve convapi(api.Curve());

  v8::Local<v8::Array> bezArray = Nan::New<v8::Array>(convapi.NbArcs());

  for(int i=1; i<=convapi.NbArcs(); i++) {
    v8::Local<v8::Array> cpointsArray = Nan::New<v8::Array>(convapi.Arc(i)->NbPoles());
    for(int j=1; j<=convapi.Arc(i)->NbPoles(); j++) {
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
