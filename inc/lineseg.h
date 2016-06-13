#ifndef LINESEG_H
#define LINESEG_H

#include <nan.h>
#include <gp_Pnt.hxx>
#include <Geom_TrimmedCurve.hxx>

namespace mox {
  class LineSegment : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);

  private:
    explicit LineSegment(const gp_Pnt& from, const gp_Pnt& to);
    ~LineSegment();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static Nan::Persistent<v8::Function> constructor;

    opencascade::handle<Geom_TrimmedCurve> m_curveHandle;
  };
}

#endif // LINESEG_H

