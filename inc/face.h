#ifndef FACE_H
#define FACE_H

#include <nan.h>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>

namespace mox {

  class Face : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    TopoDS_Face toOCC() { return m_face; }

  private:
    explicit Face(const TopoDS_Wire& occWire);
    ~Face();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Face m_face;
  };
}


#endif // FACE_H
