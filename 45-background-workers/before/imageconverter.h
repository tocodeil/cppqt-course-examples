#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QObject>

class ImageConverter : public QObject
{
    Q_OBJECT
public:
    explicit ImageConverter(QObject *parent = 0);

signals:
    void convertDone(QString fileName);

public slots:
    void convert(QStringList imageFiles);
};

#endif // IMAGECONVERTER_H
