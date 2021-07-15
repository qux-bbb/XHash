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

        QFile file(filePath);
        qint64 fileSize = file.size();
        qint64 currentSize;

        file.open(QFile::ReadOnly);

        emit progressBarFileSetValue(0);
        currentSize = 0;
        emit hashTypeLabelSetValue("md5");
        QCryptographicHash cryptoMd5(QCryptographicHash::Md5);
        while(!file.atEnd()){
            // unit bytes
            cryptoMd5.addData(file.read(1024*1024));
            currentSize += 1024*1024;
            if (currentSize > fileSize)
                currentSize = fileSize;
            // 不能直接设置进度条最大值，因为文件太大进度条数字就有bug了，还不知道为什么
            emit progressBarFileSetValue(currentSize*100/fileSize);
        }
        QString md5Value = QString(cryptoMd5.result().toHex());
        qDebug() << md5Value;
        emit textBrowserAppendValue("md5_value: "+md5Value);

        file.reset();
        emit progressBarFileSetValue(0);
        currentSize = 0;
        emit hashTypeLabelSetValue("sha1");
        QCryptographicHash cryptoSha1(QCryptographicHash::Sha1);
        while(!file.atEnd()){
            cryptoSha1.addData(file.read(1024*1024));
            currentSize += 1024*1024;
            if (currentSize > fileSize)
                currentSize = fileSize;
            emit progressBarFileSetValue(currentSize*100/fileSize);
        }
        QString sha1Value = QString(cryptoSha1.result().toHex());
        qDebug() << sha1Value;
        emit textBrowserAppendValue("sha1_value: "+sha1Value);

        file.reset();
        emit progressBarFileSetValue(0);
        currentSize = 0;
        emit hashTypeLabelSetValue("sha256");
        QCryptographicHash cryptoSha256(QCryptographicHash::Sha256);
        while(!file.atEnd()){
            cryptoSha256.addData(file.read(1024*1024));
            currentSize += 1024*1024;
            if (currentSize > fileSize)
                currentSize = fileSize;
            emit progressBarFileSetValue(currentSize*100/fileSize);
        }
        QString sha256Value = QString(cryptoSha256.result().toHex());
        qDebug() << sha256Value;
        emit textBrowserAppendValue("sha256_value: "+sha256Value);

        file.reset();
        emit progressBarFileSetValue(0);
        currentSize = 0;
        emit hashTypeLabelSetValue("sha512");
        QCryptographicHash cryptoSha512(QCryptographicHash::Sha512);
        while(!file.atEnd()){
            cryptoSha512.addData(file.read(1024*1024));
            currentSize += 1024*1024;
            if (currentSize > fileSize)
                currentSize = fileSize;
            emit progressBarFileSetValue(currentSize*100/fileSize);
        }
        QString sha512Value = QString(cryptoSha512.result().toHex());
        qDebug() << sha512Value;
        emit textBrowserAppendValue("sha512_value: "+sha512Value);

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
