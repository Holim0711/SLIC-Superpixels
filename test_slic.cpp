/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 * Modified by: HL
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 
#include <stdio.h>

#include "slic.h"

int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    IplImage *img = cvLoadImage(argv[1], 1);
    IplImage *lab = cvCloneImage(img);
    cvCvtColor(img, lab, CV_BGR2Lab);
    
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = img->width, h = img->height;
    int nr_superpixels = atoi(argv[3]);
    int nc = 10;

    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic slic(lab, step, nc);
    slic.generate_superpixels(lab);
    slic.create_connectivity(lab);
    vec2di cls = slic.get_clusters();
    
    /* Write out cluster information  */
	FILE *fp = fopen(argv[2], "wb");
    for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			fwrite(&cls[x][y], sizeof(int), 1, fp);
	fclose(fp);
    return 0;
}
