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

ReferencePixelCorrect : ReferencePixelCorrect.cpp $(OBJS)
	${CPP} $(CFLAGS) -o ReferencePixelCorrect ReferencePixelCorrect.cpp $(MODS)

ReferencePixelCorrect_iona_omp : ReferencePixelCorrect_iona_omp.cpp $(OBJS)
	${CPP} $(CFLAGS) -o ReferencePixelCorrect_iona_omp ReferencePixelCorrect_iona_omp.cpp $(MODS)

ReferencePixelCorrect_iona_test : ReferencePixelCorrect_iona_test.cpp $(OBJS)
	${CPP} $(CFLAGS) -o ReferencePixelCorrect_iona_test ReferencePixelCorrect_iona_test.cpp $(MODS)

Reference_pixel_correction_final : Reference_pixel_correction_final.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Reference_pixel_correction_final Reference_pixel_correction_final.cpp $(MODS)

Up-the-Ramp_test : Up-the-Ramp_test.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Up-the-Ramp_test Up-the-Ramp_test.cpp $(MODS)

Up-the-Ramp_test3 : Up-the-Ramp_test3.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Up-the-Ramp_test3 Up-the-Ramp_test3.cpp $(MODS)

SampleProgram3_20201210 : SampleProgram3_20201210.cpp $(OBJS)
	${CPP} $(CFLAGS) -o SampleProgram3_20201210 SampleProgram3_20201210.cpp $(MODS)

SampleProgram3G_20201210 : SampleProgram3G_20201210.cpp $(OBJS)
	${CPP} $(CFLAGS) -o SampleProgram3G_20201210 SampleProgram3G_20201210.cpp $(MODS)

SampleProgram4_20201212 : SampleProgram4_20201212.cpp $(OBJS)
	${CPP} $(CFLAGS) -o SampleProgram4_20201212 SampleProgram4_20201212.cpp $(MODS)

SampleProgram4test_20201212 : SampleProgram4test_20201212.cpp $(OBJS)
	${CPP} $(CFLAGS) -o SampleProgram4test_20201212 SampleProgram4test_20201212.cpp $(MODS)

SampleProgram4_omp : SampleProgram4_omp.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram4_omp SampleProgram4_omp.cpp $(MODS)

SampleProgram5 : SampleProgram5.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram5 SampleProgram5.cpp $(MODS)

SampleProgram5_double : SampleProgram5_double.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram5_double SampleProgram5_double.cpp $(MODS)

SampleProgram5_wobit : SampleProgram5_wobit.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram5_wobit SampleProgram5_wobit.cpp $(MODS)

SampleProgram6 : SampleProgram6.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram6 SampleProgram6.cpp $(MODS)

SampleProgram7 : SampleProgram7.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram7 SampleProgram7.cpp $(MODS)


SampleProgram9 : SampleProgram9.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram9 SampleProgram9.cpp $(MODS)

Up-the-ramp_float : Up-the-ramp_float.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o Up-the-ramp_float Up-the-ramp_float.cpp $(MODS)


Up-the-ramp_float_test : Up-the-ramp_float_test.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o Up-the-ramp_float_test Up-the-ramp_float_test.cpp $(MODS)



SampleProgram9.int : SampleProgram9.int.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram9.int SampleProgram9.int.cpp $(MODS)

SampleProgram10_testPALA : SampleProgram10_testPALA.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram10_testPALA SampleProgram10_testPALA.cpp $(MODS)

SampleProgram10_testPALA_test : SampleProgram10_testPALA_test.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o SampleProgram10_testPALA_test SampleProgram10_testPALA_test.cpp $(MODS)

Up-the-Ramp_final_test : Up-the-Ramp_final_test.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o Up-the-Ramp_final_test Up-the-Ramp_final_test.cpp $(MODS)


Up-the-Ramp_final_icc : Up-the-Ramp_final_icc.cpp $(OBJS)
	${CPP} $(CFLAGS) $(OMP) -o Up-the-Ramp_final_icc Up-the-Ramp_final_icc.cpp $(MODS)

Up-the-Ramp_iona : Up-the-Ramp_iona.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Up-the-Ramp_iona Up-the-Ramp_iona.cpp $(MODS)

Up-the-Ramp_iona_omp : Up-the-Ramp_iona_omp.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Up-the-Ramp_iona_omp Up-the-Ramp_iona_omp.cpp $(MODS)

Up-the-Ramp_iona_4k4k : Up-the-Ramp_iona_4k4k.cpp $(OBJS)
	${CPP} $(CFLAGS) -o Up-the-Ramp_iona_4k4k Up-the-Ramp_iona_4k4k.cpp $(MODS)

Up-the-Ramp_iona : Up-the-Ramp_iona.cpp $(OBJS)
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
