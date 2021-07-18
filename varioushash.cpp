#include "varioushash.h"


VariousHash::VariousHash()
{

}

void VariousHash::calcHash(QStringList filePaths)
{
    stopFlag = false;
    // TODO add crc32 hash calc
    foreach(QString filePath, filePaths){
        emit textBrowserAppendValue(filePath);

        QStringList hashTypes = {"md5", "sha1", "sha256", "sha512"};
        foreach (QString hashType, hashTypes) {
            calcMostHash(hashType, filePath);
            if(stopFlag){
                emit signal_setCalcStatus(false);
                return;
            }
        }

        emit textBrowserAppendValue("");
        emit progressBarTotalAddValue();
    }
    emit hashTypeLabelSetValue("");
    emit signal_setCalcStatus(false);

}

void VariousHash::on_stopWork()
{
    stopFlag = true;
}

void VariousHash::doWork(QStringList filePaths)
{
    QtConcurrent::run(this, &VariousHash::calcHash, filePaths);

}

void VariousHash::calcMostHash(QString hashTypeStr, QString filePath)
{
    QFile file(filePath);
    qint64 fileSize = file.size();
    file.open(QFile::ReadOnly);

    QCryptographicHash *cryptHash;
    if(hashTypeStr=="md5")
        cryptHash = new QCryptographicHash(QCryptographicHash::Md5);
    else if (hashTypeStr=="sha1")
        cryptHash = new QCryptographicHash(QCryptographicHash::Sha1);
    else if (hashTypeStr=="sha256")
        cryptHash = new QCryptographicHash(QCryptographicHash::Sha256);
    else if (hashTypeStr=="sha512")
        cryptHash = new QCryptographicHash(QCryptographicHash::Sha512);
    else
        return;

    emit progressBarFileSetValue(0);
    emit hashTypeLabelSetValue(hashTypeStr);
    qint64 currentSize = 0;
    while(!file.atEnd()){
        // unit bytes
        cryptHash->addData(file.read(1024*1024));
        currentSize += 1024*1024;
        if (currentSize > fileSize)
            currentSize = fileSize;
        // 不能直接设置进度条最大值，因为文件太大进度条数字就有bug了，还不知道为什么
        emit progressBarFileSetValue(currentSize*100/fileSize);
        if(stopFlag)
            break;
    }
    if(!stopFlag){
        QString hashValue = QString(cryptHash->result().toHex());
        qDebug() << hashValue;
        emit textBrowserAppendValue(hashTypeStr+": "+hashValue);
    }

    file.close();
    delete cryptHash;
    cryptHash = nullptr;
}
