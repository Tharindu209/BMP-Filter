#include "bmp.h"

// grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect 
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur
void blur(int height, int width, RGBTRIPLE image[height][width]);

