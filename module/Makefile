# Makefile for DIP programming environment
#
#

# GNU compilers, flags
CPP = g++ -O3
CFLAGS = -Wall -pedantic -Wno-deprecated
LIBS = -lcfitsio -lm 

# Paths for includes and libraries
INCP = -I/usr/local/include 
LIBP = -L/usr/local/lib 

# Locally compiled modules
OBJS = spline3.o sstring.o iastring.o options.o textfile.o fitsimage.o solve.o functions.o 

all : $(OBJS)

clean :
	rm -f $(OBJS)

# Modules compiled and linked separately
sstring.o : sstring.cpp sstring.h
	${CPP} $(CFLAGS) -c sstring.cpp $(INCP)

iastring.o : iastring.cpp iastring.h
	${CPP} $(CFLAGS) -c iastring.cpp $(INCP)

options.o : options.cpp options.h
	${CPP} $(CFLAGS) -c options.cpp $(INCP)

textfile.o : textfile.cpp textfile.h
	${CPP} $(CFLAGS) -c textfile.cpp $(INCP)

fitsimage.o : fitsimage.cpp fitsimage.h
	${CPP} $(CFLAGS) -c fitsimage.cpp $(INCP)

solve.o : solve.cpp solve.h
	${CPP} $(CFLAGS) -c solve.cpp $(INCP)

functions.o : functions.cpp functions.h
	${CPP} $(CFLAGS) -c functions.cpp $(INCP)

psffit.o : psffit.cpp psffit.h
	${CPP} $(CFLAGS) -c psffit.cpp $(INCP)

spline3.o : spline3.cpp spline3.h
	${CPP} $(CFLAGS) -c spline3.cpp $(INCP)

