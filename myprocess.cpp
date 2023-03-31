#include "myprocess.h"
#include"opencv2/opencv.hpp"



MyProcess::MyProcess(QObject *parent) : QAbstractVideoSurface(parent)
{

}

bool MyProcess::present(const QVideoFrame &frame)
{
    QVideoFrame fm = frame;//拷贝构造，内部地址浅拷贝，视频帧依旧存放于不可读取的内存上，需要进行映射
    fm.map(QAbstractVideoBuffer::ReadOnly);//映射视频帧内容，映射到可访问的地址上
    QImage image(fm.bits(),fm.width(),fm.height(),fm.imageFormatFromPixelFormat(fm.pixelFormat()));
    //摄像头拍摄到的图片，是上下左右相反的，需镜像一下
    image = image.mirrored(0);//纵向镜像，纵向镜像是默认值
    //通过sndImage信号发送image
    emit sndImage(image);
    return true;
}

QList<QVideoFrame::PixelFormat> MyProcess::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    Q_UNUSED(type);
        return QList<QVideoFrame::PixelFormat>()
        << QVideoFrame::Format_ARGB32
        << QVideoFrame::Format_ARGB32_Premultiplied
        << QVideoFrame::Format_RGB32
        << QVideoFrame::Format_RGB24
        << QVideoFrame::Format_RGB565
        << QVideoFrame::Format_RGB555
        << QVideoFrame::Format_ARGB8565_Premultiplied
        << QVideoFrame::Format_BGRA32
        << QVideoFrame::Format_BGRA32_Premultiplied
        << QVideoFrame::Format_BGR32
        << QVideoFrame::Format_BGR24
        << QVideoFrame::Format_BGR565
        << QVideoFrame::Format_BGR555
        << QVideoFrame::Format_BGRA5658_Premultiplied
        << QVideoFrame::Format_AYUV444
        << QVideoFrame::Format_AYUV444_Premultiplied
        << QVideoFrame::Format_YUV444
        << QVideoFrame::Format_YUV420P
        << QVideoFrame::Format_YV12
        << QVideoFrame::Format_UYVY
        << QVideoFrame::Format_YUYV
        << QVideoFrame::Format_NV12
        << QVideoFrame::Format_NV21
        << QVideoFrame::Format_IMC1
        << QVideoFrame::Format_IMC2
        << QVideoFrame::Format_IMC3
        << QVideoFrame::Format_IMC4
        << QVideoFrame::Format_Y8
        << QVideoFrame::Format_Y16
        << QVideoFrame::Format_Jpeg
        << QVideoFrame::Format_CameraRaw
        << QVideoFrame::Format_AdobeDng;
}
