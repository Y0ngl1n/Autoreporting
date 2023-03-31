#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QObject>
#include<QAbstractVideoSurface>
#include<QDebug>
#include"opencv2/opencv.hpp"

class MyProcess : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit MyProcess(QObject *parent = nullptr);
    virtual bool present(const QVideoFrame &frame);
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;
signals:
    void sndImage(QImage);
public slots:
};

#endif // MYPROCESS_H
