all: lat_module python_module

python_module: setup.py pythonSched.c
	python setup.py build_ext --inplace

lat_module: lat_module.c lat_workflow.c lat_inifile_parser.c lat_debug.c lat_iniconfig_sched.c lat_device.c
	gcc -c lat_debug.c
	gcc -I../include/ -c lat_module.c lat_workflow.c lat_iniconfig_sched.c lat_inifile_parser.c lat_device.c
	ld -r lat_module.o lat_workflow.o lat_iniconfig_sched.o lat_inifile_parser.o lat_device.o -o lat.o

clean:
	rm -f py_lat_module.so
