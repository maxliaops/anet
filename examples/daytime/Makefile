CC = cc
CFLAGS = -I../../anet

PROGS =	server1 client1

CLEANFILES = *.o 


all:	${PROGS}

server1:	server1.o
		${CC} ${CFLAGS} -o $@ server1.o ../../anet/libanet.a

client1:	client1.o
		${CC} ${CFLAGS} -o $@ client1.o ../../anet/libanet.a

clean:
		rm -f ${PROGS} ${CLEANFILES}