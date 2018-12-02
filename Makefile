all:
#	gcc -o test test.c $(shell /usr/bin/python3.5-config --cflags) $(shell /usr/bin/python3.5-config --ldflags) 
cli:
	gcc -o bb_cli bb_cli.c -Wall -lreadline -levent
svr:
	gcc -o bb_svr bb_svr.c -Wall -lreadline -levent

