#ifndef AUTOREPORTING_H
#define AUTOREPORTING_H

#include<QWidget>
#include<QCamera>
#include<QCameraInfo>
#include<QCameraImageCapture>
#include<QMediaRecorder>
#include<QDebug>
#include<QList>
#include<ctime>
#include <QTimer>
#include"opencv2/opencv.hpp"
#include<iostream>
#include<QDateTime>
namespace Ui {
class autoreporting;
}

class autoreporting : public QWidget
{
    Q_OBJECT
private:
    //当前帧索引
    int m_frameIndex = 0;
    //当前摄像头
    QCamera *currentCamera;
    //摄像头列表
    QList<QCameraInfo> cameras;
    //ViewFinder
    QCameraViewfinderSettings viewfinderSettings;
    //图像捕捉器
    QCameraImageCapture *imageCapture;
    //摄像头索引
    int cameraIndex;
    //上一帧
    cv::Mat preFrameImage;
    //当前帧
    cv::Mat curFrameImage;
    QAbstractVideoSurface* surface;

    cv::Mat image_ba;

    QPixmap *pixmap;

    QTimer *timer_calendar;
    //初始化摄像头
    void iniCamera();
    //初始化摄像头（Opencv）
//    void iniCameraopencv();
    //初始化ViewFinder
    void iniViewFinder();

public:
    //靶心圆心坐标
    cv::Point2f center_point;
    //最终成绩
    int score;
    //最佳成绩
    int scoreBest;
    //平均成绩
    double scoreAverage;
    //总环数
    int scoreTotal;
    //返回的激光坐标点
    cv::Point2f pos;
    //激光点与靶心距离
    double distance;
    //原图
    cv::Mat srcImage;
    //背景图
    cv::Mat src;
    //每次转换相机位置后的转换矩阵
    cv::Mat warpR;
    //总射击次数
    int shootRound=0;
    explicit autoreporting(QWidget *parent = 0);
    ~autoreporting();

private slots:
    void on_comboBox_cameralist_activated(int index);

    void on_button_ok_clicked();

    void on_button_close_clicked();

    void on_button_grab_clicked();

    void timerUpdate();

    //slot：处理捕获的图片
    void imageProcess(int id,QImage image);
    void rcvImage(QImage image);
    //成员函数：QImage转化为Mat格式的图片
    cv::Mat QImageToMat(QImage &image);

    void on_pushButton_clicked();

    void on_button_quit_clicked();

    void on_button_grab_2_clicked();

private:
    Ui::autoreporting *ui;
};

#endif // AUTOREPORTING_H
