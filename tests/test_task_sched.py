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

print "Initializing the AFE scheduler..."
rc = py_lat_module.lat_device_sched_init ();
if (rc != 0):
    print "ERROR: lat_device_sched_init() failed (ret: %d)\n" % rc
print "Success.\n";

print "Initializing the host scheduler..."
rc = py_lat_module.lat_host_sched_init ();
if (rc != 0):
    print "ERROR: lat_device_sched_init() failed (ret: %d)\n" % rc
print "Success.\n";

print "Simulating the scheduling of a task on a specific device..."
core_id = py_lat_module.lat_device_sched_task ()
print "Assigned core ID: %d" % core_id

print "Simulating the scheduling of a task on a specific host..."
host_id = py_lat_module.lat_host_sched_task ()
print "Assigned host ID: %d" % host_id

# XXX Finalize the various scheduler

print "Finalizing the module..."
rc = py_lat_module.lat_module_finalize ()
if (rc != 0):
    print "ERROR: lat_module_finalize() failed (ret: %d)" % rc
print "Success.\n"

