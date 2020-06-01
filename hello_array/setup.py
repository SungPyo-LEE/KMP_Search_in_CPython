
from distutils.core import setup, Extension
import numpy

# define the extension module
hello_module_np = Extension('hello_array', sources=['hello_array.c'],
                          include_dirs=[numpy.get_include()])

# run the setup
setup(ext_modules=[hello_module_np])