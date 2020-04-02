#include "OpencvText.h"
#include <QtWidgets/QApplication>
#include<opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //OpencvText w;
    //w.show();
    VideoCapture capture(0);
    if (!capture.isOpened())
        return 0;

    Mat edges;
    while (1)
    {
        Mat frame; //定义一个Mat变量，用于存储每一帧的图像  
        capture >> frame;  //读取当前帧                          
        if (frame.empty())
        {
            break;
        }
        else
        {
            cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度  
            blur(edges, edges, Size(7, 7));//模糊化  
            Canny(edges, edges, 0, 30, 3);//边缘化  
            imshow("Video", frame); //显示当前帧  
        }
        waitKey(30); //延时30ms 
    }

    capture.release();//释放资源
    destroyAllWindows();//关闭所有窗口
    return a.exec();
}
