{
  "variables" : {
    "OCC_ROOT" : '/home/jayesh/output/occ'
  },
  "targets": [
    {
      "target_name": "moxcad",
      "include_dirs" : [
        "inc",
        "<(OCC_ROOT)/inc",
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "<!@(node -e \"console.log(require('fs').readdirSync('./src').map(f=>'src/'+f).join(' '))\")",
        "<!@(node -e \"console.log(require('fs').readdirSync('./inc').map(f=>'inc/'+f).join(' '))\")"
      ],
      "conditions" : [
        [
          "OS=='win'",
          {
            "cflags": ['-fPIC', '-std=c++0x', '-stdlib=libc++', '-Wall'],
          }
        ],
        [
          "OS=='linux'",
          {
            "cflags": ['-fPIC', '-std=c++0x', '-Wall'],
          }
        ]
      ],
      "cflags_cc!": ['-fno-rtti', '-fno-exceptions' ],
      "xcode_settings" : {
        'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++', '-v'],
        'OTHER_LDFLAGS': ['-stdlib=libc++'],
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        "OTHER_CFLAGS" : ['-fPIC', '-std=c++11','-stdlib=libc++', '-Wall']
      },
      "conditions" : [
        [ "OS=='win'",
          {
            "variables" : {
              'LIB_DIR' : '<(OCC_ROOT)/win64/vc12/lib'
            }
          }
        ],
        [ "OS=='linux'",
          {
            "variables" : {
              'LIB_DIR' : '<(OCC_ROOT)/lib'
            }
          }
        ],
        [ "OS=='mac'",
          {
            "variables" : {
              'LIB_DIR' : '<(OCC_ROOT)/lib'
            }
          }
        ]
      ],
      "link_settings": {
        "conditions" : [
          [
            "OS=='win'",
            {
              "libraries": [
                '<(LIB_DIR)/FWOSPlugin',
                '<(LIB_DIR)/TKBO',
                '<(LIB_DIR)/TKBRep',
                '<(LIB_DIR)/TKBin',
                '<(LIB_DIR)/TKBinL',
                '<(LIB_DIR)/TKBinTObj',
                '<(LIB_DIR)/TKBinXCAF',
                '<(LIB_DIR)/TKBool',
                '<(LIB_DIR)/TKCAF',
                '<(LIB_DIR)/TKCDF',
                '<(LIB_DIR)/TKDCAF',
                '<(LIB_DIR)/TKDraw',
                '<(LIB_DIR)/TKFeat',
                '<(LIB_DIR)/TKFillet',
                '<(LIB_DIR)/TKG2d',
                '<(LIB_DIR)/TKG3d',
                '<(LIB_DIR)/TKGeomAlgo',
                '<(LIB_DIR)/TKGeomBase',
                '<(LIB_DIR)/TKHLR',
                '<(LIB_DIR)/TKIGES',
                '<(LIB_DIR)/TKLCAF',
                '<(LIB_DIR)/TKMath',
                '<(LIB_DIR)/TKMesh',
                '<(LIB_DIR)/TKMeshVS',
                '<(LIB_DIR)/TKOffset',
                '<(LIB_DIR)/TKOpenGl',
                '<(LIB_DIR)/TKPrim',
                '<(LIB_DIR)/TKQADraw',
                '<(LIB_DIR)/TKSTEP',
                '<(LIB_DIR)/TKSTEP209',
                '<(LIB_DIR)/TKSTEPAttr',
                '<(LIB_DIR)/TKSTEPBase',
                '<(LIB_DIR)/TKSTL',
                '<(LIB_DIR)/TKService',
                '<(LIB_DIR)/TKShHealing',
                '<(LIB_DIR)/TKStd',
                '<(LIB_DIR)/TKStdL',
                '<(LIB_DIR)/TKTObj',
                '<(LIB_DIR)/TKTObjDRAW',
                '<(LIB_DIR)/TKTopAlgo',
                '<(LIB_DIR)/TKTopTest',
                '<(LIB_DIR)/TKV3d',
                '<(LIB_DIR)/TKVCAF',
                '<(LIB_DIR)/TKVRML',
                '<(LIB_DIR)/TKViewerTest',
                '<(LIB_DIR)/TKXCAF',
                '<(LIB_DIR)/TKXDEDRAW',
                '<(LIB_DIR)/TKXDEIGES',
                '<(LIB_DIR)/TKXDESTEP',
                '<(LIB_DIR)/TKXMesh',
                '<(LIB_DIR)/TKXSBase',
                '<(LIB_DIR)/TKXSDRAW',
                '<(LIB_DIR)/TKXml',
                '<(LIB_DIR)/TKXmlL',
                '<(LIB_DIR)/TKXmlTObj',
                '<(LIB_DIR)/TKXmlXCAF',
                '<(LIB_DIR)/TKernel'
              ]
            }
          ],
          [
            "OS=='linux'",
            {
              "libraries": [
                '-Wl,--start-group',
                '<(LIB_DIR)/libTKBO.a',
                '<(LIB_DIR)/libTKBRep.a',
                '<(LIB_DIR)/libTKBool.a',
                '<(LIB_DIR)/libTKFeat.a',
                '<(LIB_DIR)/libTKFillet.a',
                '<(LIB_DIR)/libTKG2d.a',
                '<(LIB_DIR)/libTKG3d.a',
                '<(LIB_DIR)/libTKGeomAlgo.a',
                '<(LIB_DIR)/libTKGeomBase.a',
                '<(LIB_DIR)/libTKHLR.a',
                '<(LIB_DIR)/libTKMath.a',
                '<(LIB_DIR)/libTKMesh.a',
                '<(LIB_DIR)/libTKOffset.a',
                '<(LIB_DIR)/libTKPrim.a',
                '<(LIB_DIR)/libTKTopAlgo.a',
                '<(LIB_DIR)/libTKernel.a',
                '-Wl,--end-group'
              ]
            }
          ],
          [
            "OS=='mac'",
            {
              "libraries": [
                '<(LIB_DIR)/libTKBO.a',
                '<(LIB_DIR)/libTKBRep.a',
                '<(LIB_DIR)/libTKBool.a',
                '<(LIB_DIR)/libTKFeat.a',
                '<(LIB_DIR)/libTKFillet.a',
                '<(LIB_DIR)/libTKG2d.a',
                '<(LIB_DIR)/libTKG3d.a',
                '<(LIB_DIR)/libTKGeomAlgo.a',
                '<(LIB_DIR)/libTKGeomBase.a',
                '<(LIB_DIR)/libTKHLR.a',
                '<(LIB_DIR)/libTKMath.a',
                '<(LIB_DIR)/libTKMesh.a',
                '<(LIB_DIR)/libTKOffset.a',
                '<(LIB_DIR)/libTKPrim.a',
                '<(LIB_DIR)/libTKTopAlgo.a',
                '<(LIB_DIR)/libTKernel.a'
              ]
            }
          ]
        ]
      }
    }
  ]
}
