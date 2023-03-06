//Introduction to Image Processing #Homework 3 
//1023311
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include "imageLoader.cpp"

using namespace std;

void histEqualize(imgData &src, imgData &dst); //Histogram equalization
void drawHist(const imgData &src, imgData &dst); // Draw Histogram

void copyImgShape(imgData& src, imgData& dst) {
	dst.height = src.height;
	dst.width = src.width;
	dst.pixels = new byte[src.height * src.width];
	for(int i = 0; i < src.height * src.width; ++i)
		dst.pixels[i] = 0;
}

int convertCoordinates(int x, int y, int width) {
	return y * width + x;
}

int main()
{
	imgData image, out, hist1, hist2;
	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };

	char file[200];
	cout << "Enter the file name: ";
	scanf("%s", file);

	image = loadImage(file);

	copyImgShape(image, out);

	histEqualize(image, out); //eq

	writeImage(file, "output", out);
	writeImage(file, "grayscale", image);
	
	printf("Output png file generated!");


	// namedWindow("Original", WINDOW_AUTOSIZE);
	// imshow("Original", image);
	// waitKey(0);

	// calcHist(&image, 1, 0, Mat(), hist1, 1, &histSize, &histRange);
	// Mat showHist1(256, 256, CV_8UC1, Scalar(255));
	// drawHist(hist1, showHist1);

	// namedWindow("Histogram(Original)", WINDOW_AUTOSIZE);
	// imshow("Histogram(Original)", showHist1);
	// waitKey(0);

	// namedWindow("Histogram Equalization", WINDOW_AUTOSIZE);
	// imshow("Histogram Equalization", out);
	// waitKey(0);


	// calcHist(&out, 1, 0, Mat(), hist2, 1, &histSize, &histRange);
	// Mat showHist2(256, 256, CV_8UC1, Scalar(255));
	// drawHist(hist2, showHist2);

	// namedWindow("Histogram(Equalized)", WINDOW_AUTOSIZE);
	// imshow("Histogram(Equalized)", showHist2);
	// waitKey(0);

	// imwrite("Histogram_equalized.jpg", out);

	delete[] out.pixels;
	return 0;
}


void histEqualize(imgData &src, imgData &dst)
{
	int gray[256] {0}; //Ex: gray[0] = gray value 0 appaer times, gray[1] = gray value 1 appaer times, ...
	for (int y = 0; y < src.height; y++) { 
		for (int x = 0; x < src.width; x++) { //count each gray value appaer times
			// (int)src.at<uchar>(y, x)
			gray[src.pixels[convertCoordinates(x, y, src.width)]]++;
		} 
	} 
	
	for (int i = 0; i < 255; i++) { //calculate cdf (Cumulative distribution function)
		gray[i + 1] += gray[i];
	}

	for (int y = 0; y < src.height; y++) {
		for (int x = 0; x < src.width; x++) {
			// h(v) = round(((cdf(v) - mincdf) / (M * N) - mincdf) * (L - 1)) ; L = 2^8
			// dst.at<uchar>(y, x) = (uchar)round((((double)gray[(int)src.at<uchar>(y, x)] - mincdf) / (double)(src.rows * src.cols - mincdf)) * (double)255);
			dst.pixels[convertCoordinates(x, y, src.width)] = (float)gray[src.pixels[convertCoordinates(x, y, src.width)]] / (src.width * src.height) * 255;
		}
		printf("%f percent\n", (float)(y+1) / src.height * 100);
	}
}