#include <iostream>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;



void featureDetection(const Mat &img_1, vector<Point2f> &points) {

    Ptr<Feature2D> orb = ORB::create(500);

    std::vector<KeyPoint> keypoints;

    Mat descriptors;
    orb->detectAndCompute(img_1, Mat(), keypoints, descriptors);

    vector<Point2f> points_extracted;

    for( size_t i = 0; i < keypoints.size(); i++ ) {
        points.emplace_back(keypoints[i].pt);
    }



//    goodFeaturesToTrack(img_1, points, 500, 0.09, 7, Mat(), 7, 3, 0, 0.04);
}





int main(int argc, char **argv) {


    Mat frame_grey;
    VideoCapture cap("../../files/test.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }


    while(1){

        Mat frame;
        vector<Point2f> points1, points2;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;


        cvtColor(frame, frame_grey, COLOR_BGR2GRAY);
        featureDetection(frame_grey , points1);

        for( size_t i = 0; i < points1.size(); i++ )
        {


            cv::circle( frame, Point2f(int(points1[i].x),int(points1[i].y)), 1, Scalar(0,0,255), 3, 8, 0 );
        }
        // Display the resulting frame
        imshow( "Frame", frame );

        // Press  ESC on keyboard to exit
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;
}