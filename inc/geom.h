#ifndef GEOM_H
#define GEOM_H

#include <nan.h>

namespace mox {

  class Geom : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);

  private:
    explicit Geom();
    ~Geom();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static Nan::Persistent<v8::Function> constructor;

  };
}

#endif // GEOM_H

