all:
#	gcc -o test test.c $(shell /usr/bin/python3.5-config --cflags) $(shell /usr/bin/python3.5-config --ldflags) 
	gcc -o bb_cli bb_cli.c -Wall -lreadline -levent
