#include "autoreporting.h"
#include "ui_autoreporting.h"


using namespace std;
using namespace cv;

//初始化摄像头
void autoreporting::iniCamera()
{
    cameras=QCameraInfo::availableCameras();
    foreach(const QCameraInfo &cameraInfo, cameras)
        {
            qDebug() << "CameraInfo:" << cameraInfo;
            ui->comboBox_cameralist->addItem(cameraInfo.description());

    }
}

void autoreporting::iniCameraopencv()
{
    VideoCapture cap(0);
    Mat frame;
    //打开失败
        if (!cap.isOpened()) {
            cerr << "Cannot open camera";
        }
        //打开成功
        while (true) {
            //读取视频帧
            cap.read(frame);
            //显示图像
            imshow("Pig", frame);
            waitKey(1000);
        }
        cap.release();
}

//初始化ViewFinder
void autoreporting::iniViewFinder()
{
    QCameraViewfinderSettings viewfinderSettings;
    viewfinderSettings.setResolution(1920, 1080);
    viewfinderSettings.setMinimumFrameRate(30.0);
    viewfinderSettings.setMaximumFrameRate(30.0);
}

//构造函数
autoreporting::autoreporting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::autoreporting)
{
    ui->setupUi(this);
//    iniCameraopencv();
    //初始化相机
    iniCamera();

    //初始化ViewFinder
    iniViewFinder();
    pos.x=0;
    pos.y=0;
    //靶心圆心坐标
    center_point.x=0;
    center_point.y=0;
    //最终成绩
    score=0;
    //激光点与靶心距离
    distance=0.0;
}

autoreporting::~autoreporting()
{
    delete ui;
}

//摄像头索引
void autoreporting::on_comboBox_cameralist_activated(int index)
{
    cameraIndex=index;
}

//选择摄像头，并给当前摄像头设置参数，启动并初始化图像捕捉器
void autoreporting::on_button_ok_clicked()
{
    if(cameraIndex>10){
        cameraIndex=0;
    }
        qDebug()<<"Index"<< cameraIndex <<": "<< ui->comboBox_cameralist->currentText();
        currentCamera = new QCamera(cameras[cameraIndex]);//设定摄像头
        currentCamera->setViewfinderSettings(viewfinderSettings);
        currentCamera->setViewfinder(ui->widget);
        currentCamera->setCaptureMode(QCamera::CaptureViewfinder);
        currentCamera->start();//启动摄像头
        imageCapture=new QCameraImageCapture(currentCamera,this);
        imageCapture->setBufferFormat(QVideoFrame::Format_Jpeg);
        imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
        if(currentCamera->captureMode()!=QCamera::CaptureStillImage)
        {
            currentCamera->setCaptureMode(QCamera::CaptureStillImage);
        }
        //链接 捕捉图像发出imageCaptured((int,QImage))信号，imageProcess(int id, QImage image)槽函数接收
        connect(imageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(imageProcess(int, QImage)));
}

//关闭当前摄像头
void autoreporting::on_button_close_clicked()
{
    currentCamera->stop();
}

//捕捉图像
void autoreporting::on_button_grab_clicked()
{
    imageCapture->capture();
    qDebug()<<"Grabed";
}

