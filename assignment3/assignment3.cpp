//201821053 Kim Hyung Jun
//Computer Vision assignment 3
//image stitching

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, const char* argv[]) {

    Mat image1 = imread("/Users/danie/Desktop/image1.JPG");
    Mat image2 = imread("/Users/danie/Desktop/image2.JPG");

    Mat grey1, grey2;
    cvtColor(image1, grey1, COLOR_BGR2GRAY);
    cvtColor(image2, grey2, COLOR_BGR2GRAY);

    Ptr<ORB> orb = ORB::create();

    vector<KeyPoint> kp1, kp2;
    Mat des1, des2;

    orb->detectAndCompute(grey1, noArray(), kp1, des1);
    orb->detectAndCompute(grey2, noArray(), kp2, des2);

    vector<DMatch> matches;
    BFMatcher matcher(NORM_HAMMING, true);
    matcher.match(des1, des2, matches);

    Mat matchImg;

    sort(matches.begin(), matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() + 100);

    drawMatches(image1, kp1, image2, kp1, good_matches, matchImg);

    vector<Point2f> points1, points2;
    for (int i = 0; i < good_matches.size(); i++) {
        points1.push_back(featurePoints1[good_matches[i].queryIdx].pt);
        points2.push_back(featurePoints2[good_matches[i].trainIdx].pt);
    }

    Mat Homograpy = findHomography(pts1, pts2, RANSAC);
    Mat result;
    
    warpPerspective(image2, result, Homograpy.inv(), Size(image2.cols + image1.cols, image2.rows + image1.rows));
    Mat concat(result, Rect(0, 0, targetImg.cols, targetImg.rows));
    targetImg.copyTo(concat);

    imshow("result_img", result);


    waitKey(0);

    return 0;

}
