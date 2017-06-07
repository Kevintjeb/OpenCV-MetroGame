#include "Vision.h"
#include "RenderableOutput.h"
using namespace mg_gameLogic;

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

	setTrackbarPos("Low Hue", "TrackBars", 0);
	setTrackbarPos("High Hue", "TrackBars", 11);
	setTrackbarPos("Low Saturation", "TrackBars", 10);
	setTrackbarPos("High Saturation", "TrackBars", 202);
	setTrackbarPos("Low Value", "TrackBars", 75);
	setTrackbarPos("High Value", "TrackBars", 255);

	setTrackbarPos("Low Red", "TrackBars", 208);
	setTrackbarPos("High Red", "TrackBars", 255);
	setTrackbarPos("Low Green", "TrackBars", 0);
	setTrackbarPos("High Green", "TrackBars", 227);
	setTrackbarPos("Low Blue", "TrackBars", 31);
	setTrackbarPos("High Blue", "TrackBars", 142);
	redSettings = colourCalibrate();

	low_v = 254, low_s = 161, low_h = 77;
	high_v = 255, high_s = 255, high_h = 126;

	low_r = 0, low_g = 235, low_b = 188;
	high_r = 97, high_g = 255, high_b = 247;
	greenSettings = colourCalibrate();

	low_v = 51, low_s = 144, low_h = 35;
	high_v = 222, high_s = 255, high_h = 136;

	low_r = 0, low_g = 0, low_b = 99;
	high_r = 255, high_g = 99, high_b = 255;
	blueSettings = colourCalibrate();
}

Vision::ColourSettings Vision::colourCalibrate()
{
	Mat frame, frame_threshold, frame_rgb;

	while ((char)waitKey(1) != 'q') {
		cap >> frame;
		if (frame.empty())
			break;

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
		int dilation_size = 7;
		int erosion_size = 5;

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
	cap.open(1);
	cap >> image;
	// De afbeelding converteren naar een grijswaarde afbeelding
	Mat hsv_image;
	cvtColor(image, hsv_image, CV_BGR2HSV);

	//namedWindow("HSV image", WINDOW_AUTOSIZE);
	//imshow("HSV image", hsv_image);

	// Seperate Colors with inRange
	cv::Mat lower_red_hue_range;
	cv::Mat upper_red_hue_range;
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
	cv::inRange(hsv_image, cv::Scalar(greenSettings.low_h, greenSettings.low_s, greenSettings.low_v), cv::Scalar(blueSettings.high_h, blueSettings.high_s, blueSettings.high_v), green_hue_image);

	//RGB
	cv::Mat red_rgb_image;
	cv::inRange(image, cv::Scalar(redSettings.low_b, redSettings.low_g, redSettings.low_r), cv::Scalar(redSettings.high_b, redSettings.high_g, redSettings.high_r), red_rgb_image);

	cv::Mat blue_rgb_image;
	cv::inRange(image, cv::Scalar(blueSettings.low_b, blueSettings.low_g, blueSettings.low_r), cv::Scalar(blueSettings.high_b, blueSettings.high_g, blueSettings.high_r), blue_rgb_image);

	cv::Mat green_rgb_image;
	cv::inRange(image, cv::Scalar(greenSettings.low_b, greenSettings.low_g, greenSettings.low_r), cv::Scalar(blueSettings.high_b, blueSettings.high_g, blueSettings.high_r), green_rgb_image);

	int dilation_size = 7;
	int erosion_size = 5;
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
	std::list<GameLogic::Vec2f> lines;
	if (coords.size() > 0)
	{
		for (int i = 0; i < coords[0].size(); i++)
		{
			GameLogic::Vec2f vector = GameLogic::Vec2f(((coords[0][i]->x / (image.cols / 2.0f)) - 1.0f), (coords[0][i]->y / (image.rows / 2.0f)) - 1.0f);
			lines.push_back(vector);
		}
	}
	Line* pLine = new Line({ { -0.2f, -0.3f },{ 0.3f, -0.7f } });
	allocate_line(pLine);
	return lines;
}

std::list<Vision::CV_Station> Vision::getStations()
{
	Mat frame;
	cap >> frame;
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
		station.location = Vec2f(symbol->get_location_x(0), symbol->get_location_y(0));
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
