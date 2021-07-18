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
    bool md5Checked = true;
    bool sha1Checked = true;
    bool sha256Checked = false;
    bool sha512Checked = false;
    VariousHash();
    void doWork(QStringList filePaths);
    void on_stopWork();

private:
    bool stopFlag = false;
    void calcMostHash(QString hashTypeStr, QString filePath);
    void calcHash(QStringList filePaths);

signals:
    void progressBarFileSetValue(qint64 i);
    void progressBarFileSetMaximum(qint64 i);
    void hashTypeLabelSetValue(QString theString);
    void progressBarTotalAddValue();
    void textBrowserAppendValue(QString theString);
    void signal_setCalcStatus(bool calcFlag);
};

#endif // VARIOUSHASH_H
