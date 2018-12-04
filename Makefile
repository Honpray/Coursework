all:
	gcc -o pygsheets pygsheets.c $(shell /usr/bin/python2.7-config --cflags) $(shell /usr/bin/python2.7-config --ldflags) 
cli:
	gcc -g -o cli bb_cli.c -Wall -lreadline -levent -lssl -lcrypto
svr:
	gcc -g -o svr bb_svr.c pygsheets.c -Wall -lreadline -levent $(shell /usr/bin/python2.7-config --cflags) $(shell /usr/bin/python2.7-config --ldflags) 


