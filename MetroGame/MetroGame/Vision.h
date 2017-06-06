#pragma once
#include <list>
#include "Vect.h"
#include "linedetection.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <zbar.h>

#define LINE_RED 0
#define LINE_GREEN 1
#define LINE_BLUE 2

class Vision
{
public:
	Vision();
	~Vision();
	void start();
	void calibrate();
	struct ColourSettings
	{
		int low_v, low_s, low_h;
		int high_v, high_s, high_h;
		int low_r, low_g, low_b;
		int high_r, high_g, high_b;
	};
	struct CV_Station
	{
		Vec2f location;
		int id;
	};
	ColourSettings colourCalibrate();

	std::list<GameLogic::Vec2f> getLines(int linecolour);
	std::list<CV_Station> getStations();
private:
	VideoCapture cap;
	ColourSettings redSettings;
	ColourSettings greenSettings;
	ColourSettings blueSettings;
	zbar::ImageScanner scanner;
};
