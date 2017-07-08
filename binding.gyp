{
  'targets': [{
    'target_name': 'screenjs',
        'include_dirs': [
        "<!(node -e \"require('nan')\")"
    ],
    'cflags': [
      '-Wall',
      '-Wparentheses',
      '-Winline',
      '-Wbad-function-cast',
      '-Wdisabled-optimization'
    ],

    'conditions': [
      ['OS == "mac"', {
        'include_dirs': [
          'System/Library/Frameworks/CoreFoundation.Framework/Headers',
          'System/Library/Frameworks/Carbon.Framework/Headers',
          'System/Library/Frameworks/ApplicationServices.framework/Headers',
          'System/Library/Frameworks/OpenGL.framework/Headers',
        ],
        'link_settings': {
          'libraries': [
            '-framework Carbon',
            '-framework CoreFoundation',
            '-framework ApplicationServices',
            '-framework OpenGL'
          ]
        }
      }],

      ['OS == "linux"', {
        'link_settings': {
          'libraries': [
            '-lX11'
          ]
        },

        'sources': [
          'libs/xdisplay.c'
        ]
      }],

      ["OS=='win'", {
        'defines': ['IS_WINDOWS']
      }]
    ],

    'sources': [
      'screen.cc',
      'libs/screen.c',
      'libs/screengrab.c',
      'libs/MMBitmap.c'
      ]
  }]
}
