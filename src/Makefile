# Makefile for DIP programming environment
#
#

# GNU compilers, flags
CPP = g++ -O3
CFLAGS = -Wall -pedantic -Wno-deprecated
LIBS = -lcfitsio -lm 

# openMP
#OMP = -fopenmp -std=c++11

# Paths for includes and libraries
INCP = -I/usr/local/include -I../module 
LIBP = -L/usr/local/lib 

# Locally compiled modules
OBJS_DIR = ../module
OBJS_FILE = spline3.o sstring.o iastring.o options.o fitsimage.o
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_FILE))

# All required modules
MODS = $(INCP) $(LIBP) $(OBJS) $(LIBS)

BINS = fitscombine fitsflatten fitsmkresponse fitsJD fitsrewrite fitsreduce16 fitsreduce162 fitssubtract fitsdivide fitssubframe badpixmask fitspsfcentre fitsheader cut_image resample fitsaverage

BINDIR = ../../bin

all : $(BINS)

install:
	cp $(BINS) $(BINDIR)

# This program just tests certain features of newly constructed classes
fitspsfcentre : fitspsfcentre.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitspsfcentre fitspsfcentre.cpp $(MODS)

badpixmask : badpixmask.cpp $(OBJS)
	${CPP} $(CFLAGS) -o badpixmask badpixmask.cpp $(MODS)

fitsgluesubframe : fitsgluesubframe.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsgluesubframe fitsgluesubframe.cpp $(MODS)

fitsgluesubframe_test : fitsgluesubframe_test.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsgluesubframe_test fitsgluesubframe_test.cpp $(MODS)


fitssubframe : fitssubframe.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitssubframe fitssubframe.cpp $(MODS)

checkimage : checkimage.cpp $(OBJS)
	${CPP} $(CFLAGS) -o checkimage checkimage.cpp $(MODS)

fitsdivide : fitsdivide.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsdivide fitsdivide.cpp $(MODS)

fitssubtract : fitssubtract.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitssubtract fitssubtract.cpp $(MODS)

fitscombine : fitscombine.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitscombine fitscombine.cpp $(MODS)

Reference_pixel_correction_final : Reference_pixel_correction_final.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Reference_pixel_correction_final Reference_pixel_correction_final.cpp $(MODS)


Up-the-Ramp_final_icc : Up-the-Ramp_final_icc.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o Up-the-Ramp_final_icc Up-the-Ramp_final_icc.cpp $(MODS)

tests: Reference_pixel_correction_final Up-the-Ramp_final_icc

fitsmkresponse : fitsmkresponse.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsmkresponse fitsmkresponse.cpp $(MODS)

fitsflatten : fitsflatten.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsflatten fitsflatten.cpp $(MODS)

fitsJD : fitsJD.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsJD fitsJD.cpp $(MODS)

fitsrewrite : fitsrewrite.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsrewrite fitsrewrite.cpp $(MODS)

fitsreduce16 : fitsreduce16.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsreduce16 fitsreduce16.cpp $(MODS)

fitsreduce162 : fitsreduce162.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsreduce162 fitsreduce162.cpp $(MODS)

fitsheader : fitsheader.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsheader fitsheader.cpp $(MODS)

cut_image : cut_image.cpp $(OBJS)
	${CPP} $(CFLAGS) -o cut_image cut_image.cpp $(MODS)

resample : resample.cpp $(OBJS)
	${CPP} $(CFLAGS) -o resample resample.cpp $(MODS)

fitsaverage : fitsaverage.cpp $(OBJS)
	${CPP} $(CFLAGS) -o fitsaverage fitsaverage.cpp $(MODS)

##fukuisann
#resample : resample.cpp $(OBJS)
#        ${CPP} $(CFLAGS) -o resample resample.cpp $(MODS)
#fitsaverage : fitsaverage.cpp $(OBJS)
#	${CPP} $(CFLAGS) -o fitsaverage fitsaverage.cpp $(MODS)

# Modules compiled and linked separately
sstring.o : sstring.cpp sstring.h
	${CPP} $(CFLAGS) -c sstring.cpp $(INCP)

iastring.o : iastring.cpp iastring.h
	${CPP} $(CFLAGS) -c iastring.cpp $(INCP)

options.o : options.cpp options.h
	${CPP} $(CFLAGS) -c options.cpp $(INCP)

fitsimage.o : fitsimage.cpp fitsimage.h
	${CPP} $(CFLAGS) -c fitsimage.cpp $(INCP)

clean :
	rm -f $(BINS) $(OBJS)
