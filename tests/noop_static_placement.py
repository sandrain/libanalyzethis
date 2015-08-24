
import sys, os.path

cwd = os.path.abspath(os.path.curdir)
abspath = os.path.join(cwd, '../src')
print "Src path: %s\n" % abspath
sys.path.append(abspath);

import py_lat_module

print "Calling lat_meta_sched_init()..."
rc = py_lat_module.lat_meta_sched_init()
if (rc != 0):
    print "ERROR: lat_meta_sched_init() failed (ret: %d)\n" % rc
print "Success.\n"

# At the moment, we assume that the py_lat_module will always give us the noop
# function for static placement (we do not have the plugin mechanism in place
# yet).
print "Calling the no-op static placement function. No task will be placed, will get the same file as the one passed as input"
sub_workflows = py_lat_module.lat_meta_sched_workflow ("cybershake_60")
if (sub_workflows == None):
    print "ERROR: lat_meta_sched_workflow() failed (%d)\n" % rc
else:
    print "Success."

print "Got %d workflow back:" % (len(sub_workflows))
for i in range(len(sub_workflows)):
    print "\t%d: %s" % (i, sub_workflows[i])

print "Calling lat_meta_sched_finalize()..."
rc = py_lat_module.lat_meta_sched_finalize()
if (rc != 0):
    print "ERROR: lat_meta_sched_finalize() failed (ret: %d)\n" % rc
else:
    print "Success.\n"

