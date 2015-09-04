CFLAGS=
CPPFLAGS=
EXEC=pl0_parser
all:${EXEC}
pl0_parser : pl0_rdp.o
	g++ -o $@ $^ -Wall

%.o : %.cpp
	g++ -c ${CFLAGS} ${CPPFLAGS} $< -o $@

.PHONY=clean
clean:
	rm -f pl0_parser
