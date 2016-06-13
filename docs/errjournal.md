
Error Message and their resolutions

---

    Error: dlopen(/Users/jayesh/moxspc/mox/build/Release/mox.node, 1): Symbol not found: __ZTVN3mox11LineSegmentE
      Referenced from: /Users/jayesh/moxspc/mox/build/Release/mox.node
      Expected in: flat namespace

The problem was, I had declared the destructor of `mox::LineSegment` class, but
had forgotten to implement it

---
