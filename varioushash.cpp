#include "varioushash.h"


VariousHash::VariousHash()
{

}

void VariousHash::calcHash(QStringList filePaths)
{
    // TODO add crc32/sha1/sha256/sha512 hash calc
    // TODO think progress bar update logic: before calc, change bar text to hash name
    foreach(QString filePath, filePaths){
        emit textBrowserAppendValue(filePath);
        emit progressBarFileSetValue(0);

        QFile file(filePath);
        file.size();

        file.open(QFile::ReadOnly);

        emit hashTypeLabelSetValue("md5");
        QCryptographicHash cryptoMd5(QCryptographicHash::Md5);
        while(!file.atEnd()){
            // unit bytes
            cryptoMd5.addData(file.read(1024*1024));
        }
        QString md5Value = QString(cryptoMd5.result().toHex());
        qDebug() << md5Value;
        emit textBrowserAppendValue("md5_value: "+md5Value);

        file.reset();
        emit hashTypeLabelSetValue("sha1");
        QCryptographicHash cryptoSha1(QCryptographicHash::Sha1);
        while(!file.atEnd()){
            cryptoSha1.addData(file.read(1024*1024));
        }
        QString sha1Value = QString(cryptoSha1.result().toHex());
        qDebug() << sha1Value;
        emit textBrowserAppendValue("sha1_value: "+sha1Value);

        file.reset();
        emit hashTypeLabelSetValue("sha256");
        QCryptographicHash cryptoSha256(QCryptographicHash::Sha256);
        while(!file.atEnd()){
            cryptoSha256.addData(file.read(1024*1024));
        }
        QString sha256Value = QString(cryptoSha256.result().toHex());
        qDebug() << sha256Value;
        emit textBrowserAppendValue("sha256_value: "+sha256Value);

        file.reset();
        emit hashTypeLabelSetValue("sha512");
        QCryptographicHash cryptoSha512(QCryptographicHash::Sha512);
        while(!file.atEnd()){
            cryptoSha512.addData(file.read(1024*1024));
        }
        QString sha512Value = QString(cryptoSha512.result().toHex());
        qDebug() << sha512Value;
        emit textBrowserAppendValue("sha512_value: "+sha512Value);

        emit progressBarFileSetValue(100);
        file.close();

        emit textBrowserAppendValue("\n");
        emit progressBarTotalAddValue();
    }
    emit hashTypeLabelSetValue("");

}

void VariousHash::doWork(QStringList filePaths)
{
    QtConcurrent::run(this, &VariousHash::calcHash, filePaths);

}