//定义槽函数imageProcess(int id, QImage image)，处理捕获的图像
void autoreporting::imageProcess(int id,QImage image)
{
    qDebug()<<id;
//    image.save("E:/qtproject/Autoreporting/image.jpg");
    //原图QImage格式需要转换成Mat格式 QImage -> Mat
    srcImage=QImageToMat(image);
//    srcImage=imread("C:/Users/Lelia/Pictures/1.jpg");
//    namedWindow("original image",WINDOW_NORMAL);
//    imshow("original image",srcImage);
    //灰度图
    Mat gray_image;
    cvtColor(srcImage, gray_image, COLOR_BGR2GRAY);
//    namedWindow("gray image",WINDOW_NORMAL);
//    imshow("gray image",gray_image);
    Scalar meanValue = mean(gray_image); // 计算灰度图像的平均灰度值
    cout<<"Mean gray value:"<<meanValue[0]<<endl;
    if(meanValue[0]<140){
        Mat brightness = Mat::zeros(gray_image.size(),gray_image.type()) + 30;
        add(gray_image, brightness, gray_image);
        double alpha = 1.2; // 对比度增益
        int beta = 0; // 亮度增益
        gray_image.convertTo(gray_image, -1, alpha, beta);
    }
    else if(140<meanValue[0]<150){
        Mat brightness = Mat::zeros(gray_image.size(),gray_image.type()) + 20;
        add(gray_image, brightness, gray_image);
        double alpha = 1.2; // 对比度增益
        int beta = 0; // 亮度增益
        gray_image.convertTo(gray_image, -1, alpha, beta);
    }

//    namedWindow("gray image brighter",WINDOW_NORMAL);
//    imshow("gray image brighter",gray_image);
    //二值化图
    Mat binary_image;
    threshold(gray_image, binary_image, 200, 255, THRESH_BINARY);
//    namedWindow("binary image",WINDOW_NORMAL);
//    imshow("binary image",binary_image);
    //中值滤波图
    Mat blur_image;
    medianBlur(binary_image, blur_image, 5);
//    namedWindow("blur image",WINDOW_NORMAL);
//    imshow("blur image",blur_image);
    //Canny边缘提取图
    Mat edges_image;
    Canny(blur_image, edges_image, 100, 500);
//    namedWindow("canny image",WINDOW_NORMAL);
//    imshow("canny image",edges_image);

//    画出每个轮廓
    vector<vector<Point>> contours;  //储存轮廓
    vector<Vec4i> hierarchy;

    findContours(edges_image, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);  //获取轮廓
    Mat linePic = Mat::zeros(edges_image.rows, edges_image.cols, CV_8UC3);
    for (int index = 0; index < contours.size(); index++){
        drawContours(linePic, contours, index, Scalar(rand() & 255, rand() & 255, rand() & 255), 1, 8/*, hierarchy*/);
    }
    //    imshow("edge IMAGE",linePic);
    //找出最大轮廓
    vector<vector<Point>> polyContours(contours.size());
    int maxArea = 0;
    for (int index = 0; index < contours.size(); index++){
        if (contourArea(contours[index]) > contourArea(contours[maxArea]))
          maxArea = index;
        approxPolyDP(contours[index], polyContours[index], 10, true);
      }
    //最大轮廓图
    Mat polyPic = Mat::zeros(linePic.size(), CV_8UC3);

    //在图上画出这个轮廓
    drawContours(polyPic, polyContours, maxArea, Scalar(0,0,255/*rand() & 255, rand() & 255, rand() & 255*/), 2);
//    namedWindow("Max contour",WINDOW_NORMAL);
//    imshow("Max contour",polyPic);
    //    imshow("edge IMAGE",polyPic);
    //寻找凸包
    vector<int> hull;
    convexHull(polyContours[maxArea], hull, false);  //检测该轮廓的角点
//    namedWindow("Point",WINDOW_NORMAL);
//    imshow("Point",polyPic);
    cout<<polyContours[maxArea][0]<<endl;
        cout<<polyContours[maxArea][1]<<endl;
            cout<<polyContours[maxArea][2]<<endl;
                cout<<polyContours[maxArea][3]<<endl;

    Point2f p1;
    Point2f p2;
    Point2f p3;
    Point2f p4;
    Point2f p_center;
    p_center.x=(polyContours[maxArea][0].x+polyContours[maxArea][2].x)/2;
    p_center.y=(polyContours[maxArea][0].y+polyContours[maxArea][2].y)/2;
        cout<<p_center<<endl;
    for(int i=0;i<4;i++){
        if (polyContours[maxArea][i].x<p_center.x&&polyContours[maxArea][i].y<p_center.y){
            p1=polyContours[maxArea][i];
        }
    }
    for(int i=0;i<4;i++){
        if (polyContours[maxArea][i].x>p_center.x&&polyContours[maxArea][i].y<p_center.y){
            p2=polyContours[maxArea][i];
        }
    }
    for(int i=0;i<4;i++){
        if (polyContours[maxArea][i].x>p_center.x&&polyContours[maxArea][i].y>p_center.y){
            p3=polyContours[maxArea][i];
        }
    }
    for(int i=0;i<4;i++){
        if (polyContours[maxArea][i].x<p_center.x&&polyContours[maxArea][i].y>p_center.y){
            p4=polyContours[maxArea][i];
        }
    }
    cout<<p1<<endl;
        cout<<p2<<endl;
            cout<<p3<<endl;
                cout<<p4<<endl;
//    namedWindow("Point",WINDOW_NORMAL);
//    imshow("Point",polyPic);
    // 起始坐标
    vector<Point2f> org;
    org.push_back(p1);//左上
    org.push_back(p2);//右上
    org.push_back(p3);//右下
    org.push_back(p4);//左下

    // 目标坐标
    vector<Point2f> dst;
    dst.push_back(Point2f(0, 0));
    dst.push_back(Point2f(1485, 0));
    dst.push_back(Point2f(1485, 1050));
    dst.push_back(Point2f(0, 1050));
    //求解转换矩阵
    Mat warpR = getPerspectiveTransform(org, dst);
    Mat blank_image(1050, 1485, CV_8UC3, Scalar(0, 0, 0));

    //透视变换
    warpPerspective(srcImage, srcImage, warpR, blank_image.size());
//    namedWindow("show",WINDOW_NORMAL);
//    imshow("show",srcImage);
    //逆时针旋转90度
    Mat img_rotated;
    rotate(srcImage, img_rotated, ROTATE_90_CLOCKWISE);
    //    namedWindow("result1",WINDOW_NORMAL);
    //    imshow("result1",img_rotated);
    imwrite("result.jpg",img_rotated);

    //差影法求弹孔位置
    src = imread("E:/qtproject/Autoreporting/Background.jpg");
    if (src.empty() || img_rotated.empty()) {
            printf("Could not find image file");
        }
    Mat dst2;
    subtract(img_rotated, src, dst2);//减法操作输入图片1，图片2，输出图片3
    //    namedWindow("result2",WINDOW_NORMAL);
    //    imshow("result2",dst2);

    //转化为灰度图
    Mat dst2_gray;
    cvtColor(dst2, dst2_gray, COLOR_BGR2GRAY);
    //    namedWindow("result3",WINDOW_NORMAL);
    //    imshow("result3", dst2_gray);

    //根据阈值二值化
    Mat dst2_binary;
    threshold(dst2_gray, dst2_binary, 50, 255, THRESH_BINARY);
    //    namedWindow("result1",WINDOW_NORMAL);
    //    imshow("result1", dst2_binary);

    //腐蚀操作
    Mat kernel = getStructuringElement(MORPH_CROSS, Size(9, 9));
    Mat dst2_eroded;
    erode(dst2_binary, dst2_eroded, kernel);
//        namedWindow("result",WINDOW_NORMAL);
//        imshow("result", dst2_eroded);

    //Cannys算子邊緣提取
    Mat dst2_cannys;
    Canny(dst2_eroded, dst2_cannys, 50, 70);
    //显示图像
//    namedWindow("result1",WINDOW_NORMAL);
//    imshow("result1", dst2_cannys);

    //找到弹孔中心点坐标
    vector<vector<Point>> contours2;
    findContours(dst2_cannys, contours2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //找到面积最大的轮廓
    double max_area = 0;
    int max_idx = -1;
    for (int i = 0; i < contours2.size(); i++)
    {
        double area = contourArea(contours2[i]);
        if (area > max_area)
        {
            max_area = area;
            max_idx = i;
        }
    }
    qDebug()<<"max area:"<<max_area;
    if(max_area==0){
        score=0;
        Mat whiteImage(1485, 1050, CV_8UC1, cv::Scalar(255));
    //    namedWindow("result",WINDOW_NORMAL);
        circle(whiteImage, center_point,5,cv::Scalar(0),-1);
        circle(whiteImage, center_point,110,cv::Scalar(0), 5);
        circle(whiteImage, center_point,220,cv::Scalar(0), 3);
        circle(whiteImage, center_point,330,cv::Scalar(0), 3);
        circle(whiteImage, center_point,440,cv::Scalar(0), 3);
        circle(whiteImage, center_point,550,cv::Scalar(0), 3);
        imwrite("result_whiteimage.jpg",whiteImage);
        ui->label_score->setStyleSheet("color: red");
        ui->label_score->setText(QString::number(score));
        QPixmap pix("result_whiteimage.jpg");
        pix = pix.scaled(ui->label_ba->size());
        ui->label_ba->setPixmap(pix);
        ui->list_history->insertItem(id,QString::number(score));
    }
    else
    {
    //找到面积最大的轮廓的中心点坐标
    if (max_idx >= 0)
    {
        Moments mu = moments(contours2[max_idx]);
        double x = mu.m10 / mu.m00;
        double y = mu.m01 / mu.m00;
        // 输出中心点坐标
        pos.x=x;
        pos.y=y;
        cout << "The point is (" << x << ", " << y << ")" << endl;
    }


    //计算激光点与圆心的距离
    center_point.x=519;
    center_point.y=903;
    Mat whiteImage(1485, 1050, CV_8UC1, cv::Scalar(255));
//    namedWindow("result",WINDOW_NORMAL);
    circle(whiteImage, center_point,5,cv::Scalar(0),-1);
    circle(whiteImage, center_point,110,cv::Scalar(0), 4);
    circle(whiteImage, center_point,220,cv::Scalar(0), 3);
    circle(whiteImage, center_point,330,cv::Scalar(0), 3);
    circle(whiteImage, center_point,440,cv::Scalar(0), 3);
    circle(whiteImage, center_point,550,cv::Scalar(0), 3);
    circle(whiteImage, pos,20,cv::Scalar(0), -1);

//    imshow("result", whiteImage);
    imwrite("result_whiteimage.jpg",whiteImage);

    //激光点与靶心圆心的距离
    distance = norm(pos-center_point);
    cout << "Distance between p1 and p2 is:" << distance << endl;
    if(distance>0&&distance<=110){
        score=10;
    }
    else if(distance>110&&distance<=220){
        score=9;
    }
    else if(distance>220&&distance<=330){
        score=8;
    }
    else if(distance>330&&distance<=440){
        score=7;
    }
    else if(distance>440&&distance<=550){
        score=6;
    }
    else if(distance>550&&distance<=660){
        score=5;
    }
    else{
        score=0;
    }

    //显示成绩
    ui->label_score->setStyleSheet("color: green");
    ui->label_score->setText(QString::number(score));
    ui->list_history->insertItem(id,QString::number(score));
    //显示靶图
    QPixmap pix("result_whiteimage.jpg");
    pix = pix.scaled(ui->label_ba->size());
    ui->label_ba->setPixmap(pix);
}
}

Mat autoreporting::QImageToMat(QImage &image)
{
    switch(image.format())
    {
        // 8-bit, 4 channel
        case QImage::Format_ARGB32:
            break;
        case QImage::Format_ARGB32_Premultiplied:
            {
                cv::Mat mat(image.height(), image.width(),
                            CV_8UC4,
                            (void*)image.constBits(),
                            image.bytesPerLine());
                return mat.clone();
            }

        // 8-bit, 3 channel
        case QImage::Format_RGB32:
            {
                cv::Mat mat(image.height(),image.width(),
                            CV_8UC4,
                            (void*)image.constBits(),
                            image.bytesPerLine());

                 // drop the all-white alpha channel
                cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
                return mat.clone();
            }
        case QImage::Format_RGB888:
            {
                QImage swapped = image.rgbSwapped();
                cv::Mat mat(swapped.height(), swapped.width(),
                            CV_8UC3,
                            (void*)image.constBits(),
                            image.bytesPerLine());
                return mat.clone();
            }

        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
            {
                cv::Mat mat(image.height(),image.width(),
                            CV_8UC1,
                            (void*)image.constBits(),
                            image.bytesPerLine());
                return mat.clone();
            }

        // wrong
        default:
            qDebug() << "ERROR: QImage could not be converted to Mat.";
            break;
    }
    return cv::Mat();
}

void autoreporting::on_pushButton_clicked()
{
    ui->list_history->clear();
}
