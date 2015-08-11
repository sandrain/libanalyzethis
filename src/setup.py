from distutils.core import setup, Extension

py_lat_module = Extension ('py_lat_module',
                           sources=['pythonSched.c','lat_module.c','lat_workflow.c'],
                           extra_compile_args=['-I../include/'])

setup (name='LibAnalyzeThis',
       version = '1.0',
       description = 'AnalyeThis Scheduling Module',
       ext_modules=[py_lat_module])
