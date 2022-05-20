/*******************************************************************************
 *                                                                             *
 *  This code is a C++ implementation based on Offenberg et al 2005 algorithim *
 *  to perform memory efficent up the ramp group sampling for PRIME.           *
 *                                                                             *
 *  reference:                                                                 *
 *   Memory-Effifient Up-the-Ramp Processing with Cosmic-Ray Rejection         *
 *   J. D. Offenberg, D. J. Fixen and J. C. Mather                             *
 *   The Publications of the Astronomical Society of                           *
 *   the Pacific, Volume 117, Issue 827, pp. 94-103, January 2005.             *
 *                                                                             *
 *  Usage:                                                                     *
 *    ./Up-the-Ramp_final_icc -input /home/prime/Data/refcor/0001C1            *
 *       /home/prime/Data/refcor/0002C1 /home/prime/Data/refcor/0003C1         *
 *       -output /home/prime/Data/ramp/0001C1                                  *
 *                                                                             *
 *                                                                             *
 *  Iona Kondo and Gregory Mosby 14/12/2020                                                      *
 *                                                                             *
 *  Last Modified                                                              *
 *  -------------                                                              *
 *     07/10/2021                                                              *
 *                                                                             *
 ******************************************************************************/

#include<stdio.h>                                                           
#include<math.h>
#include<stdlib.h> // malloc
#include<time.h>
#include<sys/time.h>
#include "include.h"
#include "boolean.h"
#include "options.h"
#include "quicksort.h"
#include "fitsimage.h"
#include "sstring.h"


//#define B 2                   //Nummber of shift bits //Noise bits to save
#define C 5                     //Cutoff/Gain //Glitch Cutoff/Gain
#define E 1125                  //2*C*readvar/Gain //2C*V**2/G
#define F 65535                 //Full Well //Full-well (saturation)cutoff
#define G 2                     //Gain e/count //Detector Gain
//#define N 25                  //Num Dat 1024**2 //Number of consecutive good intervals (current “winning streak”)
#define N 524288                //Num Dat 128*4096 for an output
//#define I 0x1000000           //For inc of n,m
//#define L 0xFFFFFF            //Low 24 bits
//#define W 0x1000001           //Init weight
//#define A (z&0xFFFF0000)      //Mask for A
//#define Z (z&0xFFFF)                             //Mask for Z
#define LOOP for(P=M,D=*ds++;P<Q;P++)              //Standard loop
struct {float w,s,t,z,a; int n,m;} M[N], *P, *Q;   //External Memory
float **ds; float *D;                              //Input Data
void Integrate(int nramp,float *S,float *V) ;      //Samples, Out, Variance

