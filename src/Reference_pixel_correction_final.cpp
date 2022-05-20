 /*******************************************************************************
 *                                                                              *
 *  Reference_pixel_correction_final.cpp                                        *
 *                                                                              *
 *  1. Divide 4096x4096 image into 32 128x4096 subframes                        *
 *  2. Do reference pixel correction                                            *
 *     Take a median of the top four rows of an HxRG image                      *
 *     for each output channel (4 rows x 128 columns in 32 channel mode)        *
 *     Then subtracting that median from all the pixels in that output channel. * 
 *                                                                              *
 *  Iona Kondo 05/12/2020                                                       *
 *                                                                              *
 *  Last Modified                                                               *
 *  -------------                                                               *
 *       07.10.2021 by Kondo                                                    *
 *                                                                              *
 *                                                                              *
 *******************************************************************************/

#include "include.h"
#include "fitsimage.h"
#include "quicksort.h"
#include "boolean.h"
#include "options.h"
#include "sstring.h"

int maximam(int a, int b);
int minimam(int a, int b);

int
main(int argc, char* argv[]){

  // Load program parameters from commnd line and parameter file
  OptionSet parameter(argc, argv);

  String filename = parameter.getOption("frame", 1, "");
//  String filenameR = parameter.getOption("frameR", 1, "");
  FitsImage image;
  
  //cout << "# Reading Raw Image " << filename << endl; 
  //cout << "# Loading " << filename << endl;
//  cout << "# Loading " << filenameR << endl;
  int Rmode1 = parameter.getOption("Rmode", 1, 0); //1. Top, 2. Bottom, 3. Top and Bottom
  int Rmode2 = parameter.getOption("Rmode", 2, 0); //1. average, 2. median
  //cout << "# Loading Mode of Reference Pixel Correction Rmode1= " <<Rmode1 << " Rmode2= " << Rmode2 << endl; 


  image.read(filename);
  image.close();

  int sizex, sizey;
  image.size(sizex, sizey);

  int nsubf = 0;
  FitsImage out;

  String key = "subframe" + num_to_str(nsubf);
  String outname;

  while(parameter.checkSwitch(key)){

    int x1 = parameter.getOption(key, 1, 0);
    int x2 = parameter.getOption(key, 2, sizex);
    int y1 = parameter.getOption(key, 3, 0);
    int y2 = parameter.getOption(key, 4, sizey);

    x1 = maximum(x1, 0);
    x2 = minimum(x2, sizex);
    y1 = maximum(y1, 0);
    y2 = minimum(y2, sizey);

    //cout << "# " << key << " " << x1 << " " << x2 << " " << y1 << " " << y2  << endl;

    out.resize(x2-x1, y2-y1);

    //---take median and average ---------------------------------------------
    int height = 4; //PRIME H4RG 
    int width = 128; //PRIME H4RG
    int numUse;
    if(Rmode1 < 2){
       numUse = height * width; //top or bottom
    }else{
       numUse = 2*height * width; // top and bottom 
    }
    int mid = numUse / 2;
    int ndata = 0;
    float sum = 0.0;
    float average;
    float median;
    float *data = new float[numUse];

    for(int ix = x1; ix < x1+width; ix++){
     if(Rmode1==1 || Rmode1==3) {
     for(int iy = y1; iy < y1+height; iy++){
      data[ndata] = image.value(ix, iy);
      sum += data[ndata];  
      ++ndata;
     }}

     if(Rmode1==2 || Rmode1==3) {
     for(int iy = y2-height; iy < y2; iy++){
      data[ndata] = image.value(ix, iy);
      sum += data[ndata];  
      ++ndata;
    }} }


      average = sum/numUse;
      QuickSort(data, 0, numUse - 1, true);
      ImType medvalue1 = (ImType)data[mid];
      ImType medvalue2 = (ImType)data[mid-1];  //top or bottom
      median  = (medvalue1+ medvalue2)/2.0;
      //cout << "# Calculated average value is  " << average << " ";
      //cout << "# Calculated median  value is  " << median << " ";

     delete[] data; 

//---subtract average/median value---------------------------------------------

    for(int ix = x1; ix < x2; ix++){
    for(int iy = y1; iy < y2; iy++){
      ImType value ;
      if(Rmode2 == 0){ //average
      //ImType value = image.value(ix, iy)-average;
      value = image.value(ix, iy)-average;
      }else{ //median
      //ImType value = image.value(ix, iy)-median;
      value = image.value(ix, iy)-median;
      }
      out.assign(ix-x1, iy-y1, value);

    }}

      outname = parameter.getOption("out", 1, "subframe");
      //outname = outname + "-" + num_to_str(nsubf) + ".fit";
      outname = outname + "-" + num_to_str(nsubf) + ".fit.ref.test";
      //outname = outname + "-" + num_to_str(nsubf) + ".fit.ref";
      out.create(outname);

    // Write resulting image
    //cout << "# Writing Reference Pixel Corrected Image to " << outname << endl; 
    out.write();
    out.close();

    nsubf++;
    key = "subframe" + num_to_str(nsubf);

  }

  return 0;

}

int maximam(int a, int b){

  if(a > b){
    return a;
  }else{
    return b;
  }

}

int minimam(int a, int b){

  if(a > b){
    return b;
  }else{
    return a;
  }

}
