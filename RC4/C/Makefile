GCC		= gcc -Wall -Wextra
SOURCES 	= main.c rc4.c
HEADERS		= rc4.h
OBJECTS		= main.o rc4.o
EXECBIN		= rc4

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} ${OBJECTS} -o ${EXECBIN}
	chmod +x ${EXECBIN}

%.o :%.c
	${GCC} -c $<

clean :
	-rm ${OBJECTS}

spotless : clean
	-rm ${EXECBIN}
