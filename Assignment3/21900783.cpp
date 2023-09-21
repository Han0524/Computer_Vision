#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    //get the image
    Mat moon = imread("Moon.jpeg", 0); //load image for gray scale(input)
    Mat salt = imread("saltnpepper.png", 0); //load image image for gray scale(input)
    Mat moon_filtered, moon_blur, salt_filtered;
    int k = 5;//scale(이 값이 클수록 차이가 더 극명하게 갈림)

    if(moon.empty()){
        cout << "Could not open or find the image1" << endl;
        return -1;
    }
    if(salt.empty()){
        cout << "Could not open or find the image2" << endl;
        return -1;
    }

    //clone for each image for result
    moon_blur = moon.clone();
    moon_filtered = moon.clone();
    salt_filtered = salt.clone();

    //get width, height and calculate rect1,2
    int h1 = moon.rows;
    int w1 = moon.cols;
    int h2 = salt.rows;
    int w2 = salt.cols;

    Rect rect1(w1/2,0,w1/2,h1);
    Rect rect2(0,0,w2/2,h2); 

    //sharpening for moon
    /*
    GaussianBlur(moon(rect1), moon_filtered(rect1), Size(3,3), 0, 0, BORDER_DEFAULT);
    Laplacian(moon(rect1), moon_lap, CV_16S, 1, 1, 0);
    convertScaleAbs(moon_lap, moon_abslap);
    moon_filtered(rect1) = moon_abslap+moon(rect1);
    */
    GaussianBlur(moon(rect1), moon_blur(rect1), Size(3,3), 0, 0, BORDER_DEFAULT);//blur the image
    moon_filtered(rect1) = (1+k)*(moon(rect1)) - k*(moon_blur(rect1));
    
    //median blur for saltnpepper
    medianBlur(salt(rect2), salt_filtered(rect2), 9);


    //display the result
    imshow("moon", moon);//show the input image for screen
    imshow("saltnpepper", salt);//show the output image for screen
    imshow("moon_filtered", moon_filtered);//show the input image for screen
    imshow("saltnpepper_filtered", salt_filtered);//show the output image for screen
    
    waitKey(0);
}