

(Convention: **Class**, *method(args)->returnValue*, `namespace`)

---
`mox`

* `geom`
  - **Point**
    - *constructor(x=0,y=0,z=0)*
    - *set(x,y,z)*
    - *x()->Number*
    - *y()->Number*
    - *z()->Number*
  - **Vector**
    - *constructor(x=0,y=0,z=0)*
  - **LineSegment**
    - *static make(fromPoint, toPoint) -> LineSegment*
    - *makeEdge() -> Edge*
  - **CircleArc**
  - **EllipseArc**
  - **BezierCurve**
  - **BSplineCurve**

* `topo`
  - **Vertex**
  - **Edge**
  - **Face**
  - **Wire**
    - *constructor(edges)*
    - *addEdge(edge)*
    - *makeFace() -> Face*
  - **Shell**
  - **Solid**
    - *numVertices() -> Number*
    - *numEdges() -> Number*
    - *numFaces() -> Number*
    - *eachVertex(callback(vertex))*
    - *eachEdge(callback(edge))*
    - *eachFace(callback(face))*

* `ops`
  - *extrude(profileFace, dirVector) -> Solid*
  - *revolve() -> Solid*
  - *fillet(solid, edges)*
  - *chamfer(solid, edges)*


