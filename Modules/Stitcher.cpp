#include "Stitcher.h"

bool Stitcher::Initialize (void)
{
    // Initialize the final image and apply a uniform color to
    // all indices. This will allow us to notice blank spots later on.
    _finalImage = cv::Mat (IMAGE_DIMENSION, IMAGE_DIMENSION, CV_8UC3,
                           cv::Scalar(DEFAULT_RED,DEFAULT_GREEN,DEFAULT_BLUE));
    _centerPan = CENTER_PAN_PX;
    _centerTilt = CENTER_TILT_PX;
    _imageHeight = IMAGE_HEIGHT;
    _imageWidth = IMAGE_WIDTH;
	return true;
}

/*
 * Using the determined Pan/Tilt of a given pixel, determine the
 * pixel it relates to in the final image.
*/
void Stitcher::CalculateFinalPx(double panDegree, double tiltDegree, double *panOffset, double *tiltOffset)
{
    *panOffset = (((1.00-((panDegree + 5.50)/151.50))) * 239) - (_centerPan);
    *tiltOffset = ((240.00*tiltDegree/152.00)) + 1.5686 - (_centerTilt);
}

void Stitcher::SaveImage ()
{
    cv::imwrite("finalImage.jpg", _finalImage);
}

void Stitcher::UpdateFinalImage(double panDegree, double tiltDegree)
{
  cv::Vec3b newColor, oldColor;
  double currentAverage;
  double finalPanPx, finalTiltPx;
  double currentPanPx, currentTiltPx;
  _currentImage = cv::imread ("./Modules/Captures/raw_capture.png");
  CalculateFinalPx(panDegree, tiltDegree, &finalPanPx, &finalTiltPx);
  std::cout<<"\t\tFinal Degrees: P("<<panDegree<<")\tT("<<tiltDegree<<")\n";
  std::cout<<"\t\tFinal Px: P("<<finalPanPx<<")\tT("<<finalTiltPx<<")\n";
  for (double row = 0; row < _imageHeight; row++)
      for (double col = 0; col < _imageWidth; col++)
      {
          currentPanPx = col + finalPanPx;
          currentTiltPx = row + finalTiltPx;

          if (currentPanPx < 0.00)
              currentPanPx = 0.00;
          else if (currentPanPx > 239.00)
              currentPanPx = 239.00;

          if (currentTiltPx < 0.00)
              currentTiltPx = 0.00;
          else if (currentTiltPx > 239.00)
              currentTiltPx = 239.00;

          currentPanPx = nearbyint(currentPanPx);
          currentTiltPx = nearbyint(currentTiltPx);

        newColor = _currentImage.at<cv::Vec3b>(row, col);
        oldColor = _finalImage.at<cv::Vec3b>(currentTiltPx, currentPanPx);

        if (oldColor [0] != DEFAULT_RED||
                oldColor [1] != DEFAULT_GREEN ||
                oldColor [2] != DEFAULT_BLUE)
        {
            // Try to average the rgb values. Should make things smoother.
            // Average it out.
            for (int i = 0; i < 3; i++)
            {
                currentAverage = (oldColor [i] * oldColor [i]) + (newColor [i] * newColor [i]);
                currentAverage /= 2;
                currentAverage = sqrt (currentAverage);
                newColor [i] = nearbyint (currentAverage);
            }
        }

        _finalImage.row(currentTiltPx).col(currentPanPx) = newColor;
      }
}
