
#include "mox.h"

#include "geom.h"

#include <gp.hxx>
#include "gp_XYZ.hxx"

void mox::doOCCMath(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  gp_XYZ xyz(3,4,1);
  v8::Local<v8::Number> answer = v8::Number::New(isolate, xyz.Modulus());
  args.GetReturnValue().Set(answer);
}

void mox::init(Local<Object> exports)
{
  mox::Geom::Init(exports);
  NODE_SET_METHOD(exports, "doOCCMath", doOCCMath);
}

NODE_MODULE(mox, mox::init)


