from distutils.core import setup, Extension

lat_module = Extension ('lat_module', sources=['pythonSched.c'])

setup ( name='LibAnalyzeThis',
        version = '1.0',
        description = 'AnalyeThis Scheduling Module',
        ext_modules=[lat_module])
