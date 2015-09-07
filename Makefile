CPPFLAGS=-Wall
EXEC=pl0_parser
all:${EXEC}
pl0_parser : pl0_rdp.o
	g++ -o $@ $^  ${CPPFLAGS}

%.o : %.cpp
	g++ -c ${CFLAGS} ${CPPFLAGS} $< -o $@

.PHONY=clean run

run:
	./${EXEC} < good.pl0

clean:
	rm -f pl0_parser pl0_rdp.o


