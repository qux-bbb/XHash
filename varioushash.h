#ifndef VARIOUSHASH_H
#define VARIOUSHASH_H

#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QtConcurrent>
#include <QtDebug>

class VariousHash:public QObject
{
    Q_OBJECT
public:
    VariousHash();
    void doWork(QStringList filePaths);

private:
    void calcHash(QStringList filePaths);

signals:
    void progressBarFileSetValue(int i);
    void progressBarTotalAddValue();
    void textBrowserAppendValue(QString theString);
};

#endif // VARIOUSHASH_H
