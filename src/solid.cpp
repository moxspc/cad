
#include <vector>

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
#include <GeomLib.hxx>

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

bool isInLedger(
  const std::vector<TopoDS_Shape>& ledger,
  const TopoDS_Shape& entity)
{
  for(auto item : ledger) {
    if(item.IsSame(entity)) {
      return true;
    }
  }
  return false;
}

NAN_METHOD(moxcad::Solid::numFaces)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);
  std::vector<TopoDS_Shape> faceLedger;
  unsigned int i=0;
  while(exp.More()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    if(!isInLedger(faceLedger, face)) {
      faceLedger.push_back(face);
      i++;
    }
    exp.Next();
  }
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(i));
}

NAN_METHOD(moxcad::Solid::numEdges)
{
  GET_SELF(moxcad::Solid, self);
  TopExp_Explorer exp(self->m_solid, TopAbs_EDGE);
  std::vector<TopoDS_Shape> edgeLedger;
  unsigned int i=0;
  while(exp.More()) {
    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
    if(!isInLedger(edgeLedger, edge)) {
      edgeLedger.push_back(edge);
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
  std::vector<TopoDS_Shape> vertexLedger;
  unsigned int i=0;
  while(exp.More()) {
    TopoDS_Vertex vertex = TopoDS::Vertex(exp.Current());
    if(!isInLedger(vertexLedger, vertex)) {
      vertexLedger.push_back(vertex);
      i++;
    }
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

  std::vector<TopoDS_Shape> vertexLedger;
  TopExp_Explorer exp(self->m_solid, TopAbs_VERTEX);
  while(exp.More()) {
    TopoDS_Vertex topoVtx = TopoDS::Vertex(exp.Current());

    if(!isInLedger(vertexLedger, topoVtx)) {
      vertexLedger.push_back(topoVtx);

      // Package the vertex into Javascript object and invoke callback with it
      v8::Local<v8::Object> vtxInstance = moxcad::Vertex::NewInstance();
      moxcad::Vertex *vtx = ObjectWrap::Unwrap<moxcad::Vertex>(vtxInstance);
      vtx->setOCC(topoVtx);

      // Invoke callback
      const unsigned int argc = 1;
      v8::Local<v8::Value> argv[] = { vtxInstance };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
    }

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

  std::vector<TopoDS_Shape> edgeLedger;
  TopExp_Explorer exp(self->m_solid, TopAbs_EDGE);
  while(exp.More()) {
    TopoDS_Edge topoEdge = TopoDS::Edge(exp.Current());

    if(!isInLedger(edgeLedger, topoEdge)) {
      edgeLedger.push_back(topoEdge);

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

  std::vector<TopoDS_Shape> faceLedger;
  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);
  while(exp.More()) {
    TopoDS_Face topoFace = TopoDS::Face(exp.Current());

    if(!isInLedger(faceLedger, topoFace)) {
      faceLedger.push_back(topoFace);

      // Package the face into Javascript object and invoke callback with it
      v8::Local<v8::Object> faceInstance = moxcad::Face::NewInstance();
      moxcad::Face *face = ObjectWrap::Unwrap<moxcad::Face>(faceInstance);
      face->setOCC(topoFace);

      // Invoke callback
      const unsigned int argc = 1;
      v8::Local<v8::Value> argv[] = { faceInstance };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
    }

    exp.Next();
  }
  info.GetReturnValue().Set(info.This());
}

void extractFaceBuffer(const TopoDS_Face& face, v8::Handle<v8::Object>& output)
{
  const Standard_Real linDeflection   = 0.01;
  const Standard_Real angDeflection = 0.5;

  v8::Local<v8::Context> ctx = Nan::GetCurrentContext();
  v8::Local<v8::Array> idxArr = Nan::New<v8::Array>();
  v8::Local<v8::Array> vtxArr = Nan::New<v8::Array>();
  v8::Local<v8::Array> nrmArr = Nan::New<v8::Array>();
  v8::Local<v8::Array> uvArr = Nan::New<v8::Array>();

  bool normalsPopulated = false;

  TopAbs_Orientation faceOrient = face.Orientation();

  BRepMesh_IncrementalMesh aMesh(
    face, linDeflection, Standard_False, angDeflection);
  aMesh.Perform();

  TopLoc_Location faceLocation;
  const Handle(Poly_Triangulation)& pt =
    BRep_Tool::Triangulation(face, faceLocation);

  const Poly_Array1OfTriangle& triangles = pt->Triangles();
  const TColgp_Array1OfPnt& nodes = pt->Nodes();
  const TColgp_Array1OfPnt2d *uvs;

  if(pt->HasNormals()) {
    // Get normals from the triangulation : TODO
    MOXLOG("TODO: Extract normals from triangulation");
  }

  if(pt->HasUVNodes()) {
    // Get normals from the underlying surface if available
    uvs = &pt->UVNodes();
    const TopoDS_Face zeroFace = TopoDS::Face(face.Located(TopLoc_Location()));
    Handle(Geom_Surface) hdlSurf = BRep_Tool::Surface(zeroFace);
    if(!hdlSurf.IsNull()) {
      for(Standard_Integer iterNode = nodes.Lower(), idx=0;
          iterNode <= nodes.Upper();
          iterNode++, idx++)
      {
        gp_Pnt2d uv = uvs->Value(iterNode);
        gp_Dir normal;
        GeomLib::NormEstim(hdlSurf, uv, Precision::Confusion(), normal);

        if(faceOrient == TopAbs_REVERSED) {
          normal.Reverse();
        }

        nrmArr->Set(ctx, 3*idx, Nan::New<v8::Number>(normal.X()));
        nrmArr->Set(ctx, 3*idx+1, Nan::New<v8::Number>(normal.Y()));
        nrmArr->Set(ctx, 3*idx+2, Nan::New<v8::Number>(normal.Z()));
      }
      normalsPopulated = true;
      output->Set(Nan::New("nrm").ToLocalChecked(), nrmArr);
    }
  }


  for(Standard_Integer i=triangles.Lower(),
      idx=0; i<=triangles.Upper();
      i++, idx++)
  {
    const Poly_Triangle& triangle = triangles.Value(i);
    /*
    Standard_Integer N1, N2, N3;
    triangle.Get(N1, N2, N3);
    if(faceOrient != TopAbs_FORWARD) {
      Standard_Integer tmp = N1;
      N1 = N2;
      N2 = tmp;
    }
    gp_Pnt V1(nodes(N1));
    gp_Pnt V2(nodes(N2));
    gp_Pnt V3(nodes(N3));

    if(!faceLocation.IsIdentity()) {
      const gp_Trsf& faceTransform = faceLocation.Transformation();
      V1.Transform(faceTransform);
      V2.Transform(faceTransform);
      V3.Transform(faceTransform);
    }
    */

    if(faceOrient == TopAbs_FORWARD) {
      idxArr->Set(ctx, 3*idx, Nan::New<v8::Uint32>(triangle.Value(1)-1));
      idxArr->Set(ctx, 3*idx+1, Nan::New<v8::Uint32>(triangle.Value(2)-1));
      idxArr->Set(ctx, 3*idx+2, Nan::New<v8::Uint32>(triangle.Value(3)-1));
    } else {
      idxArr->Set(ctx, 3*idx, Nan::New<v8::Uint32>(triangle.Value(2)-1));
      idxArr->Set(ctx, 3*idx+1, Nan::New<v8::Uint32>(triangle.Value(1)-1));
      idxArr->Set(ctx, 3*idx+2, Nan::New<v8::Uint32>(triangle.Value(3)-1));
    }


    if(!normalsPopulated) {
      // Calculate normal
      /*
      gp_Vec vec1(V1.X(),V1.Y(),V1.Z());
      gp_Vec vec2(V2.X(),V2.Y(),V2.Z());
      gp_Vec vec3(V3.X(),V3.Y(),V3.Z());
      gp_Vec normal = (vec2-vec1)^(vec3-vec1);
      */

      MOXLOG("TODO: Compute per-vertex normals")
    }
  }
  output->Set(Nan::New("idx").ToLocalChecked(), idxArr);

  // Vertices
  for(Standard_Integer i=nodes.Lower(), idx=0; i<=nodes.Upper(); i++, idx++) {
    gp_Pnt pnt = nodes.Value(i);
    if(!faceLocation.IsIdentity()) {
      const gp_Trsf& faceTransform = faceLocation.Transformation();
      pnt.Transform(faceTransform);
    }
    vtxArr->Set(ctx, 3*idx, Nan::New<v8::Number>(pnt.X()));
    vtxArr->Set(ctx, 3*idx+1, Nan::New<v8::Number>(pnt.Y()));
    vtxArr->Set(ctx, 3*idx+2, Nan::New<v8::Number>(pnt.Z()));
  }
  output->Set(Nan::New("vtx").ToLocalChecked(), vtxArr);

  // UVs
  if(pt->HasUVNodes()) {
    const TColgp_Array1OfPnt2d& uvs = pt->UVNodes();
    for(Standard_Integer i=nodes.Lower(), idx=0;
        i<=nodes.Upper();
        i++, idx++)
    {
      const gp_Pnt2d& uv = uvs.Value(i);
      uvArr->Set(ctx, 2*idx, Nan::New<v8::Number>(uv.X()));
      uvArr->Set(ctx, 2*idx+1, Nan::New<v8::Number>(uv.Y()));
    }
    output->Set(Nan::New("uv").ToLocalChecked(), uvArr);
  }
}

NAN_METHOD(moxcad::Solid::tessellate)
{
  v8::Local<v8::Object> buffers = Nan::New<v8::Object>();
  v8::Local<v8::Array> faceBuffers = Nan::New<v8::Array>();

  GET_SELF(moxcad::Solid, self);

  TopExp_Explorer exp(self->m_solid, TopAbs_FACE);

  int i = 0;
  while(exp.More()) {
    TopoDS_Face topoFace = TopoDS::Face(exp.Current());
    v8::Handle<v8::Object> newOutput = Nan::New<v8::Object>();
    extractFaceBuffer(topoFace, newOutput);
    faceBuffers->Set(i, newOutput);
    exp.Next();
    i++;
  }

  buffers->Set(Nan::New("faceBuffers").ToLocalChecked(), faceBuffers);

  info.GetReturnValue().Set(buffers);
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
