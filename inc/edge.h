
#ifndef EDGE_H
#define EDGE_H

#include <nan.h>
#include <TopoDS_Edge.hxx>

namespace mox {

  class Edge : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    const TopoDS_Edge toOCC() { return m_edge; }

  private:
    explicit Edge(const TopoDS_Edge& occEdge);
    ~Edge();

    static NAN_METHOD(New);
    static Nan::Persistent<v8::Function> constructor;

    const TopoDS_Edge& m_edge;
  };
}


#endif // EDGE_H
