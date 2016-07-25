# setup.py
from distutils.core import setup, Extension

setup(name='SensorLib',
      ext_modules=[
        Extension('SensorLib',
                  ['am2301.c','qc12864b.c','python_warpper.c'],
                  include_dirs = ['./'],
                  define_macros = [('FOO','1')],
                  undef_macros = ['BAR'],
                  library_dirs = ['/usr/local/lib'],
                  libraries = ['wiringPi']
                  )
        ]
)
