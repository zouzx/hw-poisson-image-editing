#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int px, py;
Mat img, src_img, mask;
void on_mouse(int event, int x, int y, int flags, void* param){
    static int sx, sy;
    if (event == CV_EVENT_LBUTTONDOWN){
        sx = x;
        sy = y;
        circle(img, Point(x, y), 1, Scalar(0, 255, 0));
        circle(mask, Point(x, y), 1, Scalar::all(255));
        imshow("get_mask", img);
    }
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON)){
        circle(img, Point(x, y), 1, Scalar(0, 255, 0));
        circle(mask, Point(x, y), 1, Scalar::all(255));
        line(img, Point(px, py), Point(x, y), Scalar(0, 255, 0));
        line(mask, Point(px, py), Point(x, y), Scalar::all(255));
        imshow("get_mask", img);
    }
    else if (event == CV_EVENT_LBUTTONUP){
        line(img, Point(px, py), Point(x, y), Scalar(0, 255, 0));
        line(mask, Point(px, py), Point(x, y), Scalar::all(255));
        line(img, Point(sx, sy), Point(x, y), Scalar(0, 255, 0));
        line(mask, Point(sx, sy), Point(x, y), Scalar::all(255));
        imshow("get_mask", img);
        std::vector<std::vector<cv::Point> > contours;
        vector<Vec4i> hierarchy;
        cv::findContours( mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );  

        mask.setTo(cv::Scalar::all(0));  
        cv::drawContours( mask, contours, -1, cv::Scalar(255), CV_FILLED );  

        //cv::Mat color_tab;  
        std::cout << contours.size() << std::endl;
        Mat result;
        src_img.copyTo(result, mask);
        imshow("mask", result);
    }
    px = x;
    py = y;
}
int main(int argc, char **argv){
    if (argc != 2){
        cout << "please input image path!" << endl;
        return 0;
    }
    src_img = imread(argv[1], 1);
    src_img.copyTo(img);
    mask = Mat(img.size(), CV_8U, Scalar::all(0));
    namedWindow("get_mask", WINDOW_NORMAL);
    setMouseCallback("get_mask", on_mouse);
    imshow("get_mask", img);
    while (1){
        char q = waitKey(0);
        if (q == 'y'){
            cout << "saving mask ..." << endl;
            imwrite("mask.jpg", mask);
            break;
        }
        else{
            destroyWindow("mask");
            src_img.copyTo(img);
            mask = Mat(img.size(), CV_8U, Scalar::all(0));
        }
    }

    return 0;
}