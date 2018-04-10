#ifndef STITCHER_H_
#define STITCHER_H_

#include <iostream>
#include <fstream>
#include <QString>
#include <math.h>
#include <opencv/highgui.h>
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"

#define IMAGE_DIMENSION 240.00
#define ANGLE_CONVERSION_MULTIPLIER -0.64
#define CENTER_PAN_PX 39.00;
#define CENTER_TILT_PX 29.00;
#define IMAGE_HEIGHT 60.00;
#define IMAGE_WIDTH 80.00;
#define DEFAULT_RED 181
#define DEFAULT_GREEN 109
#define DEFAULT_BLUE 246

class Stitcher
{
	public:
		bool Initialize ();
        void UpdateFinalImage (double panAngle, double tiltAngle);
        void SaveImage ();
    private:
        cv::Mat _currentImage;
        cv::Mat _finalImage;
        double _centerPan;
        double _centerTilt;
        double _imageHeight;
        double _imageWidth;
        void CalculateFinalPx (double panDegree, double tiltDegree
                               , double* panOffset, double* tiltOffset);
};

#endif /* Stitcher_H_ */
