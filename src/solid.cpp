
#include "helper.h"
#include "solid.h"
#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "buffermesh.h"

#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepMesh_IncrementalMesh.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <TColgp_Array1OfPnt.hxx>

Nan::Persistent<v8::Function> moxcad::Solid::constructor;

moxcad::Solid::Solid()
{
}

moxcad::Solid::~Solid()
{
}

void moxcad::Solid::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Solid", tpl);

  Nan::SetPrototypeMethod(tpl, "numFaces", numFaces);
  Nan::SetPrototypeMethod(tpl, "numEdges", numEdges);
  Nan::SetPrototypeMethod(tpl, "numVertices", numVertices);
  Nan::SetPrototypeMethod(tpl, "numShells", numShells);

  Nan::SetPrototypeMethod(tpl, "eachVertex", eachVertex);
  Nan::SetPrototypeMethod(tpl, "eachEdge", eachEdge);
  Nan::SetPrototypeMethod(tpl, "eachFace", eachFace);

  Nan::SetPrototypeMethod(tpl, "tessellate", tessellate);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Solid").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(moxcad::Solid::New)
{
  ALLOW_ONLY_CONSTRUCTOR(info);
  Solid *obj = new Solid();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::Solid::numFaces)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(moxcad::Solid::numEdges)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_EDGE);
  unsigned int i=0;
  while(exp.More()) {
    TopoDS_Edge topoEdge = TopoDS::Edge(exp.Current());
    if(topoEdge.Orientation() == TopAbs_FORWARD) {
      i++;
    }
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(moxcad::Solid::numVertices)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_VERTEX);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(moxcad::Solid::numShells)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_SHELL);
  unsigned int i=0;
  while(exp.More()) {
    i++;
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));

}

NAN_METHOD(moxcad::Solid::eachVertex)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over vertices
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_VERTEX);
  while(exp.More()) {
    TopoDS_Vertex topoVtx = TopoDS::Vertex(exp.Current());

    // Package the vertex into Javascript object and invoke callback with it
    v8::Local<v8::Object> vtxInstance = moxcad::Vertex::NewInstance();
    moxcad::Vertex *vtx = ObjectWrap::Unwrap<moxcad::Vertex>(vtxInstance);
    vtx->setOCC(topoVtx);

    // Invoke callback
    const unsigned int argc = 1;
    v8::Local<v8::Value> argv[] = { vtxInstance };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::Solid::eachEdge)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over edges
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_EDGE);
  while(exp.More()) {
    TopoDS_Edge topoEdge = TopoDS::Edge(exp.Current());

    if(topoEdge.Orientation() == TopAbs_FORWARD) {
      // Package the edge into Javascript object and invoke callback with it
      v8::Local<v8::Object> edgeInstance = moxcad::Edge::NewInstance();
      moxcad::Edge *edge = ObjectWrap::Unwrap<moxcad::Edge>(edgeInstance);
      edge->setOCC(topoEdge);

      // Invoke callback
      const unsigned int argc = 1;
      v8::Local<v8::Value> argv[] = { edgeInstance };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
    }

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::Solid::eachFace)
{
  // Extract callback function
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  // Iterate over faces
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);
  while(exp.More()) {
    TopoDS_Face topoFace = TopoDS::Face(exp.Current());

    // Package the face into Javascript object and invoke callback with it
    v8::Local<v8::Object> faceInstance = moxcad::Face::NewInstance();
    moxcad::Face *face = ObjectWrap::Unwrap<moxcad::Face>(faceInstance);
    face->setOCC(topoFace);

    // Invoke callback
    const unsigned int argc = 1;
    v8::Local<v8::Value> argv[] = { faceInstance };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(moxcad::Solid::tessellate)
{
  v8::Local<v8::Object> bufferMeshHdl = moxcad::BufferMesh::NewInstance();
  moxcad::BufferMesh *bufferMesh =
    ObjectWrap::Unwrap<moxcad::BufferMesh>(bufferMeshHdl);

  GET_SELF(moxcad::Solid, self);

  const Standard_Real aLinearDeflection   = 0.01;
  const Standard_Real anAngularDeflection = 0.5;

  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);
  while(exp.More()) {
    TopoDS_Face topoFace = TopoDS::Face(exp.Current());
    BRepMesh_IncrementalMesh aMesh(topoFace, aLinearDeflection, Standard_False, anAngularDeflection);
    aMesh.Perform();
    TopLoc_Location l;
    const Handle(Poly_Triangulation)& pt = BRep_Tool::Triangulation(topoFace, l);
    //MOXLOG("Num Triangles " << (pt.IsNull() ? 0 : pt->NbTriangles()));
    const Poly_Array1OfTriangle& polyarr = pt->Triangles();

    for(Standard_Integer i=polyarr.Lower(); i<=polyarr.Upper(); i++) {
      const Poly_Triangle& ptri = polyarr.Value(i);
      //MOXLOG("Indices " << ptri.Value(1) << "," << ptri.Value(2) << "," << ptri.Value(3));
    }

    const TColgp_Array1OfPnt& nodes = pt->Nodes();
    for(Standard_Integer i=nodes.Lower(); i<=nodes.Upper(); i++) {
      const gp_Pnt& pnt = nodes.Value(i);
      //MOXLOG(i << " [" << pnt.X() << "," << pnt.Y() << "," << pnt.Z() << "]");
    }

    bufferMesh->addFace(topoFace);
    exp.Next();
  }
  info.GetReturnValue().Set(bufferMeshHdl);
}

v8::Local<v8::Object> moxcad::Solid::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[1] = {Nan::New("xxx").ToLocalChecked()};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}
