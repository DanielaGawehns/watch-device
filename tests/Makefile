CFLAGS=-I../inc -I../src -g
LDLIBS=-lssl -lcrypto -lsqlite3
all: keyval prot_client

keyval: ../src/param.c ../src/keyval.c ../src/protocol.c nullclient.c nullcmd.c netlog.c testutil.c
prot_client: ../src/param.c ../src/keyval.c ../src/network.c ../src/protocol.c ../src/keyval_cmds.c ../src/netssl.c ../src/sqlite_db.c netlog.c testutil.c
