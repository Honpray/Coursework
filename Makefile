all:
#	gcc -o test test.c $(shell /usr/bin/python3.5-config --cflags) $(shell /usr/bin/python3.5-config --ldflags) 
	gcc -o bb-cli bb-cli.c -Wall -lreadline
