
import sys, os.path

cwd = os.path.abspath(os.path.curdir)
abspath = os.path.join(cwd, '../src')
print "Src path: %s\n" % abspath
sys.path.append(abspath);

import py_lat_module

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
rc = py_lat_module.lat_device_sched_task()
if (rc != 0):
    print "ERROR: lat_device_sched_task() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

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
(rc, output_file) = py_lat_module.lat_meta_sched_workflow("dummy_input")
if (rc != 0):
    print "ERROR: lat_meta_sched_workflow() failed (ret: %d)\n" % rc
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

