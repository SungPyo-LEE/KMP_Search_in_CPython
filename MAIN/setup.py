from distutils.core import setup, Extension
import numpy

# define the extension module
kmp_module_np = Extension('nlp_c', sources=['kmp_array.c'],
                          include_dirs=[numpy.get_include()])

# run the setup
setup(ext_modules=[kmp_module_np])