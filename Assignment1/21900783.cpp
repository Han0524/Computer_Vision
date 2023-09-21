#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat frame;
    VideoCapture cap;
    int fps;//Frame rate
    int total_frame;//total frame
    int delay;

    if(cap.open("background.mp4") == 0){//if file is not exist
        cout << "No file" << endl;
        return -1;
    }
    
    fps = cap.get(CAP_PROP_FPS);//get frame rate
    total_frame = cap.get(CAP_PROP_FRAME_COUNT);//get total frame for video
    delay = 1000/fps;//calculate delay time

    while(cap.get(CAP_PROP_POS_MSEC) < 3000){
        cap >> frame;
        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        cout << "frame : " << cap.get(CAP_PROP_POS_FRAMES) << " / " << total_frame << endl;
        imshow("video", frame);
        waitKey(delay);
    }
    

}