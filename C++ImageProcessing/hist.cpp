
#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;

using namespace std;

int main(int argc, char** argv)

{

	if (argc != 2)

	{

		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;

		return -1;

	}

	Mat image;

	image = imread(argv[1], IMREAD_COLOR); // Read the file

	if (!image.data) // Check for invalid input

	{

		cout << "Could not open or find the image" << std::endl;

		return -1;

	}

	Mat gr;

	int his[256];

	for (int i = 0; i < 256; i++) {

		his[i] = 0;

	}

	cvtColor(image, gr, cv::COLOR_BGR2GRAY, 0);

	int h = gr.rows;

	int w = gr.cols;

	int val = 0;

	cout << "Width: " << w << endl;

	cout << "Height: " << h << endl;

	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++) {

			val = gr.at<uchar>(i, j);

			his[val] = his[val] + 1;

		}

	}

	int max = 0;

	for (int i = 0; i < 256; i++) {

		cout << "Gray level " << i << ": " << his[i] << endl;

		if (max < his[i])

			max = his[i];

	}

	cout << max << endl;

	Mat him(301, 260, CV_8UC1, Scalar(255));

	int hist[256];

	double maxd = max;

	for (int i = 0; i <= 255; i++) {

		hist[i] = cvRound(double(his[i] / maxd) * 300);

		Point pt1 = Point(i, 300 - hist[i]);

		Point pt2 = Point(i, 300);

		line(him, pt1, pt2, Scalar(0), 1, 8, 0);

	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.

	imshow("Display window", image); // Show our image inside it.

	namedWindow("Display Gray", WINDOW_AUTOSIZE); // Create a window for display.

	imshow("Display Gray", gr); // Show our image inside it.

	namedWindow("Display Histogram", WINDOW_AUTOSIZE); // Create a window for display.

	imshow("Display Histogram", him); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window

	image.release();

	gr.release();

	him.release();

	return 0;

}

