#include <QCoreApplication>
#include <numeric>
#include <QtCore>
#include <QtConcurrent>
#include <QFutureWatcher>

QByteArray calcHash(QString w)
{
    return QCryptographicHash::hash(w.toLatin1(), QCryptographicHash::Sha1).toHex();
}

void readWordsIntoVector(QVector<QString> &words)
{
    QFile f("/usr/share/dict/words");
    if (!f.open(QIODevice::ReadOnly)) throw new std::exception();

    QTextStream ts(&f);

    while (!ts.atEnd())
    {
        words.push_back(ts.readLine());
    }
    f.close();
}

int calculateSha1Serial(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // read words file
    QVector<QString> words;
    readWordsIntoVector(words);

    for (auto word : words)
    {
        qDebug() << word << " => " << calcHash(word);
    }
    return 0;
}


int calculateSha1(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // read words file
    QVector<QString> words;
    readWordsIntoVector(words);
    QFuture<QByteArray> hashes = QtConcurrent::mapped(words, calcHash);

    QFutureWatcher<QByteArray> fw;
    fw.setFuture(hashes);
    QObject::connect(&fw, &QFutureWatcher<QString>::resultReadyAt, [&hashes, &words](int idx) {
       qDebug() << words.at(idx) << " => " << hashes.resultAt(idx);
    });
    QObject::connect(&fw, &QFutureWatcher<QString>::finished, &a, &QCoreApplication::quit);
    return a.exec();
}

int calculatePrimeNumbers(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<int> N;
    N.resize(100);
    std::iota(N.begin(), N.end(), 0);

    QFuture<int> primes = QtConcurrent::filtered(N, [](int n) {
       for (int i=2; i <= qSqrt(n); i++)
       {
            if (n % i == 0)
            {
                return false;
            }
       }
       return true;
    });
    QFutureWatcher<int> fw;
    fw.setFuture(primes);
    QObject::connect(&fw, &QFutureWatcher<int>::resultReadyAt, [&primes](int idx) {
       qDebug() << "Prime: " << primes.resultAt(idx);
    });
    QObject::connect(&fw, &QFutureWatcher<int>::finished, &a, &QCoreApplication::quit);

    return a.exec();
}

int main(int argc, char *argv[])
{    
//    calculatePrimeNumbers(argc, argv);
    if (argc > 1 && strncmp(argv[1], "s", 1))
    {
        calculateSha1Serial(argc, argv);
    }
    else if (argc > 1 && strncmp(argv[1], "p", 1))
    {
        calculateSha1(argc, argv);
    }
}
