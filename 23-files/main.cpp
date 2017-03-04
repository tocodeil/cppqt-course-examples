#include <QCoreApplication>
#include <QtCore>

QString getDataFileName(QString base)
{
    QStringList locs = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QDir path(locs.first());
    if (!path.exists())
    {
        path.mkpath(".");
    }
    QString filename = path.filePath(base);
    return filename;
}


/**
 * first demo: Writing some strings into a text file
 */
void writeToTextFile()
{
    QString filename = getDataFileName("info.txt");
    QFile f(filename);
    qDebug() << "Writing to: " << filename;

    if (f.exists())
    {
        qDebug() << "File " << filename << " Already Exists. Not writing";
        return;
    }

    if (!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file " << filename << " for writing: " << f.errorString();
        return;
    }

    QTextStream out(&f);
    out.setCodec(QTextCodec::codecForName("utf-8"));

    QString line("This is line %1 of %2...");
    for (int i=0; i < 10; i++)
    {
        out << line.arg(i).arg(10) << endl;
    }

    f.close();
}

void readFromTextFile()
{
    QString filename = getDataFileName("info.txt");
    QFile f(filename);
    qDebug() << "Reading from: " << filename;

    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file for reading: " << f.errorString();
        return;
    }

    QTextStream in(&f);
    in.setCodec(QTextCodec::codecForName("utf-8"));
    while(!in.atEnd())
    {
        QString nextLine = in.readLine();
        qDebug() << "Read Line: " << nextLine;
    }
    f.close();
}

void writeBinaryDataToFile()
{
    QString filename = getDataFileName("info.bin");
    QFile f(filename);
    qDebug() << "Writing To: " << filename;

    if (!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file for writing: " << f.errorString();
        return;
    }

    QDataStream out(&f);
    out << 10 << 20 << 30 << QString("the end");
    f.close();
}

void readBinaryDataFromFile()
{
    QString filename = getDataFileName("info.bin");
    QFile f(filename);
    qDebug() << "Reading from: " << filename;

    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file for reading: " << f.errorString();
        return;
    }

    QDataStream in(&f);
    int a, b, c;
    QString d;
    in >> a >> b >> c >> d;

    qDebug() << "Read: " << a << b << c << d;
    f.close();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    writeToTextFile();
    readFromTextFile();
    writeBinaryDataToFile();
    readBinaryDataFromFile();

    return 0;
}
