all: lat_module python_module

python_module: setup.py pythonSched.c
	python setup.py build_ext --inplace

lat_module: lat_module.c lat_workflow.c
	gcc -I../include/ -c lat_module.c lat_workflow.c
	ld -r lat_module.o lat_workflow.o -o lat.o
