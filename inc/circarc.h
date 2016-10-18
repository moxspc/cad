#pragma once

#include <nan.h>
#include <gp_Pnt.hxx>
#include <Geom_TrimmedCurve.hxx>

namespace moxcad {

  class CircularArc : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    opencascade::handle<Geom_TrimmedCurve> toOCC() { return m_curveHandle; }

  private:
    opencascade::handle<Geom_TrimmedCurve> m_curveHandle;

    explicit CircularArc(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3);
    ~CircularArc();

    static NAN_METHOD(New);
    static NAN_METHOD(makeEdge);

    static Nan::Persistent<v8::Function> constructor;
  };
}
