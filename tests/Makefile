all: test_parse_inifile

test_parse_inifile: test_parse_inifile.c
	gcc -I../include/ -I../src/ test_parse_inifile.c ../src/lat_inifile_parser.o ../src/lat_debug.o -o test_parse_inifile

clean:
	rm -f test_parse_inifile
