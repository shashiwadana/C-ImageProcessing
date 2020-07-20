


#include <iostream>

#include <opencv2/core/core.hpp>

#include <opencv2/opencv.hpp>

#include<opencv2/imgproc/imgproc.hpp>



using namespace cv;

using namespace std;





int main(int argc, char* argv[])

{

    if (argc != 2) {

        printf("Enter exeFileName imageFileName\n");

    }



    Mat image = imread(argv[1], IMREAD_COLOR);



    if (image.empty()) {

        cout << "Error: No Image to load" << endl;

    }



    Mat gr(image.rows, image.cols, CV_8UC1, Scalar(0));

    cvtColor(image, gr, COLOR_BGR2GRAY);



    // allcoate memory for all the intensity values

    int histogram[256];

    double prob[256];

    double cprob[256];

    int cNew[256];

    int equalizedHist[256];





    // initialize all intensity values to 0

    for (int i = 0; i < 256; i++)

    {

        histogram[i] = 0;

        prob[i] = 0.0;

        cprob[i] = 0.0;

        cNew[i] = 0;

        equalizedHist[i] = 0;



    }



    int t1 = 0;

    int t2 = 0;



    // calculate no of pixels for each intensities

    for (int i = 0; i < image.rows; i++)

    {

        for (int j = 0; j < image.cols; j++)

        {

            t1 = (int)gr.at<uchar>(i, j);

            histogram[t1] = histogram[t1] + 1;

        }

    }



    /*for (int i = 0; i < 256; i++)

    {

        cout << histogram[i] << endl;

    }*/





    //total number of pixels

    int N = gr.rows * gr.cols;



    //Calculate the probability of each intensity

    for (int i = 0; i < 256; i++) {

        prob[i] = (double)histogram[i] / N;

    }



    cprob[0] = prob[0];

    //Generate cumulative probability

    for (int i = 1; i < 256; i++) {

        cprob[i] = cprob[i - 1] + prob[i];

    }



    /*for (int i = 0; i < 256; i++) {

        printf("%f\n", cprob[i]);

    }*/



    //Scale cumulative probability

    for (int i = 0; i < 256; i++) {

        cNew[i] = cvRound(cprob[i] * 255);

    }



    Mat copy = gr.clone();



    int z;

    for (int k = 0; k < image.rows; k++)

    {

        for (int l = 0; l < image.cols; l++)

        {

            z = (int)cNew[gr.at<uchar>(k, l)];

            copy.at<uchar>(k, l) = (uchar)z;

        }

    }



    for (int k = 0; k < image.rows; k++)

    {

        for (int l = 0; l < image.cols; l++)

        {

            t2 = (int)copy.at<uchar>(k, l);

            equalizedHist[t2] = equalizedHist[t2] + 1;

        }

    }



    for (int i = 0; i < 256; i++) {

        printf("%d\n", equalizedHist[i]);

    }



    int hist_w = 512;

    int hist_h = 400;



    //draw the histogram

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));

    Mat orgImage(hist_h, hist_w, CV_8UC1, Scalar(255));



    int max = equalizedHist[0];

    for (int i = 0; i < 256; i++) {

        if (max < equalizedHist[i]) {

            max = equalizedHist[i];

        }

    }



    int omax = histogram[0];

    for (int i = 0; i < 256; i++) {

        if (omax < histogram[i]) {

            omax = histogram[i];

        }

    }



    //normalize the histogram

    for (int i = 0; i < 256; i++) {

        equalizedHist[i] = ((double)equalizedHist[i] / max) * histImage.rows;

    }



    for (int i = 0; i < 256; i++) {

        histogram[i] = ((double)histogram[i] / omax) * orgImage.rows;

    }



    int bin_w = cvRound((double)hist_w / 256);



    //draw intensity line for histogram

    for (int i = 0; i < 256; i++) {

        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - equalizedHist[i]), Scalar(0), 1, 8, 0);

    }



    for (int i = 0; i < 256; i++) {

        line(orgImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0), 1, 8, 0);

    }





    namedWindow("Gray Image", 1);

    imshow("Gray Image", gr);



    namedWindow("Equalized Image", 1);

    imshow("Equalized Image", copy);



    namedWindow("Equalized histogram", 1);

    imshow("Equalized histogram", histImage);



    namedWindow("Original histogram", 1);

    imshow("Original histogram", orgImage);



    waitKey();

    gr.release();

    copy.release();

    histImage.release();

    orgImage.release();

    return 0;

}

