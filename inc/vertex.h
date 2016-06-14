#ifndef VERTEX_H
#define VERTEX_H

#include <nan.h>
#include <TopoDS_Vertex.hxx>

namespace mox {

  class Vertex : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    void setOCCVertex(TopoDS_Vertex occVertex);

    static v8::Local<v8::Object> NewInstance();

  private:
    Vertex() {}
    explicit Vertex(const TopoDS_Vertex occVertex);
    ~Vertex();

    static NAN_METHOD(New);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Vertex m_vertex;
  };
}


#endif // VERTEX_H
