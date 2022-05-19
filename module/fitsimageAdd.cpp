#include "fitsimage.h"

FitsImage::FitsImage(void)
{
  nPixx = 0;
  nPixy = 0;
  nPixels = 0;
  buffer = 0;
  nullvalue = 0;
  filename = "";
  bpp16 = false;
}

void FitsImage::resize(int sizex, int sizey)
{
  nPixx = sizex;
  nPixy = sizey;
  nPixels = nPixx * nPixy;
  if (buffer) delete[] buffer;
  buffer = new ImType[nPixels];
  for (int n = 0; n < nPixels; ++n) buffer[n] = 0;
}

ImType FitsImage::value(int x, int y)

  /* Return value at the given pixel location with range checking. */
{
  if (x >= 0 && x < nPixx && y >= 0 && y < nPixy)
    return buffer[nPixx * y + x];
  else
    return nullvalue;
}

void FitsImage::assign(int x, int y, ImType value)

  /* Assign given value at given pixel location with range checking. */
{
  if (x >= 0 && x < nPixx && y >= 0 && y < nPixy)
    buffer[nPixx * y + x] = value;
}

void FitsImage::size(int& sizex, int& sizey)

  /* Get the dimensions of the current image. */
{
  sizex = nPixx;
  sizey = nPixy;
}

int FitsImage::num_pixels(void)

  /* Return the total number of pixels in the image. */
{
  return nPixels;
}

ImType* FitsImage::data_table(void)

  /* return a pointer to the pixel data table. */
{
  return &buffer[0];
}

FitsImage::~FitsImage(void)
{
  //int status;
  //fits_close_file(fptr, &status);
  delete[] buffer;
}

bool FitsImage::read(const String fname)

  /* Open the FITS file on disk for reading and gobble up the pixel
     data. */
{
  filename = fname;

  int status = 0;
  if (fits_open_file(&fptr, filename.c_str(), READONLY, &status))
    return report_error(status, "Problem opening file " + filename);

  // Get image dimensions
  int  nfound;
  long naxes[2];
  if (fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status))
    return report_error(status, "Problem sizing " + filename);

  // Must resize the current image now
  resize((int)naxes[0], (int)naxes[1]);

  // Gobble up the image pixel data
  long firstelem = 1;
  int anynull;
  if (fits_read_img(fptr, datatype, firstelem, nPixels, &nullvalue, 
		buffer, &anynull, &status))
    return report_error(status, "Problem with data on " + filename);

  // Read start and end JDs if they are encoded into the FITS header
  char comment[FLEN_COMMENT];
  if (fits_read_key(fptr, TDOUBLE, "JDSTART", &JDstart, comment, &status))
    JDstart = 0;
  if (fits_read_key(fptr, TDOUBLE, "JDEND", &JDend, comment, &status))
    JDend = 0;

  return true;
}


//--------------------
bool FitsImage::read3d(const String fname)

  /* Open the FITS file on disk for reading and gobble up the pixel
     data. */
{
  filename = fname;

  int status = 0;
  if (fits_open_file(&fptr, filename.c_str(), READONLY, &status))
    return report_error(status, "Problem opening file " + filename);

  // Get image dimensions
  int  nfound;
  long naxes[2];
  if (fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status))
    return report_error(status, "Problem sizing " + filename);

  // Must resize the current image now
  resize((int)naxes[0], (int)naxes[1]);

  // Gobble up the image pixel data
  long firstelem = 1;
  int anynull;
  if (fits_read_img(fptr, datatype, firstelem, nPixels, &nullvalue, 
    buffer, &anynull, &status))
    return report_error(status, "Problem with data on " + filename);

  // Read start and end JDs if they are encoded into the FITS header
  char comment[FLEN_COMMENT];
  if (fits_read_key(fptr, TDOUBLE, "JDSTART", &JDstart, comment, &status))
    JDstart = 0;
  if (fits_read_key(fptr, TDOUBLE, "JDEND", &JDend, comment, &status))
    JDend = 0;

  return true;
}



//-------------------



bool FitsImage::create(const String fname)

  /* Create a new FITS file. If a file has already been opened for
     reading in a given class instance, the file must be closed before
     calling this function. The bits per pixel will be that defined in
     the typedef macro. */
{
  filename = fname;
  int status = 0;

  remove(filename.c_str());

  // First open a blank file
  if (fits_create_file(&fptr, filename.c_str(), &status))
    return report_error(status, "Problem creating file " + filename);
  
  // Create image of type specified by bitpix. CFITSIO will put in a
  // default standard header
  long naxis = 2;
  long naxes[2] = {nPixx, nPixy};
  if (fits_create_img(fptr, bitpix, naxis, naxes, &status))
    return report_error(status, "Problem creating image on " + filename);

  bpp16 = false;
  return true;
}

