#include "Vision.h"
#include "RenderableOutput.h"
using namespace mg_gameLogic;

bool debug = true;

int low_v = 30, low_s = 30, low_h = 30;
int high_v = 100, high_s = 100, high_h = 100;

int low_r = 30, low_g = 30, low_b = 30;
int high_r = 100, high_g = 100, high_b = 100;

void on_low_v_thresh_trackbar(int, void *);
void on_high_v_thresh_trackbar(int, void *);
void on_low_s_thresh_trackbar(int, void *);
void on_high_s_thresh_trackbar(int, void *);
void on_low_h_thresh_trackbar(int, void *);
void on_high_h_thresh_trackbar(int, void *);

void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);

Vision::Vision()
{

}


Vision::~Vision()
{

}

void Vision::start()
{
	cap.open(1);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	scanner;
	scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
}


void Vision::calibrate()
{	
	string value;
	ifstream readFile("thresholds.txt");
	if (readFile.is_open())
	{
		getline(readFile, value); redSettings.high_r = atoi(value.c_str()); getline(readFile, value); redSettings.high_g = atoi(value.c_str()); getline(readFile, value); redSettings.high_b = atoi(value.c_str()); getline(readFile, value); redSettings.high_h = atoi(value.c_str()); getline(readFile, value); redSettings.high_s = atoi(value.c_str()); getline(readFile, value); redSettings.high_v = atoi(value.c_str());
		getline(readFile, value); redSettings.low_r = atoi(value.c_str()); getline(readFile, value); redSettings.low_g = atoi(value.c_str()); getline(readFile, value); redSettings.low_b = atoi(value.c_str()); getline(readFile, value); redSettings.low_h = atoi(value.c_str()); getline(readFile, value); redSettings.low_s = atoi(value.c_str()); getline(readFile, value); redSettings.low_v = atoi(value.c_str());

		getline(readFile, value); greenSettings.high_r = atoi(value.c_str()); getline(readFile, value); greenSettings.high_g = atoi(value.c_str()); getline(readFile, value); greenSettings.high_b = atoi(value.c_str()); getline(readFile, value); greenSettings.high_h = atoi(value.c_str()); getline(readFile, value); greenSettings.high_s = atoi(value.c_str()); getline(readFile, value); greenSettings.high_v = atoi(value.c_str());
		getline(readFile, value); greenSettings.low_r = atoi(value.c_str()); getline(readFile, value); greenSettings.low_g = atoi(value.c_str()); getline(readFile, value); greenSettings.low_b = atoi(value.c_str()); getline(readFile, value); greenSettings.low_h = atoi(value.c_str()); getline(readFile, value); greenSettings.low_s = atoi(value.c_str()); getline(readFile, value); greenSettings.low_v = atoi(value.c_str());

		getline(readFile, value); blueSettings.high_r = atoi(value.c_str()); getline(readFile, value); blueSettings.high_g = atoi(value.c_str()); getline(readFile, value); blueSettings.high_b = atoi(value.c_str()); getline(readFile, value); blueSettings.high_h = atoi(value.c_str()); getline(readFile, value); blueSettings.high_s = atoi(value.c_str()); getline(readFile, value); blueSettings.high_v = atoi(value.c_str());
		getline(readFile, value); blueSettings.low_r = atoi(value.c_str()); getline(readFile, value); blueSettings.low_g = atoi(value.c_str()); getline(readFile, value); blueSettings.low_b = atoi(value.c_str()); getline(readFile, value); blueSettings.low_h = atoi(value.c_str()); getline(readFile, value); blueSettings.low_s = atoi(value.c_str()); getline(readFile, value); blueSettings.low_v = atoi(value.c_str());

		readFile.close();
	}


	namedWindow("Video Capture", WINDOW_NORMAL);
	namedWindow("TrackBars", WINDOW_NORMAL);
	namedWindow("RGB", WINDOW_NORMAL);
	namedWindow("HSV", WINDOW_NORMAL);
	namedWindow("Cut out", WINDOW_NORMAL);
	namedWindow("Combined", WINDOW_NORMAL);
	//-- Trackbars to set thresholds for RGB values
	createTrackbar("Low Hue", "TrackBars", &low_h, 255, on_low_h_thresh_trackbar);
	createTrackbar("High Hue", "TrackBars", &high_h, 255, on_high_h_thresh_trackbar);
	createTrackbar("Low Saturation", "TrackBars", &low_s, 255, on_low_s_thresh_trackbar);
	createTrackbar("High Saturation", "TrackBars", &high_s, 255, on_high_s_thresh_trackbar);
	createTrackbar("Low Value", "TrackBars", &low_v, 255, on_low_v_thresh_trackbar);
	createTrackbar("High Value", "TrackBars", &high_v, 255, on_high_v_thresh_trackbar);

	createTrackbar("Low Red", "TrackBars", &low_r, 255, on_low_r_thresh_trackbar);
	createTrackbar("High Red", "TrackBars", &high_r, 255, on_high_r_thresh_trackbar);
	createTrackbar("Low Green", "TrackBars", &low_g, 255, on_low_g_thresh_trackbar);
	createTrackbar("High Green", "TrackBars", &high_g, 255, on_high_g_thresh_trackbar);
	createTrackbar("Low Blue", "TrackBars", &low_b, 255, on_low_b_thresh_trackbar);
	createTrackbar("High Blue", "TrackBars", &high_b, 255, on_high_b_thresh_trackbar);

	setTrackbarPos("Low Hue", "TrackBars", redSettings.low_h);
	setTrackbarPos("High Hue", "TrackBars", redSettings.high_h);
	setTrackbarPos("Low Saturation", "TrackBars", redSettings.low_s);
	setTrackbarPos("High Saturation", "TrackBars", redSettings.high_s);
	setTrackbarPos("Low Value", "TrackBars", redSettings.low_v);
	setTrackbarPos("High Value", "TrackBars", redSettings.high_v);

	setTrackbarPos("Low Red", "TrackBars", redSettings.low_r);
	setTrackbarPos("High Red", "TrackBars", redSettings.high_r);
	setTrackbarPos("Low Green", "TrackBars", redSettings.low_g);
	setTrackbarPos("High Green", "TrackBars", redSettings.high_g);
	setTrackbarPos("Low Blue", "TrackBars", redSettings.low_b);
	setTrackbarPos("High Blue", "TrackBars", redSettings.high_b);
	if (debug) //DEBUG ONLY
	{
		setTrackbarPos("Low Hue", "TrackBars", 150);
		setTrackbarPos("High Hue", "TrackBars", 255);
		setTrackbarPos("Low Saturation", "TrackBars", 72);
		setTrackbarPos("High Saturation", "TrackBars", 255);
		setTrackbarPos("Low Value", "TrackBars", 255);
		setTrackbarPos("High Value", "TrackBars", 255);

		setTrackbarPos("Low Red", "TrackBars", 232);
		setTrackbarPos("High Red", "TrackBars", 255);
		setTrackbarPos("Low Green", "TrackBars", 0);
		setTrackbarPos("High Green", "TrackBars", 101);
		setTrackbarPos("Low Blue", "TrackBars", 0);
		setTrackbarPos("High Blue", "TrackBars", 142);
	}
	redSettings = colourCalibrate();

	setTrackbarPos("Low Hue", "TrackBars", greenSettings.low_h);
	setTrackbarPos("High Hue", "TrackBars", greenSettings.high_h);
	setTrackbarPos("Low Saturation", "TrackBars", greenSettings.low_s);
	setTrackbarPos("High Saturation", "TrackBars", greenSettings.high_s);
	setTrackbarPos("Low Value", "TrackBars", greenSettings.low_v);
	setTrackbarPos("High Value", "TrackBars", greenSettings.high_v);

	setTrackbarPos("Low Red", "TrackBars", greenSettings.low_r);
	setTrackbarPos("High Red", "TrackBars", greenSettings.high_r);
	setTrackbarPos("Low Green", "TrackBars", greenSettings.low_g);
	setTrackbarPos("High Green", "TrackBars", greenSettings.high_g);
	setTrackbarPos("Low Blue", "TrackBars", greenSettings.low_b);
	setTrackbarPos("High Blue", "TrackBars", greenSettings.high_b);
	if (debug) //DEBUG ONLY
	{
		setTrackbarPos("Low Hue", "TrackBars", 0);
		setTrackbarPos("High Hue", "TrackBars", 75);
		setTrackbarPos("Low Saturation", "TrackBars", 200);
		setTrackbarPos("High Saturation", "TrackBars", 255);
		setTrackbarPos("Low Value", "TrackBars", 200);
		setTrackbarPos("High Value", "TrackBars", 255);

		setTrackbarPos("Low Red", "TrackBars", 70);
		setTrackbarPos("High Red", "TrackBars", 155);
		setTrackbarPos("Low Green", "TrackBars", 170);
		setTrackbarPos("High Green", "TrackBars", 255);
		setTrackbarPos("Low Blue", "TrackBars", 0);
		setTrackbarPos("High Blue", "TrackBars", 255);
	}
	greenSettings = colourCalibrate();

	setTrackbarPos("Low Hue", "TrackBars", blueSettings.low_h);
	setTrackbarPos("High Hue", "TrackBars", blueSettings.high_h);
	setTrackbarPos("Low Saturation", "TrackBars", blueSettings.low_s);
	setTrackbarPos("High Saturation", "TrackBars", blueSettings.high_s);
	setTrackbarPos("Low Value", "TrackBars", blueSettings.low_v);
	setTrackbarPos("High Value", "TrackBars", blueSettings.high_v);

	setTrackbarPos("Low Red", "TrackBars", blueSettings.low_r);
	setTrackbarPos("High Red", "TrackBars", blueSettings.high_r);
	setTrackbarPos("Low Green", "TrackBars", blueSettings.low_g);
	setTrackbarPos("High Green", "TrackBars", blueSettings.high_g);
	setTrackbarPos("Low Blue", "TrackBars", blueSettings.low_b);
	setTrackbarPos("High Blue", "TrackBars", blueSettings.high_b);

	if (debug) //DEBUG ONLY
	{
		setTrackbarPos("Low Hue", "TrackBars", 90);
		setTrackbarPos("High Hue", "TrackBars", 150);
		setTrackbarPos("Low Saturation", "TrackBars", 180);
		setTrackbarPos("High Saturation", "TrackBars", 255);
		setTrackbarPos("Low Value", "TrackBars", 255);
		setTrackbarPos("High Value", "TrackBars", 255);

		setTrackbarPos("Low Red", "TrackBars", 0);
		setTrackbarPos("High Red", "TrackBars", 160);
		setTrackbarPos("Low Green", "TrackBars", 0);
		setTrackbarPos("High Green", "TrackBars", 120);
		setTrackbarPos("Low Blue", "TrackBars", 180);
		setTrackbarPos("High Blue", "TrackBars", 255);
	}
	blueSettings = colourCalibrate();

	blueSettings = colourCalibrate();
	cvDestroyWindow("Video Capture");
	cvDestroyWindow("TrackBars");
	cvDestroyWindow("RGB");
	cvDestroyWindow("HSV");
	cvDestroyWindow("Cut out");
	cvDestroyWindow("Combined");

	ofstream writeFile("thresholds.txt");
	if (writeFile.is_open())
	{
		writeFile << redSettings.high_r << "\n"; writeFile << redSettings.high_g << "\n"; writeFile << redSettings.high_b << "\n"; writeFile << redSettings.high_h << "\n"; writeFile << redSettings.high_s << "\n"; writeFile << redSettings.high_v << "\n";
		writeFile << redSettings.low_r << "\n"; writeFile << redSettings.low_g << "\n"; writeFile << redSettings.low_b << "\n"; writeFile << redSettings.low_h << "\n"; writeFile << redSettings.low_s << "\n"; writeFile << redSettings.low_v << "\n";

		writeFile << greenSettings.high_r << "\n"; writeFile << greenSettings.high_g << "\n"; writeFile << greenSettings.high_b << "\n"; writeFile << greenSettings.high_h << "\n"; writeFile << greenSettings.high_s << "\n"; writeFile << greenSettings.high_v << "\n";
		writeFile << greenSettings.low_r << "\n"; writeFile << greenSettings.low_g << "\n"; writeFile << greenSettings.low_b << "\n"; writeFile << greenSettings.low_h << "\n"; writeFile << greenSettings.low_s << "\n"; writeFile << greenSettings.low_v << "\n";

		writeFile << blueSettings.high_r << "\n"; writeFile << blueSettings.high_g << "\n"; writeFile << blueSettings.high_b << "\n"; writeFile << blueSettings.high_h << "\n"; writeFile << blueSettings.high_s << "\n"; writeFile << blueSettings.high_v << "\n";
		writeFile << blueSettings.low_r << "\n"; writeFile << blueSettings.low_g << "\n"; writeFile << blueSettings.low_b << "\n"; writeFile << blueSettings.low_h << "\n"; writeFile << blueSettings.low_s << "\n"; writeFile << blueSettings.low_v << "\n";

		writeFile.close();
	}
	else cout << "Unable to open file";

}

