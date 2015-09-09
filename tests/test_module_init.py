import sys, os.path

cwd = os.path.abspath(os.path.curdir)
abspath = os.path.join(cwd, '../src')
print "Src path: %s\n" % abspath
sys.path.append(abspath);

import py_lat_module

print "Initializing the module with fake arguments..."
cfg_file = os.path.join(cwd, 'platform_sample.cfg')
print "Using the platform configuration file %s" % cfg_file
rc = py_lat_module.lat_module_init ("verbose", "1", "ini_config_file", cfg_file)
if (rc != 0):
    print "ERROR: lat_module_init() failed (ret: %d)\n" % rc
print "Success.\n"

print "Finalizing the module..."
rc = py_lat_module.lat_module_finalize ()
if (rc != 0):
    print "ERROR: lat_module_finalize() failed (ret: %d)" % rc
print "Success.\n"

