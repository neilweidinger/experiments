#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Provide image file name!\n";
        return 1;
    }

    cv::Mat img = cv::imread(argv[1], -1);

    if (img.empty()) {
        std::cout << "Error reading image\n";
        return 2;
    }

    cv::namedWindow("Test window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Test window", img);

    cv::waitKey(0);
    cv::destroyWindow("Test window");

    return 0;
}
