#include<stdio.h>                                                           
#include<math.h>

#define B 2                       //Nummber of shift bits //Noise bits to save
#define C 5                       //Cutoff/Gain //Glitch Cutoff/Gain
#define E 2250                    //Readout noise// 2*C*readvar/Gain //2C*V**2/G
#define F 32000                   //Full Well //Full-well (saturation)cutoff
#define G 2                       //Gain e/count //Detector Gain
//#define N 1048576               /Num Dat 1024**2 
#define N 524288                  //Num Dat 128*4096 for an output
#define I 0x1000000               //For inc of n,m
#define L 0xFFFFFF                //Low 24 bits
#define W 0x1000001               //Init weight
#define A (z&0xFFFF0000)          //Mask for A
#define Z (z&0xFFFF)              //Mask for Z
#define LOOP for(P=M,D=*ds++;P<Q;P++)           //Standard loop
struct {long w,s,t,z;} M[N], *P, *Q;            //External Memory
extern int**ds; int *D;                         //Input Data

void Integrate(int n,int *S,int *V){            //Samples, Out, Variance
int e,m,r,t,x,z; Q=M+N;                         //Registers
LOOP{P->t=P->z=*D++; P->s=P->w=0;}               //1st Sample
while(--n)LOOP{if((r=*D++)<F){z=P->z;           //Next sample, not full
    e=(x=(r-Z))-(t=P->s/((m=P->w)?m&L:1));       //Calc err
    if(e*e<C*t+E){m=((t=P->t+I)>>24);           //Good? Update n
        P->w+=I+(m*(m+1)>>1); P->s+=m*r-(t&L);} //Update m,W,S
    else{if(m<=W){P->w=W; P->s=x; t=I+Z; z=0;}  //Begin again
        else x=t=0;}} else x=t=0;               //Bad or full, restart Int
    P->t=t+r; P->z=A+(x<<16)+r;}                //Finish Update n,T,A,Z
LOOP{t=P->w?P->w:W; m=t>>24; t&=L; z=P->z>>16;  //unpack
    *S++=x=P->s*((E*4+z)<<B)/(m*P->s+t*E*4);    //Optimum estimate
    *V++=(E<<2*B)/(t*G)+(x<<B)/(m*G);}}         //Variance estimate