bool FitsImage::create16(const String fnam)

  /* Create new FITS file with the data table forced to be 16 bits per
     pixel regardless of how the data is represented by the class. */
{
  filename = fnam;
  int status = 0;

  // Delete file if a FITS file with the same name already
  // exists. This effectively overwrites the named file
  remove(filename.c_str());

  // First open a blank file
  if (fits_create_file(&fptr, filename.c_str(), &status))
    return report_error(status, "Problem creating file " + filename);

  // Create image of short signed integer (16bpp). CFITSIO will put in
  // a default standard header
  long naxis = 2;
  long naxes[2] = {nPixx, nPixy};
  if (fits_create_img(fptr, SHORT_IMG, naxis, naxes, &status))
    return report_error(status, "Problem creating image on " + filename);

  bpp16 = true;
  return true;
}

// Added by A.Fukui
bool FitsImage::create_blank_file(const String fname)

  /* Create a new blank FITS file. If a file has already been opened for
     reading in a given class instance, the file must be closed before
     calling this function. The bits per pixel will be that defined in
     the typedef macro. */
{
  filename = fname;
  int status = 0;

  remove(filename.c_str());

  // First open a blank file
  if (fits_create_file(&fptr, filename.c_str(), &status))
    return report_error(status, "Problem creating file " + filename);
  
  bpp16 = false;
  return true;

}

void FitsImage::conv_check(void)

  /* Check data buffer for potential overflow and underflow problems
     if converting data to 16 bpp. Also round off ADUs to nearest
     integer. The contents of the data buffer will be alerted
     irretrievably but will only differ slightly (by < 1ADU) from the
     original. */
{
  for (int n = 0; n < nPixels; ++n) {
    ImType value = buffer[n];
    if (fabs(value) > 32768 || fabs(value) < 0.000001) value = 0;
    buffer[n] = nint(value);
  }
}

// added by kkamiya
/********************************************************************/
void FitsImage::conv_check2(void)

  /* Check data buffer for potential overflow and underflow problems
     if converting data to 16 bpp. Also round off ADUs to nearest
     integer. The contents of the data buffer will be alerted
     irretrievably but will only differ slightly (by < 1ADU) from the
     original. */
{
  for (int n = 0; n < nPixels; ++n) {
    ImType value = buffer[n];
    if (value < 0.000001) value = 0;
    buffer[n] = nint(value);
  }
}
/********************************************************************/

int FitsImage::clean(ImType low, ImType high)
{
  int nblot = 0;
  for (int n = 0; n < nPixels; ++n) {
    ImType value = buffer[n];
    if (value < low || value > high) {
      buffer[n] = 0;
      ++nblot;
    }
  }
  return nblot;
}

bool FitsImage::write_time(void)

  /* Write the start and end JDs of the exposure if defined. */
{
  if (JDstart <= 0 || JDend <= 0) return false;

  int status = 0;
  if (fits_update_key(fptr, TDOUBLE, "JDSTART", &JDstart, 
		      "Start JD of exposure", &status))
    return report_error(status, "Unable to write 'JDstart' in header");

  if (fits_update_key(fptr, TDOUBLE, "JDEND", &JDend, 
		      "End JD of exposure", &status))
    return report_error(status, "Unable to write 'JDstart' in header");

  return true;
}

bool FitsImage::write_comment(const String comment)

  /* Write or append comment keyword. */
{
  int status = 0;
  if (fits_write_comment(fptr, comment.c_str(), &status))
    return report_error(status, "Unable to write comment: " + comment);

  return true;
}

bool FitsImage::write_history(const String history)

  /* Write or append history keyword. */
{
  int status = 0;
  if (fits_write_history(fptr, history.c_str(), &status))
    return report_error(status, "Unable to write history: " + history);

  return true;
}

bool FitsImage::write(void)

  /* Write current image to the file. Automatic data conversion is
     done if a 16bpp FITS file was created.  */
{
  int status = 0;

  // Write the image buffer to the FITS file. Automatic data
  // conversion is done if 'datatype' differs from 'bitpix' previously
  // defined when creating the image
  long firstel = 1;
  if (fits_write_img(fptr, datatype, firstel, (long)nPixels, buffer, &status))
    //return report_error(status, "Problem writing data to " + filename);
    return true; // changed by A.Fukui. (There may be minor problems on fits_write_img().)

  // Write was successful if we have made it this far
  return true;
}

