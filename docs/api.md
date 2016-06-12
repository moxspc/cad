

(Convention: **Class**, *method(args)->returnValue*, `namespace`)

---
`mox`

* `geom`
  - **Point**
    - *constructor(x=0,y=0,z=0)*
    - *set(x,y,z)*
  - **LineSegment**
    - *static make(fromPoint, toPoint)*
  - **CircleArc**
  - **EllipseArc**
  - **BezierCurve**
  - **BSplineCurve**

* `topo`
  - **Vertex**
  - **Edge**
  - **Face**
    - *static make(wire)*
  - **Wire**
    - *constructor(edges)*
    - *addEdge(edge)*
  - **Shell**
  - **Solid**

* `ops`
  - *extrude(face)->Solid*
  - *revolve()->Solid*
  - *fillet(solid, edges)*
  - *chamfer(solid, edges)*


