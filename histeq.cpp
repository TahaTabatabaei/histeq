#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include "imageLoader.cpp"

using namespace std;

void histEqualize(imgData &src, imgData &dst); //Histogram equalization

void copyImgShape(imgData& src, imgData& dst) {
	dst.height = src.height;
	dst.width = src.width;
	dst.pixels = new byte[src.height * src.width];
	for(int i = 0; i < src.height * src.width; ++i)
		dst.pixels[i] = 0;
}

/************************************************************************************************
 * The function converts a 2D array index to a flattened 1D array equivalent of it
 * Inputs:        int x : the x in 2D coordinates
 *         		  int y : the y in 2D coordinates
 * 			  int width : the width
 * Outputs:    1D index : the equivalent index that shows the item's position in the 1D array
 ***********************************************************************************************/
int convertCoordinates(int x, int y, int width) {
	return y * width + x;
}

int main()
{
	imgData image, out;

	char file[200];
	cout << "Enter the file name: ";
	scanf("%s", file);

	image = loadImage(file);

	copyImgShape(image, out);

	histEqualize(image, out);

	writeImage(file, "output", out);
	writeImage(file, "grayscale", image);
	
	printf("\nGrayscale png of input file generated!\n");
	printf("Output png file generated!\n");

	delete[] out.pixels;
	return 0;
}

/************************************************************************************************
 * The function applies the histogram equalization filter
 * Inputs:        imgData &src : the original image
 *         		  imgData &dst : the output image after applying the filter
 ***********************************************************************************************/
void histEqualize(imgData &src, imgData &dst)
{
	//Ex: gray[0] = gray value 0 appear how many times, gray[1] = gray value 1 appear how many times, ...
	int gray[256] {0}; 
	for (int y = 0; y < src.height; y++) { 
		for (int x = 0; x < src.width; x++) { //count how many times each gray value appears
			gray[src.pixels[convertCoordinates(x, y, src.width)]]++;
		} 
	} 
	
	//calculate cdf (Cumulative distribution function)
	for (int i = 0; i < 255; i++) { 
		gray[i + 1] += gray[i];
	}

	for (int y = 0; y < src.height; y++) {
		for (int x = 0; x < src.width; x++) {
			dst.pixels[convertCoordinates(x, y, src.width)] = (float)gray[src.pixels[convertCoordinates(x, y, src.width)]] / (src.width * src.height) * 255;
		}
		printf("%f percent\n", (float)(y+1) / src.height * 100);
	}
}