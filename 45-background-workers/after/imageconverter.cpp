#include "imageconverter.h"
#include <QtGui>
#include <QColor>

ImageConverter::ImageConverter(QObject *parent) : QObject(parent)
{

}

void ImageConverter::convert(QStringList imageFiles)
{
    for (QString fileName : imageFiles)
    {
        QImage src(fileName);
        QSize outSize(640, 480);
        QImage result = src.scaled(outSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPainter painter(&result);
        QColor bgColor(0, 0, 0, 150);
        painter.fillRect(0, 350, 640, 130, bgColor);
        painter.setPen(Qt::white);
        painter.setFont(QFont("serif", 24, 500));
        painter.drawText(10, 400, "Made With 💚");

        QString outFileName = fileName.left(fileName.length() - 4) + "-edited.png";
        qDebug() << "Saving to: " << outFileName;
        result.save(outFileName, "PNG");
        emit convertDone(fileName);
    }
}
