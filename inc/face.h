#ifndef FACE_H
#define FACE_H

#include <nan.h>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>

namespace moxcad {

  class Face : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    TopoDS_Face toOCC() { return m_face; }
    void setOCC(TopoDS_Face occFace) { m_face = occFace; }

    static v8::Local<v8::Object> NewInstance();

  private:
    Face();
    explicit Face(TopoDS_Face occFace);
    ~Face();

    static NAN_METHOD(New);
    static NAN_METHOD(toString);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Face m_face;
  };
}


#endif // FACE_H
