/*
  A simple radix 2 fast fourier transform. Written mainly in c style.
 */

#include <complex>
#include <iostream>
#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>

typedef std::complex<double> Complex;

void TestSpike(Complex* data, int length){
  assert( 1.0 == data[3]);
}

//Generates a spike in the DC bin, used for testing the fft
void GenerateSpike(Complex* data, int length){
  std::fill(data, data+length, 0.0);
  if(length >= 2) data[3] = 1.0;
  TestSpike(data, length);
}

void TestTwiddle(){
}

void TestButterfly(){
}

Complex w(int bin, int length){
  return (cos(2*M_PI*bin/length), sin(2*M_PI*bin/length));  
}

void butterfly(Complex* data, int bin, int stepSize, int fftlength){
  Complex x0 = data[bin];
  Complex x1 = data[bin+stepSize];

  data[bin]          = x0 + w(bin, fftlength)*x1;
  data[bin+stepSize] = x0 - w(bin, fftlength)*x1;
  std::cout << "bin: " << bin << " bin + stepSize: " << bin+stepSize << std::endl;
  std::cout << "data[bin]: " << data[bin] << " data[bin+stepSize]: " << data[bin+stepSize] << std::endl;
}

//Decimation in time
void FFT(Complex* data, int length){
  for(int bflySize = 2 ; bflySize <= length ; bflySize *= 2)
    {
      int stepSize = bflySize/2;
      for(int i = 0 ; i < stepSize ; i++)
	{
	   for(int j = i ; j < length ; j+= bflySize)
	    {
	      butterfly(data, j, stepSize, length);
	    }
	}
    }
}

int Reverse(unsigned int i, int size){
  int reversed = 0;
  while(size > 1){
    reversed = (reversed >> 1) | (i & 1);
    i >>= 1;
    size >>= 1;
  }
  return reversed;
}

int main(int argv, char** argc){
  
  int length;
  std::cout << "Please input the length of the FFT" << std::endl;
  std::cin >> length;
  std::complex<double> data[length];
  GenerateSpike(data, length);
  FFT(data, length);
  for(int i = 0 ; i < length ; i++)
    {
      //int j = Reverse(i,length);
      std::cout << data[i] << std:: endl;
    }
  return 0;
}






