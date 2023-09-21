#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat image = imread("Lena.png", 0); //image for gray scale(input)
    Mat resize_img; //image for manipulate image(output)
    float gamma = 10;
    unsigned char pix[256];

    if(image.empty()){
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    resize(image, resize_img, Size(image.rows, image.cols));//resize the image
    
    //rotate the image for 90 degree
    for(int j = 0; j < image.rows; j++){
        for(int i = 0; i < image.cols; i++){
            resize_img.at<uchar>(image.cols-i, j) = image.at<uchar>(j, i);
        }
    }
    //rotate(output_image, output_image, ROTATE_90_CLOCKWISE);

    //calculate gamma value
    for(int i = 127; i < 256; i++){
        pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }

    
    //apply negative transformation that pixel value is smaller than 127/gamma transformation that pixel value is bigger than 127
    for(int j = 0; j < resize_img.rows; j++){
        for(int i = 0; i < resize_img.cols; i++){
            //resize_img.at<uchar>(j, i) = image.at<uchar>()
            if(resize_img.at<uchar>(j, i) < 127){//pixel value is smaller than 127 -> negative transformation
                resize_img.at<uchar>(j,i) = 255 - resize_img.at<uchar>(j,i);
            }
            else{//pixel value is bigger than 127 -> gamma transformation
                resize_img.at<uchar>(j,i) = pix[resize_img.at<uchar>(j,i)];
            }
        }
    }


    imshow("gray image", image);//show the input image for screen
    imshow("result", resize_img);//show the output image for screen
    

    waitKey(0);
}