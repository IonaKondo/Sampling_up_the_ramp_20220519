#ifndef FITSIMAGE_H
#define FITSIMAGE_H

#include <cmath>

#include "fitsio2.h"
//#include "fitsio.h"

#include "boolean.h"
#include "sstring.h"
#include "xtreme.h"

// Define image pixel data to be of this type
typedef float ImType;

// We need these FITSIO macros
const int datatype = TFLOAT;
const int bitpix   = FLOAT_IMG;

// Function to return nearest integer to floating value
inline ImType nint(ImType value)
{
  int ipart = (int)value;
  ImType fpart = value - ipart;

  if (fpart <= -0.5) 
    ipart--;
  else if (fpart >= 0.5) 
    ipart++;

  return (ImType)ipart;
}

class FitsImage {

  /* Simple class to function as a wrapper for fitsio. */

 public:
  
  FitsImage(void);
  void resize(int sizex, int sizey);

  // Pixel access with range checking
  ImType value(int x, int y);
  void assign(int x, int y, ImType value);

  // Dimension information
  void size(int& sizex, int& sizey);
  int num_pixels(void);

  ImType* data_table(void);

  ~FitsImage(void);

  /* FITS file handling routines */

  // Open a FITS file for read only and gobble up the data
  bool read(const String fname);

  // Create a new FITS file for writing
  bool create(const String fname);
  bool create16(const String fname);
  bool create_blank_file(const String fname); // Added by A.Fukui

  // Check for potential data conversion problems
  void conv_check(void);
  void conv_check2(void);

  // Blot out pixels outside the given range
  int clean(ImType low, ImType high);

  // Header writing routines
  bool write_time(void);
  bool write_comment(const String comment);
  bool write_history(const String history);

  // Write current data to current FITS file
  bool write(void);

  // Copy header information from named file and write to current FITS
  // file that has been opened for writing
  bool copyheader(String fname);

  // Read value associated with FITS keyword
  bool get_key_value(String key, int&    kvalue);
  bool get_key_value(String key, double& kvalue);
  bool get_key_value(String key, String& kvalue);
  
  bool set_key_value(String key, double kvalue, String comment);
  bool set_key_value(String key, int kvalue, String comment);
  bool set_key_value(String key, String kvalue, String comment);

  // Close the current fitsfile
  bool close(void);

  // Operators on images
  friend void add(FitsImage& image1, FitsImage& image2);
  friend void subtract(FitsImage& image1, FitsImage& image2);
  friend void divide(FitsImage& image1, FitsImage& image2);
  friend void imcopy(FitsImage& image1, FitsImage& image2);

 protected:

  // Pixel data parameters
  int nPixx, nPixy, nPixels;
  ImType *buffer;
  ImType nullvalue;

 private:

  // If possible, always record the JD at the start and end of the
  // exposure
  double JDstart, JDend;

  // cfitsio file pointer
  fitsfile *fptr;

  // Name of file associated with fptr
  String filename;

  // Set this flag true if data is to be written as short integer
  bool bpp16;

};

bool report_error(int status, const String message);

#endif