Vision::ColourSettings Vision::colourCalibrate()
{
	Mat frame, frame_threshold, frame_rgb;

	while ((char)waitKey(1) != 'q') {

		if (debug)
		{
			frame = imread("metro_test2.png");
		}
		else
		{
			cap >> frame;
			if (frame.empty())
				break;
		}
		Mat mask;
		Mat cutout;
		mask = imread("mask.png");
		frame.copyTo(cutout, mask);
		imshow("Cut out", cutout);
		cutout.copyTo(frame);
		//-- Detect the object based on RGB Range Values
		Mat hsv_image;
		cvtColor(frame, hsv_image, CV_BGR2HSV);
		inRange(hsv_image, Scalar(low_h, low_s, low_v), Scalar(high_h, high_s, high_v), frame_threshold);
		inRange(frame, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), frame_rgb);
		int dilation_size = 9;//7
		int erosion_size = 7;//5

		Mat element = getStructuringElement(MORPH_ELLIPSE,
			Size(2 * dilation_size + 1, 2 * dilation_size + 1),
			Point(dilation_size, dilation_size));
		Mat element2 = getStructuringElement(MORPH_ELLIPSE,
			Size(2 * erosion_size + 1, 2 * erosion_size + 1),
			Point(erosion_size, erosion_size));

		imshow("Video Capture", hsv_image);
		dilate(frame_threshold, frame_threshold, element);
		erode(frame_threshold, frame_threshold, element2);
		dilate(frame_rgb, frame_rgb, element);
		erode(frame_rgb, frame_rgb, element2);

		//-- Show the frames
		imshow("RGB", frame_rgb);
		imshow("HSV", frame_threshold);

		Mat combined;
		combined = frame_rgb.mul(frame_threshold);

		//addWeighted(frame_rgb, 1.0, frame_threshold, 1.0, 0.0, combined);
		imshow("Combined", combined);
	}
	Vision::ColourSettings coloursettings;
	coloursettings.high_r = high_r;
	coloursettings.high_g = high_g;
	coloursettings.high_b = high_b;

	coloursettings.low_r = low_r;
	coloursettings.low_g = low_g;
	coloursettings.low_b = low_b;

	coloursettings.high_h = high_h;
	coloursettings.high_s = high_s;
	coloursettings.high_v = high_v;

	coloursettings.low_h = low_h;
	coloursettings.low_s = low_s;
	coloursettings.low_v = low_v;
	return coloursettings;
}




