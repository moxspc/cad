
#include <iostream>

#define INIT_HELPER(name) \
  Nan::HandleScope scope; \
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);\
  tpl->SetClassName(Nan::New(name).ToLocalChecked()); \
  tpl->InstanceTemplate()->SetInternalFieldCount(1); \
  constructor.Reset(tpl->GetFunction()); \
  namespc->Set(Nan::New(name).ToLocalChecked(), tpl->GetFunction());

#define ALLOW_ONLY_CONSTRUCTOR(info) \
  if(!info.IsConstructCall()) { \
    Nan::ThrowError("Only constructor usage with new is supported"); \
    return; \
  }

#define GET_SELF(type, var) \
  type *var = ObjectWrap::Unwrap<type>(info.Holder());

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define MOXLOG(msg) \
  std::cout << "[" << __FILENAME__ << ":" << __LINE__ << "]" << msg << std::endl;
