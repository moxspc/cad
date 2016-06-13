#ifndef POINT_H
#define POINT_H

#include <nan.h>
#include <gp_Pnt.hxx>

namespace mox {

  class Point : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    const gp_Pnt& toOCC() { return m_point; }

  private:
    explicit Point(double x, double y, double z);
    ~Point();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static Nan::Persistent<v8::Function> constructor;

    static void GetX(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void GetY(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void GetZ(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static void SetXYZ(const Nan::FunctionCallbackInfo<v8::Value>& info);


    gp_Pnt m_point;
  };

}

#endif // POINT_H

