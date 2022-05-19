# Up-Ramp-Group Sampling Code

This code is a C++ implementation of the Offenberg et al 2005 algorithim to perform memory efficent up the ramp group sampling.

## Compilation
This code depends on CFITSIO. Please ensure that CFITSIO is installed to `/usr/local/`.

To compile code with set of sample programs:

```
 cd src
 make tests
```

## Usage
To run a sample program on test data, execute:
```
cd src
./SampleProgram4_20201212 -frame ../tests/input/make_fits11.fits ../tests/input/make_fits12.fits ../tests/input/make_fits13.fits -out ../tests/output/output4.fits

./Up-the-ramp_float -frame (input fitsfile1) (input fitsfile2) (input fitsfile3)  -out (outputS fitsfile) (outputV)
./Up-the-ramp_float -frame ../tests/input/DarkN1-0.fit.ref ../tests/input/DarkN2-0.fit.ref ../tests/input/DarkN3-0.fit.ref -out ../tests/output/output_float_S.fits ../tests/output/output_float_V.fits
```
