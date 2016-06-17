
#ifndef BUFFERMESH_H
#define BUFFERMESH_H

#include <nan.h>
#include "edge.h"
#include "face.h"
#include "vertex.h"
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>

namespace mox {

  class BufferMesh : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);

    void addFace(TopoDS_Face face);
    void addEdge(TopoDS_Edge edge);
    void addVertex(TopoDS_Vertex vertex);

    static v8::Local<v8::Object> NewInstance();

  private:
    explicit BufferMesh();
    ~BufferMesh();

    static NAN_METHOD(New);

    static Nan::Persistent<v8::Function> constructor;
  };

}
#endif // BUFFERMESH_H