std::list<GameLogic::Vec2f> Vision::getLines(int linecolour)
{
	Mat image;
	//image = imread("line.png");
	//cap.open(1);
	cap >> image;
	if (image.empty())
		cout << "GEEN IMAGE" << endl;

	if (debug)
	{
		image = imread("metro_test2.png");
	}

	Mat mask;
	Mat cutout;
	mask = imread("mask2.png");
	image.copyTo(cutout, mask);
	//imshow("Cut out", cutout);
	cutout.copyTo(image);

	// De afbeelding converteren naar een grijswaarde afbeelding
	Mat hsv_image;
	cvtColor(image, hsv_image, CV_BGR2HSV);
	//imshow("LINE_HSV Image", hsv_image);
	//namedWindow("HSV image", WINDOW_AUTOSIZE);
	//imshow("HSV image", hsv_image);

	// Seperate Colors with inRange
	/*cv::Mat lower_red_hue_range;
	cv::Mat upper_red_hue_range;*/
	//cv::inRange(hsv_image, cv::Scalar(0, 10, 100), cv::Scalar(10, 255, 255), lower_red_hue_range); // 0 10
	//cv::inRange(hsv_image, cv::Scalar(160, 10, 100), cv::Scalar(179, 255, 255), upper_red_hue_range); // 160 179

																									  // Combine the above two images
	//HSV
	cv::Mat red_hue_image;
	//cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_image);
	cv::inRange(hsv_image, cv::Scalar(redSettings.low_h, redSettings.low_s, redSettings.low_v), cv::Scalar(redSettings.high_h, redSettings.high_s, redSettings.high_v), red_hue_image);

	cv::Mat blue_hue_image;
	cv::inRange(hsv_image, cv::Scalar(blueSettings.low_h, blueSettings.low_s, blueSettings.low_v), cv::Scalar(blueSettings.high_h, blueSettings.high_s, blueSettings.high_v), blue_hue_image);
	
	cv::Mat green_hue_image;
	cv::inRange(hsv_image, cv::Scalar(greenSettings.low_h, greenSettings.low_s, greenSettings.low_v), cv::Scalar(greenSettings.high_h, greenSettings.high_s, greenSettings.high_v), green_hue_image);

	//RGB
	cv::Mat red_rgb_image;
	cv::inRange(image, cv::Scalar(redSettings.low_b, redSettings.low_g, redSettings.low_r), cv::Scalar(redSettings.high_b, redSettings.high_g, redSettings.high_r), red_rgb_image);

	cv::Mat blue_rgb_image;
	cv::inRange(image, cv::Scalar(blueSettings.low_b, blueSettings.low_g, blueSettings.low_r), cv::Scalar(blueSettings.high_b, blueSettings.high_g, blueSettings.high_r), blue_rgb_image);

	cv::Mat green_rgb_image;
	cv::inRange(image, cv::Scalar(greenSettings.low_b, greenSettings.low_g, greenSettings.low_r), cv::Scalar(greenSettings.high_b, greenSettings.high_g, greenSettings.high_r), green_rgb_image);

	int dilation_size = 9;//7
	int erosion_size = 7;//5
	Mat element = getStructuringElement(MORPH_ELLIPSE,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	Mat element2 = getStructuringElement(MORPH_ELLIPSE,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	dilate(red_hue_image, red_hue_image, element);
	erode(red_hue_image, red_hue_image, element2);
	dilate(red_rgb_image, red_rgb_image, element);
	erode(red_rgb_image, red_rgb_image, element2);

	dilate(blue_hue_image, blue_hue_image, element);
	erode(blue_hue_image, blue_hue_image, element2);
	dilate(blue_rgb_image, blue_rgb_image, element);
	erode(blue_rgb_image, blue_rgb_image, element2);

	dilate(green_hue_image, green_hue_image, element);
	erode(green_hue_image, green_hue_image, element2);
	dilate(green_rgb_image, green_rgb_image, element);
	erode(green_rgb_image, green_rgb_image, element2);

	Mat combined_red, combined_green, combined_blue;
	combined_red = red_rgb_image.mul(red_hue_image);
	combined_green = green_rgb_image.mul(green_hue_image);
	combined_blue = blue_rgb_image.mul(blue_hue_image);
	namedWindow("Combined Blue", WINDOW_AUTOSIZE);
	imshow("LINE_Combined Blue", combined_red);
	//imshow("LINE_HSV Blue", blue_hue_image);
	//imshow("LINE_RGB Blue", blue_rgb_image);
	//Threshold to get Binary image
	Mat binaryImage_red;
	threshold(combined_red, binaryImage_red, 254, 1, CV_THRESH_BINARY);
	Mat binaryImage_green;
	threshold(combined_green, binaryImage_green, 254, 1, CV_THRESH_BINARY);
	Mat binaryImage_blue;
	threshold(combined_blue, binaryImage_blue, 254, 1, CV_THRESH_BINARY);

	// Convert to 16 binary
	Mat binary16S_red;
	binaryImage_red.convertTo(binary16S_red, CV_16S);
	Mat binary16S_green;
	binaryImage_green.convertTo(binary16S_green, CV_16S);
	Mat binary16S_blue;
	binaryImage_blue.convertTo(binary16S_blue, CV_16S);

	//Label all the blobs
	Mat labeledImageRed, labeledImageGreen, labeledImageBlue;
	vector<vector<Point2d *>> coords;
	int blobs;
	switch (linecolour)
	{
	case LINE_RED:
		blobs = labelBLOBs(binary16S_red, labeledImageRed, coords);
		cout << "N:" << blobs << " Red" << endl;
		break;
	case LINE_GREEN:
		blobs = labelBLOBs(binary16S_green, labeledImageGreen, coords);
		cout << "N:" << blobs << " Green" << endl;
		break;
	case LINE_BLUE:
		blobs = labelBLOBs(binary16S_blue, labeledImageBlue, coords);
		cout << "N:" << blobs << " Blue" << endl;
		break;
	default:
		break;
	}
	//imshow("Blue blob", labeledImageBlue * 254);
	std::list<GameLogic::Vec2f> lines;
	std::vector<GameLogic::Vec2f> test;
	if (coords.size() > 0)
	{
		for (int j = 0; j < coords.size() - 1; j++)
		{
			for (int i = 0; i < coords[j].size(); i++)
			{
				GameLogic::Vec2f vector = GameLogic::Vec2f((((coords[j][i]->x - 260) / ((image.cols - 500) / 2.0f)) - 1.0f), ((coords[j][i]->y - 60) / ((image.rows - 180) / 2.0f)) - 1.0f);
				lines.push_back(vector);
			}
		}

	}
	//test.push_back(GameLogic::Vec2f(-1.0f, -1.0f));
	//test.push_back(GameLogic::Vec2f(1.0f, 1.0f));
	RenderableLine pLine;
	switch (linecolour)
	{
	case LINE_RED:
		pLine = RenderableLine(test, LineType::Red);
		break;
	case LINE_GREEN:
		pLine = RenderableLine(test, LineType::Green);
		break;
	case LINE_BLUE:
		pLine = RenderableLine(test, LineType::Blue);
		break;
	default:
		break;
	}
	allocate_line(pLine);
	Mat redLines, greenLines, blueLines;
	//switch (linecolour)
	//{
	//case LINE_RED:
	//	redLines = image.clone();
	//	for (int i = 0; i < coords.size(); i++)
	//	{
	//		for (int y = 1; y < coords[i].size(); y++)
	//		{
	//			line(redLines, *coords[i][y - 1], *coords[i][y], Scalar(150, 20, 20), 3, CV_AA);
	//		}
	//	}
	//	namedWindow("RedLines", WINDOW_AUTOSIZE);
	//	imshow("RedLines", redLines);
	//	break;
	//case LINE_GREEN:
	//	greenLines = image.clone();
	//	for (int i = 0; i < coords.size(); i++)
	//	{
	//		for (int y = 1; y < coords[i].size(); y++)
	//		{
	//			line(greenLines, *coords[i][y - 1], *coords[i][y], Scalar(150, 20, 20), 3, CV_AA);
	//		}
	//	}
	//	namedWindow("GreenLines", WINDOW_AUTOSIZE);
	//	imshow("GreenLines", greenLines);
	//	break;
	//case LINE_BLUE:
	//	blueLines = image.clone();
	//	for (int i = 0; i < coords.size(); i++)
	//	{
	//		for (int y = 1; y < coords[i].size(); y++)
	//		{
	//			line(blueLines, *coords[i][y - 1], *coords[i][y], Scalar(150, 20, 20), 3, CV_AA);
	//		}
	//	}
	//	namedWindow("BlueLines", WINDOW_AUTOSIZE);
	//	imshow("BlueLines", blueLines);
	//	break;
	//default:
	//	break;
	//}
	return lines;
}

std::list<Vision::CV_Station> Vision::getStations()
{
	Mat frame;
	cap >> frame;
	if (debug)
	{
		frame = imread("metro_test2.png");
	}
	Mat grey;
	cvtColor(frame, grey, CV_BGR2GRAY);
	int width = frame.cols;
	int height = frame.rows;
	uchar *raw = (uchar *)grey.data;
	std::list<Vision::CV_Station> qr_stations;
	zbar::Image image(width, height, "Y800", raw, width * height);
	int n = scanner.scan(image);
	for (zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) 
	{
		vector<Point> vp;
		Vision::CV_Station station;
		station.location = GameLogic::Vec2f((((symbol->get_location_x(0) - 260) / ((frame.cols - 500) / 2.0f)) - 1.0f), ((symbol->get_location_y(0) - 60) / ((frame.rows - 180) / 2.0f)) - 1.0f);
		//station.location = GameLogic::Vec2f(symbol->get_location_x(0), symbol->get_location_y(0));
		station.id = std::stoi(symbol->get_data());
		qr_stations.push_back(station);
		cout << "decoded " << symbol->get_type_name() << " symbol \"" << symbol->get_data() << '"' << " " << "x:" << symbol->get_location_x(0) << " y:" << symbol->get_location_y(0) << endl;
		int n = symbol->get_location_size();
		for (int i = 0; i<n; i++) {
			vp.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		}
		RotatedRect r = minAreaRect(vp);
		Point2f pts[4];
		r.points(pts);
		for (int i = 0; i<4; i++) {
			line(frame, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 3);
		}
		//cout<<"Angle: "<<r.angle<<endl;  
	}

	imshow("MyVideo", frame);
	return qr_stations;
}

void on_low_v_thresh_trackbar(int, void *)
{
	low_v = min(high_v - 1, low_v);
	setTrackbarPos("Low Value", "Object Detection", low_v);
}
void on_high_v_thresh_trackbar(int, void *)
{
	high_v = max(high_v, low_v + 1);
	setTrackbarPos("High Value", "Object Detection", high_v);
}
void on_low_s_thresh_trackbar(int, void *)
{
	low_s = min(high_s - 1, low_s);
	setTrackbarPos("Low Saturation", "Object Detection", low_s);
}
void on_high_s_thresh_trackbar(int, void *)
{
	high_s = max(high_s, low_s + 1);
	setTrackbarPos("High Saturation", "Object Detection", high_s);
}
void on_low_h_thresh_trackbar(int, void *)
{
	low_h = min(high_h - 1, low_h);
	setTrackbarPos("Low Hue", "Object Detection", low_h);
}
void on_high_h_thresh_trackbar(int, void *)
{
	high_h = max(high_h, low_h + 1);
	setTrackbarPos("High Hue", "Object Detection", high_h);
}

void on_low_r_thresh_trackbar(int, void *)
{
	low_r = min(high_r - 1, low_r);
	setTrackbarPos("Low R", "RGB", low_r);
}
void on_high_r_thresh_trackbar(int, void *)
{
	high_r = max(high_r, low_r + 1);
	setTrackbarPos("High R", "RGB", high_r);
}
void on_low_g_thresh_trackbar(int, void *)
{
	low_g = min(high_g - 1, low_g);
	setTrackbarPos("Low G", "RGB", low_g);
}
void on_high_g_thresh_trackbar(int, void *)
{
	high_g = max(high_g, low_g + 1);
	setTrackbarPos("High G", "RGB", high_g);
}
void on_low_b_thresh_trackbar(int, void *)
{
	low_b = min(high_b - 1, low_b);
	setTrackbarPos("Low B", "RGB", low_b);
}
void on_high_b_thresh_trackbar(int, void *)
{
	high_b = max(high_b, low_b + 1);
	setTrackbarPos("High B", "RGB", high_b);
}
