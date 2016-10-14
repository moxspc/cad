
#ifndef WIRE_H
#define WIRE_H

#include <nan.h>
#include <TopoDS_Wire.hxx>
#include <TopTools_ListOfShape.hxx>

namespace moxcad {
  class Wire : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> namespc);
    TopoDS_Wire toOCC() { return m_wire; }

  private:
    explicit Wire(const TopTools_ListOfShape& edgelist);
    ~Wire();

    static NAN_METHOD(New);
    static NAN_METHOD(makeFace);

    static Nan::Persistent<v8::Function> constructor;

    TopoDS_Wire m_wire;

  };
}

#endif // WIRE_H
