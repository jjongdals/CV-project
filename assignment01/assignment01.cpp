//컴퓨터비전 과제1 디지털미디어학과 201921782 박종원
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int cnt = 0;

Mat hough_circles(Mat input) {
    
    Mat grey, blurred;
    
    cvtColor(input, grey, COLOR_BGR2GRAY);
    grey = (grey-50)*1.3; //대비 높임
    GaussianBlur(grey, blurred, Size(9,9), 3);
    
    vector<Vec3f> circles;
    
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1.3, 40, 120, 50, 35, 130);

    for(Vec3f c : circles) {
        Point center(cvRound(c[0]), cvRound(c[1])); 
        int radius = cvRound(c[2]); 
        circle(input, center, 3, Scalar(0,255,0), -1, 8, 0); 
        circle(input, center, radius, Scalar(0,0,255), 3, 8, 0); 
    }
    
    cout << "Number of coins in input" << cnt << " : " << circles.size() << endl;
    cnt++;
    
    return input;
    
}

int main(int argc, const char * argv[]) {
    
    Mat input0 = imread("/Users/parkjongwon/Desktop/coins0.jpg");
    Mat input1 = imread("/Users/parkjongwon/Desktop/coins1.jpg");
    Mat input2 = imread("/Users/parkjongwon/Desktop/coins2.jpg");
    Mat input3 = imread("/Users/parkjongwon/Desktop/coins3.jpg");
    Mat input4 = imread("/Users/parkjongwon/Desktop/coins4.jpg");
    Mat input5 = imread("/Users/parkjongwon/Desktop/coins5.jpg");
    
    Mat result0 = hough_circles(input0);
    Mat result1 = hough_circles(input1);
    Mat result2 = hough_circles(input2);
    Mat result3 = hough_circles(input3);
    Mat result4 = hough_circles(input4);
    Mat result5 = hough_circles(input5);
    
    imshow("result0", result0);
    imshow("result1", result1);
    imshow("result2", result2);
    imshow("result3", result3);
    imshow("result4", result4);
    imshow("result5", result5);
    
    waitKey();
    
    return 0;
}