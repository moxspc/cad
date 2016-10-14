
#ifndef EDGE_H
#define EDGE_H

#include <nan.h>
#include <TopoDS_Edge.hxx>

namespace moxcad {

  class Edge : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);

    TopoDS_Edge toOCC() { return m_edge; }
    void setOCC(TopoDS_Edge occEdge);

    static v8::Local<v8::Object> NewInstance();

  private:
    Edge();
    explicit Edge(TopoDS_Edge occEdge);
    ~Edge();

    static NAN_METHOD(New);
    static NAN_METHOD(toString);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Edge m_edge;
  };
}


#endif // EDGE_H
