#include <opencv2/core/utility.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << cv::getBuildInformation() << std::endl;
    return 0;
}
