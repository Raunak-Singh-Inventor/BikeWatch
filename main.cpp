#include "opencv2/opencv.hpp"
#include <iostream>
#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <vitis/ai/demo.hpp>
#include <vitis/ai/refinedet.hpp>

using namespace cv;

int main(int argc, char** argv) {
    VideoCapture cap(0); // open default camera

    // load network using Vitis AI RefineDet library
    auto network = vitis::ai::RefineDet::create("refinedet_pruned_0_8");

//    while(true) {
      Mat frame;
      cap >> frame;
      //Resizing for RefineDet 360 by 480
      resize(frame, frame, Size(360,480));

	    auto results = network->run(frame); // run the network on the image

      //Draw boxes around results
	    for (const auto &r : results.bboxes) {
        int x1 = r.x * frame.cols;
        int y1 = r.y * frame.rows;
        int x2 = x1 + (r.width * frame.cols);
        int y2 = y1 + (r.height * frame.rows);
        Point pt1(x1, y1);
        Point pt2(x2, y2);
        cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0));
      }

      if(results.bboxes.size()==0) {
        std::cout << "0";
      } else {
        std::cout << "1";
      }

      resize(frame, frame, Size(360,480));
      

//      if( waitKey(10) == 27 ) break;
//    }
}
