CFLAGS=-I../inc -I../src -g
all: keyval prot_client

keyval: ../src/param.c ../src/keyval.c ../src/protocol.c nullclient.c nullcmd.c netlog.c testutil.c
prot_client: ../src/param.c ../src/keyval.c ../src/network.c ../src/protocol.c ../src/keyval_cmds.c netlog.c testutil.c
