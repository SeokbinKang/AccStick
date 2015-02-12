#include "stdafx.h"

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void overlayImage(const cv::Mat &background, const cv::Mat &foreground, 
  cv::Mat &output, cv::Point2i location);
void my_mouse_callback( int event, int x, int y, int flags, void* param );
Mat image;
Mat imgBR;
Mat cursor;
Mat curBG;
Mat finalBG;
Mat cursorResize;
bool windowInit=false;
void changeCursor(int size_);
void InitMouse(){
cvSetMouseCallback( "Name", my_mouse_callback, (void*)NULL);

}

void setupDesk(){
	windowInit=true;
	cvNamedWindow("Name", CV_WINDOW_NORMAL);
    cvSetWindowProperty("Name", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
   
 	image = imread("./desktop.jpg",CV_LOAD_IMAGE_COLOR );
	Mat imgDark = image + Scalar(-80, -80, -80);
	imgDark.copyTo(image);
	 cursor = imread("./cursor.png", -1);
	 resize(cursor,cursor, cvSize(cursor.size().width/10, cursor.size().height/10));
	 cursor.copyTo(cursorResize);
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return ;
    }
	image.copyTo(curBG);
    //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
   imshow( "Name", curBG );                   // Show our image inside it.
	cvSetMouseCallback( "Name", my_mouse_callback, (void*)NULL);
 //   waitKey(0);                                          // Wait for a keystroke in the window
 
	
	return ;
}
void changeCursor(int size_) {
	float scale = size_;
	
	if(!windowInit) setupDesk();
	resize(cursor,cursorResize, cvSize(cursor.size().width*(size_-1), cursor.size().height*(size_-1)));
}
void changeBR(int br){
	if(!windowInit) setupDesk();
	Mat imgH = image + Scalar(br, br, br); //increase the brightness by 75 units
	Mat imgResult;
	imgH.copyTo(curBG);
	//overlayImage(imgH, cursor, curBG, cv::Point(0,0));
	imshow( "Name", curBG );

	//waitKey(0);
}
void overlayImage(const cv::Mat &background, const cv::Mat &foreground, 
  cv::Mat &output, cv::Point2i location)
{
  background.copyTo(output);


  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = std::max(location.y , 0); y < background.rows; ++y)
  {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows)
      break;

    // start at the column indicated by location, 

    // or at column 0 if location.x is negative.
    for(int x = std::max(location.x, 0); x < background.cols; ++x)
    {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols)
        break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity =
        ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

        / 255.;


      // and now combine the background and foreground pixel, using the opacity, 

      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c)
      {
        unsigned char foregroundPx =
          foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx =
          background.data[y * background.step + x * background.channels() + c];
       // output.data[y*output.step + output.channels()*x + c] =          backgroundPx * (1.-opacity) + foregroundPx * opacity;
		 output.data[y*output.step + output.channels()*x + c] =   255- backgroundPx;
      }
    }
  }
}

int q=0;
void my_mouse_callback( int event, int x, int y, int flags, void* param ){
	//printf("calllbakkk");
	if(!windowInit) setupDesk();
	//if(q++ % 10 !=0) return ;
	overlayImage(curBG, cursorResize, finalBG, cv::Point(x,y));
				imshow( "Name", finalBG );
	switch( event ){
		case CV_EVENT_MOUSEMOVE: 

			//	overlayImage(curBG, cursorResize, finalBG, cv::Point(x,y));
			//s	imshow( "Name", finalBG );
				
		
			break;
		default:;
	
	}
}