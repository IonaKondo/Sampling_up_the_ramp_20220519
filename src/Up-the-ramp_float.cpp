//-----------------------------
// Usage: 
//   ./Up-the-ramp_float -frame (input fitsfile1) (input fitsfile2) (input fitsfile3)  -out (output fitsfile)

//   ./Up-the-ramp_float -frame ../tests/input/db_make_fits21.fit ../tests/input/db_make_fits22.fit ../tests/input/db_make_fits23.fit -out ../tests/output/output_float.fits
//
// Compile: 
//   g++ -O3 -Wall -pedantic -Wno-deprecated -fopenmp -std=c++11 -o Up-the-ramp_float Up-the-ramp_float.cpp -I/usr/local/include -I../module  -L/usr/local/lib  ../module/spline3.o ../module/sstring.o ../module/iastring.o ../module/options.o ../module/fitsimage.o -lcfitsio -lm
//
//-----------------------------

#include<stdio.h>                                                           
#include<math.h>
#include<stdlib.h> // malloc
#include<time.h>
#include <sys/time.h>

#include "include.h"
#include "boolean.h"
#include "options.h"
#include "quicksort.h"
#include "fitsimage.h"
#include "sstring.h"


//#define B 2                       //Nummber of shift bits //Noise bits to save
#define C 5                       //Cutoff/Gain //Glitch Cutoff/Gain
#define E 2250                    //2*C*readvar/Gain //2C*V**2/G
#define F 32000                   //Full Well //Full-well (saturation)cutoff
#define G 1                       //Gain e/count //Detector Gain
//#define N 25                 //Num Dat 1024**2 //Number of consecutive good intervals (current “winning streak”)
#define N 524288                 //Num Dat 128*4096 for an output
//#define I 0x1000000               //For inc of n,m
//#define L 0xFFFFFF                //Low 24 bits
//#define W 0x1000001               //Init weight
//#define A (z&0xFFFF0000)          //Mask for A
//#define Z (z&0xFFFF)              //Mask for Z
#define LOOP for(P=M,D=*ds++;P<Q;P++)           //Standard loop
struct {float w,s,t,z,a; int n,m;} M[N], *P, *Q;            //External Memory
float **ds; float *D;                         //Input Data
void Integrate(int n,float *S,float *V) ;          //Samples, Out, Variance

int
main(int argc, char* argv[])
{
   // Load program parameters from commnd line and parameter file
  OptionSet parameter(argc, argv);

  FitsImage work;  //fitssubtract.cpp
  int nramp = 3;
  float *S,*V, *S0, *V0; //S and V are int pointers to estimated signal and variance array.

  //ALlocate memory for ds
  float **ds0 = (float**)malloc(sizeof(float*)*nramp);  //number of samples
 
  for(int p=0;p<nramp;p++){
    ds0[p] = (float*)malloc(sizeof(float)*N);  //number of pixels
  }

  //ALlocate memory for S and V
  S0 = (float*)malloc(sizeof(float)*N);  //number of pixels per sample/frame
  V0 = (float*)malloc(sizeof(float)*N);  //number of pixels per sample/frame
 

  //Sample for loop
  for(int n=1; n<=nramp;n++){
    int ndata =0;

    //String filename = subname + num_to_str(n) + "-" + num_to_str(nsub) + ".fit.ref";
    String filename = parameter.getOption("frame", n, "");
    work.read(filename);
    cout << "Up-the-ramp input file" << n << ": "  << filename << endl;

    //Fill ds array with data
    for (int i = 0; i < 128; ++i){
      for (int j = 0; j < 4096; ++j){
	      ds0[n-1][ndata] = work.value(i, j);
	      ++ndata;
      }
    }
    work.close();
  }//end of sample for loop


  //Create copies of pointers to increment in integrate function
  ds = ds0;
  S = S0;
  V = V0;

  //Integrate runs on all data in **ds and outputs results to S an V
  Integrate(nramp, S, V); //S and V are already type int*

  //make output fits file
  String outfile  = parameter.getOption("out", 1, "Ramp_output.fit");
  FitsImage out;
  out.resize(128, 4096);
  for (int i = 0; i<128; ++i)  
   for (int j = 0; j <4096; ++j) {
     out.assign(i, j, *S++);
  }
  out.create(outfile); 
  out.write(); 
  out.close();
//}//end of subframe for loop 


  free(S0);
  free(V0);
  for(int i=0; i< nramp; ++i){
    free(ds0[i]);
  }
  free(ds0);

}

void Integrate(int nramp,float *S,float *V){            //Samples, Out, Variance
int m,n;                          //Registers
float e,x,y,w,s,t,z,a,r; Q=M+N;                         //Registers
LOOP{P->t=P->z=*D++; P->s=P->w=P->a=0;P->m=P->n=0;}               //1st Sample
while(--nramp)LOOP{if((r=*D++)<F){z=P->z;           //Next sample, not full
    x=(r-z);       //Calc err
    y=P->s/((w=P->w)?P->w:1);       //Calc err
    e=x-y;       //Calc err
    n=P->n;
    m=P->m;
    if(e*e<C*y+E){
        n+=1;                 //Update n
        m+=1;                 //Update m
        P->a+=r-z;         //Good? Update a
        P->w+=n*(n+1)/2.0 ;   //Update W
        P->s+=n*r-(t=P->t);   //Update S
        z=r;                  //Update z
        t=t+r; }              //Update t
    else{if(m<=1){P->w=1; P->s=x; m=1; n=1;P->a=x; t=r+z; z=r;}  //Begin again
        else{n=0;z=r;t=r;}}} else{n=0;z=r;t=r;}               //Bad or full, restart Int
    P->t=t; P->z=z ;P->n=n;P->m=m;
    }                //Finish Update n,T,A,Z
LOOP{w=P->w?P->w:1; //m=t>>24; t&=L; z=P->z>>16;  //unpack
    *S++=x=P->s*(4*E+P->a)/(P->m*P->s+4*w*E);    //Optimum estimate
    *V++=E/(w*G)+x/(P->m*G);}}         //Variance estimate





