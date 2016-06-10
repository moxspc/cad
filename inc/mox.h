
#ifndef __MOX_H__
#define __MOX_H__

#include "node.h"

namespace mox {

  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void doOCCMath(const FunctionCallbackInfo<Value>& args);

  void init(Local<Object> exports);
}

#endif // __MOX_H__
