#include <iostream>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;


class Extractor {

public:
    Ptr<Feature2D> orb = ORB::create(500);
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    Mat last_descriptor ;
    std::vector<KeyPoint> last_keypoints;

    void extract(Mat &img , vector< Point2f> &src_points ,  vector< Point2f> &dst_points){
        std::vector<KeyPoint> keypoints;

        Mat descriptors;
        std::vector< std::vector<DMatch> > matches;

        orb->detectAndCompute(img, Mat(), keypoints, descriptors);

        if(!last_descriptor.empty()){

            matcher->knnMatch( descriptors, last_descriptor, matches, 2 );

            const float ratio_thresh = 0.7f;

            for (size_t i = 0; i < matches.size(); i++)
            {
                if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
                {
                    src_points.push_back(keypoints[matches[i][0].queryIdx].pt);
                    dst_points.push_back(last_keypoints[matches[i][0].trainIdx].pt);
                }
            }

            cout<<src_points.size()<<endl;
            Mat F , mask;
            F = findFundamentalMat(dst_points, src_points,RANSAC, 0.3/460, 0.99, mask);

            for (int j = 0; j < mask.rows; ++j) {
                if(mask.at<double>(j,0) == 0){
                    src_points.erase(src_points.begin() + j);
                    dst_points.erase(dst_points.begin() + j);
                }
            }
            cout<<src_points.size()<<endl;

        }
        last_descriptor = descriptors;
        last_keypoints =  keypoints;
    }




};








int main(int argc, char **argv) {


    Mat frame_grey;
    Mat F, mask;

    VideoCapture cap("../../files/test.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    Extractor extractor1;

    while(1){

        Mat frame;
        vector< cv::DMatch > goodMatches;

        vector< Point2f> src_points ;
        vector< Point2f> dst_points;
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;


        cvtColor(frame, frame_grey, COLOR_BGR2GRAY);
        extractor1.extract(frame_grey  , src_points ,dst_points);

        for( size_t i = 0; i < src_points.size(); i++ )
        {
            cv::circle( frame, Point2f(int(src_points[i].x),int(src_points[i].y)), 1, Scalar(0,0,255), 3, 8, 0 );
            cv::circle( frame, Point2f(int(dst_points[i].x),int(dst_points[i].y)), 1, Scalar(0,255,0), 3, 8, 0 );

            cv::line(frame,Point2f(int(src_points[i].x),int(src_points[i].y)),Point2f(int(dst_points[i].x),int(dst_points[i].y)),Scalar(255,0,0),2);
        }

//        if(!src_points.empty()){
//
//            F = findFundamentalMat(dst_points, src_points,RANSAC, 0.3/460, 0.99, mask);
//
//            cout<<src_points.size()<<endl;
//            cout<<" Inlier " <<mask.size()<<endl;
//            cout<<F<<endl;
//        }


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