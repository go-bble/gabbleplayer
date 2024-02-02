#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <QApplication>
#include <mainwindow.h>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}

void test_lib();

int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);

	MainWindow* window = new MainWindow();
	window->show();

    test_lib();
    return app.exec();
}


void test_lib(){
       // 读取图像
    cv::Mat image = cv::imread("C:\\Users\\61061\\Pictures\\1111.png");

    // 检查图像是否成功读取
    if (image.empty()) {
        std::cerr << "Error: Unable to read the image." << std::endl;
        return ;
    }

    // 显示原始图像
    cv::imshow("Original Image", image);
    cv::waitKey(0);

    // 转换为灰度图
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 显示灰度图像
    cv::imshow("Gray Image", grayImage);
    cv::waitKey(0);

    // 进行简单的边缘检测
    cv::Mat edges;
    cv::Canny(grayImage, edges, 50, 150);

    // 显示边缘图像
    cv::imshow("Edges", edges);
    cv::waitKey(0);


    std::cout << "FFmpeg version: " << av_version_info() << std::endl;
}