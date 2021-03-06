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
(Conduct a reference pixel correction for three raw images, respectively)
./Reference_pixel_correction_final -input ./input/dark_raw1.fit  -output ../output/dark_rc1   -file param-subframe-PRMIE.par -Rmode 1 1 
./Reference_pixel_correction_final -input ./input/dark_raw2.fit  -output ../output/dark_rc2   -file param-subframe-PRMIE.par -Rmode 1 1 
./Reference_pixel_correction_final -input ./input/dark_raw3.fit  -output ../output/dark_rc3   -file param-subframe-PRMIE.par -Rmode 1 1 

(Conduct sampling up-the-ramp using three raw images and obtain one resultant image)
./Up-the-Ramp_final_icc -input ../output/dark_rc1 ../output/dark_rc2 ../output/dark_rc3 -output ../output/dark_ramp1 
```
