all:
	gcc -o pygsheets_embed pygsheets_embed.c $(shell /usr/bin/python2.7-config --cflags) $(shell /usr/bin/python2.7-config --ldflags) 
cli:
	gcc -g -o cli bb_cli.c -Wall -lreadline -levent
svr:
	gcc -g -o svr bb_svr.c -Wall -lreadline -levent