int
main(int argc, char* argv[])
{
  // Load program parameters from commnd line and parameter file
  OptionSet parameter(argc, argv);
  // String subname = parameter.getOption("input", 1, "Ramp_imput");  //0001C1
  String subname[3]; 
  subname[1] = parameter.getOption("input", 1, "Ramp_imput1");  //0001C1
  subname[2] = parameter.getOption("input", 2, "Ramp_imput2");  //0002C1
  subname[3] = parameter.getOption("input", 3, "Ramp_imput3");  //0003C1
  FitsImage work;  //fitssubtract.cpp
  int nramp = 3;
  float *S,*V, *S0, *V0; //S and V are int pointers to estimated signal and variance array.

  //ALlocate memory for ds
  float **ds0 = (float**)malloc(sizeof(float*)*nramp);  //number of samples 
  for(int p=0;p<nramp;p++){ds0[p] = (float*)malloc(sizeof(float)*N);}  //number of pixels

  //ALlocate memory for S and V
  S0 = (float*)malloc(sizeof(float)*N);  //number of pixels per sample/frame
  V0 = (float*)malloc(sizeof(float)*N);  //number of pixels per sample/frame
 
  //make output fits file
  String outname  = parameter.getOption("output", 1, "Ramp_output"); //0001C1
  String outfile  = outname + ".fit.ramp";
  //cout << "Up-the-ramp output file: " << outfile << endl;
  FitsImage out;
  out.resize(4096,4096);      

  for(int nsub= 0; nsub<32;nsub++){//end of subframe for loop   
    for(int n=1; n<=nramp;n++){
      int ndata =0;
      //String filename = subname + num_to_str(n) + "-" + num_to_str(nsub) + ".fit.refcor";
      String filename = subname[n]  + "-" + num_to_str(nsub) + ".fit.refcor"; //0001C1-0.fit.refcor
      work.read(filename);
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

    for (int i = 0; i<128; ++i) { 
      for (int j = 0; j <4096; ++j) {
        //Shift output S right by number of noise bits, B
        /////out.assign(i, j, *S++);
        int ix = i + nsub*128;
        int jy = j;
        out.assign(ix, jy, *S++);
        //*V++;
      }
    }
    out.create(outfile); 
    out.write(); 
    out.close();
  }//end of subframe for loop 

  free(S0);
  free(V0);
  for(int i=0; i< nramp; ++i){free(ds0[i]);}
  free(ds0);

}

void Integrate(int nramp,float *S,float *V){                //Samples, Out, Variance
int m,n; float e,x,y,w,s,t,z,a,r; Q=M+N;                    //Registers
LOOP{P->t=P->z=*D++; P->s=P->w=P->a=0;P->m=P->n=0;}         //1st Sample
while(--nramp)LOOP{if((r=*D++)<F){z=P->z;                   //Next sample, not full
    x=(r-z); y=P->s/((w=P->w)?P->w:1);e=x-y;n=P->n;m=P->m;  //Calc err
    if(e*e<C*y+E){n+=1;m+=1;P->a+=r-z;                      //Update n,m,a
        P->w+=n*(n+1)/2.0 ;P->s+=n*r-(t=P->t);              //Update W,S
        z=r; t=t+r; }                                       //Update z,t
    else{if(m<=1){P->w=1;P->s=x;m=1;n=1;P->a=x;t=r+z;z=r;}  //Begin again
        else{n=0;z=r;t=r;}}} else{n=0;z=r;t=r;}             //Bad or full, restart Int
    P->t=t; P->z=z ;P->n=n;P->m=m;}                         //Finish Update n,T,A,Z
LOOP{w=P->w?P->w:1;                                         //unpack
    *S++=x=P->s*(4*E+P->a)/(P->m*P->s+4*w*E);               //Optimum estimate
    *V++=E/(w*G)+x/(P->m*G);}}                              //Variance estimate

void Integrate_Offenberg2005(int n,int *S,int *V){  //Samples, Out, Variance
int e,m,r,t,x,z; Q=M+N;                             //Registers
LOOP{P->t=P->z=*D++; P->s=P->w=0;}                  //1st Sample
while(--n)LOOP{if((r=*D++)<F){z=P->z;               //Next sample, not full
    e=(x=(r-Z))-(t=P->s/((m=P->w)?m&L:1));          //Calc err
    if(e*e<C*t+E){m=((t=P->t+I)>>24);               //Good? Update n
        P->w+=I+(m*(m+1)>>1); P->s+=m*r-(t&L);}     //Update m,W,S
    else{if(m<=W){P->w=W; P->s=x; t=I+Z; z=0;}      //Begin again
        else x=t=0;}} else x=t=0;                   //Bad or full, restart Int
    P->t=t+r; P->z=A+(x<<16)+r;}                    //Finish Update n,T,A,Z
LOOP{t=P->w?P->w:W; m=t>>24; t&=L; z=P->z>>16;      //unpack
    *S++=x=P->s*((E*4+z)<<B)/(m*P->s+t*E*4);        //Optimum estimate
    *V++=(E<<2*B)/(t*G)+(x<<B)/(m*G);}}             //Variance estimate



