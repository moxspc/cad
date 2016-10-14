
#include <nan.h>

namespace moxcad {
  namespace ops {

    void Init(v8::Local<v8::Object> namespc);
    void extrude(const v8::FunctionCallbackInfo<v8::Value>& info);

    void approximate2d(const v8::FunctionCallbackInfo<v8::Value>& info);
  }
}
