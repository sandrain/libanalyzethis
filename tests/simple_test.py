
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

print "Calling lat_device_sched_init()..."
rc = py_lat_module.lat_device_sched_init()
if (rc != 0):
    print "ERROR: lat_device_sched_init() failed (ret: %d)\n" % rc
print "Success.\n"

print "Calling lat_host_sched_init()..."
rc = py_lat_module.lat_host_sched_init()
if (rc != 0):
    print "ERROR: lat_host_sched_init() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_meta_sched_init()..."
rc = py_lat_module.lat_meta_sched_init()
if (rc != 0):
    print "ERROR: lat_meta_sched_init() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_device_sched_task()..."
core_id = py_lat_module.lat_device_sched_task()
if (rc < 0):
    print "ERROR: lat_device_sched_task() failed (ret: %d)\n" % rc
else:
    print "Success (select core: %d).\n" % core_id

print "Calling lat_host_sched_task()..."
rc = py_lat_module.lat_host_sched_task()
if (rc != 0):
    print "ERROR: lat_host_sched_task() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_host_copy_file()..."
rc = py_lat_module.lat_host_copy_file()
if (rc != 0):
    print "ERROR: lat_host_copy_file() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_host_move_file()..."
rc = py_lat_module.lat_host_move_file()
if (rc != 0):
    print "ERROR: lat_host_move_file() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_meta_sched_task()..."
rc = py_lat_module.lat_meta_sched_task()
if (rc != 0):
    print "ERROR: lat_meta_sched_task() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_meta_sched_workflow()..."
subworkflows = py_lat_module.lat_meta_sched_workflow("dummy_input")
if (subworkflows == None):
    print "ERROR: lat_meta_sched_workflow() failed\n"
else:
    print "Success.\n"

print "Calling lat_meta_sched_finalize()..."
rc = py_lat_module.lat_meta_sched_finalize()
if (rc != 0):
    print "ERROR: lat_meta_sched_finalize() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_host_sched_finalize()..."
rc = py_lat_module.lat_host_sched_finalize()
if (rc != 0):
    print "ERROR: lat_host_sched_finalize() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Calling lat_device_sched_finalize()..."
rc = py_lat_module.lat_device_sched_finalize()
if (rc != 0):
    print "ERROR: lat_device_sched_finalize() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

print "Finalizing the module..."
rc = py_lat_module.lat_module_finalize ()
if (rc != 0):
    print "ERROR: lat_module_finalize() failed (ret: %d)" % rc
print "Success.\n"
