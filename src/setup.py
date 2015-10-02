from distutils.core import setup, Extension

py_lat_module = Extension ('py_lat_module',
                           sources=['pythonSched.c',
                                    'lat_debug.c',
                                    'lat_module.c',
                                    'lat_device.c',
                                    'lat_workflow.c',
                                    'lat_inifile_parser.c',
                                    'lat_iniconfig_sched.c',
                                    'lat_host_sched.c'],
                           extra_compile_args=['-I../include/'])

setup (name='LibAnalyzeThis',
       version = '1.0',
       description = 'AnalyeThis Scheduling Module',
       ext_modules=[py_lat_module])
