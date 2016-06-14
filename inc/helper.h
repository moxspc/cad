
#define INIT_HELPER(name) \
  Nan::HandleScope scope; \
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);\
  tpl->SetClassName(Nan::New(name).ToLocalChecked()); \
  tpl->InstanceTemplate()->SetInternalFieldCount(1); \
  constructor.Reset(tpl->GetFunction()); \
  namespc->Set(Nan::New(name).ToLocalChecked(), tpl->GetFunction());