bool FitsImage::close(void)

  /* Close the current FITS file pointed to by fitsio. */
{
  filename = "";
  int status = 0;
  if (fits_close_file(fptr, &status))
    return report_error(status, "Problem closing " + filename);
  return true;
}

bool FitsImage::copyheader(String fname)

  /*  Copy header from named FITS file and write to the FITS file
     currently defined by the class. The two FITS files should be
     different otherwise I don't know what will happen.
     
     THIS ROUTINE NEEDS MORE WORK.

     modified by A.Fukui

  */

{
  int status = 0;

  // Copy header from this FITS file
  fitsfile *tempptr;
  if (fits_open_file(&tempptr, fname.c_str(), READONLY, &status))
    report_error(status, "Couldn't open " + fname);

  if (fits_copy_header(tempptr, fptr, &status))
    report_error(status, "Couldn't copy header from " + fname);

  // Close the temporary file
  if (fits_close_file(tempptr, &status)) 
    fits_report_error(stderr, status);

  return true;
}

bool FitsImage::get_key_value(String key, int& kvalue)
{
  int status=0;
  int temp;
  String com;
  if (fits_read_key(fptr, TINT, key.c_str(), &temp, com.c_str(), &status))
    return false;

  kvalue = temp;
  return true;
}

bool FitsImage::get_key_value(String key, double& kvalue)
{
  int status=0;
  String com;
  double temp;
  if (fits_read_key(fptr, TDOUBLE, key.c_str(), &temp, com.c_str(), &status))
    return report_error(status, "Couldn't read from key: " + key);

  kvalue = temp;
  return true;
}

bool FitsImage::get_key_value(String key, String& kvalue)
{
  int status=0;
  String com;
  //String temp;
  char temp[20];
  if (fits_read_key(fptr, TSTRING, key.c_str(), temp, com.c_str(), &status))
    return report_error(status, "Couldn't read from key: " + key);

  kvalue = temp;
  return true;
}


bool FitsImage::set_key_value(String key, double kvalue, String com)
{
  int status=0;
  double temp = kvalue;
  if (fits_write_key(fptr, TDOUBLE, key.c_str(), &temp, com.c_str(), &status))
    return report_error(status, "Couldn't write key: " + key);


  //String templ = key + " " + num_to_str(kvalue) + " " + com;

  // Render the template card string into a valid FITS card
  //int keytype;
  //char card[FLEN_CARD], temp[250];
  //strcpy(temp, templ.c_str());
  //fits_parse_template(temp, card, &keytype, &status);
  //cout << "parse status = " << status << endl;
  //cout << card << endl;

  // Write this key-value-comment onto disc
  //strcpy(temp, key.c_str());
  //fits_update_card(fptr, temp, card, &status);
  //cout << "update status = " << status << endl;
  
  return true;
}

bool FitsImage::set_key_value(String key, int kvalue, String com)
{
  int status=0;
  int temp = kvalue;
  if (fits_write_key(fptr, TINT, key.c_str(), &temp, com.c_str(), &status))
    return report_error(status, "Couldn't write key: " + key);

  return true;
}

bool FitsImage::set_key_value(String key, String kvalue, String com)
{
  int status=0;
  String temp = kvalue;
  if (fits_write_key(fptr, TSTRING, key.c_str(), &temp, com.c_str(), &status))
    return report_error(status, "Couldn't write key: " + key);

  return true;
}

bool report_error(int status, const String message)

  /* Wrapper function for reporting cfitsio error. */
{
  cerr << message.c_str() << endl;
  fits_report_error(stderr, status);
  return false;
}

void add(FitsImage& image1, FitsImage& image2)

  /* Add the second image data to the first. */
{
  int numUse = minimum(image1.nPixels, image2.nPixels);
  for (int n = 0; n < numUse; ++n) 
    image2.buffer[n] += image1.buffer[n];
}

void subtract(FitsImage& image1, FitsImage& image2)

{
  int numUse = minimum(image1.nPixels, image2.nPixels);
  for (int n = 0; n < numUse; ++n) 
    image1.buffer[n] -= image2.buffer[n];
}

void divide(FitsImage& image1, FitsImage& image2)

{
  int numUse = minimum(image1.nPixels, image2.nPixels);
  for (int n = 0; n < numUse; ++n) {
    if (image2.buffer[n] != 0) 
      image1.buffer[n] /= image2.buffer[n];
    else
      image1.buffer[n] = 0;
  }
}

void imcopy(FitsImage& image1, FitsImage& image2)

  /* Add the second image data to the first. */
{
  image1.resize(image1.nPixx, image1.nPixy);
  for (int n = 0; n < image1.nPixels; ++n) 
    image2.buffer[n] = image1.buffer[n];
}
