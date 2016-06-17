
#ifndef SOLID_H
#define SOLID_H

#include <nan.h>
#include <TopoDS_Solid.hxx>

namespace mox {

  class Solid : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);

    TopoDS_Shape toOCC() { return m_solid; }
    void setOCC(TopoDS_Shape solid) { m_solid = solid; }

    static v8::Local<v8::Object> NewInstance();

  private:
    explicit Solid();
    ~Solid();

    static NAN_METHOD(New);

    static NAN_METHOD(numVertices);
    static NAN_METHOD(numEdges);
    static NAN_METHOD(numFaces);
    static NAN_METHOD(numShells);

    static NAN_METHOD(eachVertex);
    static NAN_METHOD(eachEdge);
    static NAN_METHOD(eachFace);

    static NAN_METHOD(tessellate);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Shape m_solid;
  };
}

#endif // SOLID_H
