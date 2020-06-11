from distutils.core import setup, Extension
import numpy

# define the extension module
hello_module_np = Extension('kmp_search', sources=['kmp_array.c'],
                          include_dirs=[numpy.get_include()])

# run the setup
setup(ext_modules=[hello_module_np])