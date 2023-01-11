// Computer Vision assigment1
// 201821053, Kim Hyung Jun

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

vector<Mat> GaussianPyramid(Mat img, int depth = 5) {
    vector<Mat> pyramid;
    Mat src = img;

    for (int i = 0; i < depth; i++) {
        Mat correctImg;
        pyrDown(img, correctImg);
        pyramid.push_back(correctImg);
        img = correctImg;
    }
    return pyramid;
}
vector<Mat> LaplacianPyramid(Mat img, int depth = 5) {
    vector<Mat> pyramid;
    Mat src = img;

    for (int i = 0; i < depth; i++) {
        Mat small, temp;
        pyrDown(src, small);
        pyrUp(small, temp, src.size());
        pyramid.push_back(src - temp);
        src = small;

    }
    pyramid.push_back(src);
    return pyramid;
}
Mat reconstruct(const vector<Mat>& pyramid) {
    Mat ret = pyramid.back();
    for (int i = pyramid.size() - 2; i >= 0; i--) {
        pyrUp(ret, ret, pyramid[i].size());
        ret += pyramid[i];
    }
    return ret;
}
Mat blend(Mat img1, Mat img2, Mat mask) {
    Mat mul1, mul2, mask2, sum;
    multiply(img1, mask, mul1);
    mask2 = Scalar::all(1) - mask;
    multiply(img2, mask2, mul2);

    add(mul1, mul2, sum);
    return sum;

}
int main()
{
    Mat image1 = imread("C:/Users/danie/Desktop/apple.jpg");
    Mat image2 = imread("C:/Users/danie/Desktop/orange.jpg");
    Mat mask = imread("C:/Users/danie/Desktop/mask.png");
    image1.convertTo(image1, CV_32F, 1 / 255.f);
    image2.convertTo(image2, CV_32F, 1 / 255.f);
    mask.convertTo(mask, CV_32F, 1 / 255.f);

    const int depth = 5;
    auto maskPyr = GaussianPyramid(mask, depth);
    auto image1Pyr = LaplacianPyramid(image1, depth);
    auto image2Pyr = LaplacianPyramid(image2, depth);
    vector<Mat> blendImg;

    for (int i = 0; i < depth; i++) {
        auto temp = blend(image1Pyr[i], image2Pyr[i], maskPyr[i]);
        blendImg.push_back(temp);
    }

    Mat multiblend = reconstruct(blendImg);
    imshow("mutiblend", multiblend);
    waitKey();

}


