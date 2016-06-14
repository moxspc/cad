#ifndef FACE_H
#define FACE_H

#include <nan.h>
#include <TopoDS_Face.hxx>

namespace mox {

  class Face : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);

  private:
    explicit Face(const TopoDS_Face& occFace);
    ~Face();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static Nan::Persistent<v8::Function> constructor;

    const TopoDS_Face& m_face;
  };
}


#endif // FACE_H
