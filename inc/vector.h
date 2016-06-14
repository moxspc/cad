#ifndef VECTOR_H
#define VECTOR_H

#include <nan.h>
#include <gp_Vec.hxx>

namespace mox {
  class Vector : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    const gp_Vec& toOCC() { return m_vector; }

  private:
    explicit Vector(double x, double y, double z);
    ~Vector();

    static NAN_METHOD(New);

    static Nan::Persistent<v8::Function> constructor;

    gp_Vec m_vector;
  };
}

#endif // VECTOR_H
