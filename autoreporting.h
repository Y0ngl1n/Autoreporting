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

namespace Ui {
class autoreporting;
}

class autoreporting : public QWidget
{
    Q_OBJECT
private:
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
    cv::Mat image_ba;
    QPixmap *pixmap;
    QTimer *timer_calendar;
    //初始化摄像头
    void iniCamera();
    //初始化摄像头（Opencv）
    void iniCameraopencv();
    //初始化ViewFinder
    void iniViewFinder();
public:
    //靶心圆心坐标
    cv::Point2f center_point;
    //最终成绩
    int score;
    //返回的激光坐标点
    cv::Point2f pos;
    //激光点与靶心距离
    double distance;
    //原图
    cv::Mat srcImage;
    //背景图
    cv::Mat src;
    explicit autoreporting(QWidget *parent = 0);
    ~autoreporting();

private slots:
    void on_comboBox_cameralist_activated(int index);

    void on_button_ok_clicked();

    void on_button_close_clicked();

    void on_button_grab_clicked();

    //slot：处理捕获的图片
    void imageProcess(int id,QImage image);

    //成员函数：QImage转化为Mat格式的图片
    cv::Mat QImageToMat(QImage &image);
    void on_pushButton_clicked();

private:
    Ui::autoreporting *ui;
};

#endif // AUTOREPORTING_H
