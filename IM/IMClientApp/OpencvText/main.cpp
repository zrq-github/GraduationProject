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
        Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��  
        capture >> frame;  //��ȡ��ǰ֡                          
        if (frame.empty())
        {
            break;
        }
        else
        {
            cvtColor(frame, edges, CV_BGR2GRAY);//��ɫת���ɻҶ�  
            blur(edges, edges, Size(7, 7));//ģ����  
            Canny(edges, edges, 0, 30, 3);//��Ե��  
            imshow("Video", frame); //��ʾ��ǰ֡  
        }
        waitKey(30); //��ʱ30ms 
    }

    capture.release();//�ͷ���Դ
    destroyAllWindows();//�ر����д���
    return a.exec();
}
