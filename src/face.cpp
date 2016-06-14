
#include "face.h"

Nan::Persistent<v8::Function> mox::Face::constructor;

mox::Face::Face(const TopoDS_Face &occFace) : m_face(occFace)
{
}

mox::Face::~Face()
{
}
