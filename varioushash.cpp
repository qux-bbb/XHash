#include "varioushash.h"


VariousHash::VariousHash()
{

}

void VariousHash::calcHash(QStringList filePaths)
{
    // TODO add crc32 hash calc
    foreach(QString filePath, filePaths){
        emit textBrowserAppendValue(filePath);

        caclMostHash("md5", filePath);
        caclMostHash("sha1", filePath);
        caclMostHash("sha256", filePath);
        caclMostHash("sha512", filePath);

        emit textBrowserAppendValue("\n");
        emit progressBarTotalAddValue();
    }
    emit hashTypeLabelSetValue("");

}

void VariousHash::doWork(QStringList filePaths)
{
    QtConcurrent::run(this, &VariousHash::calcHash, filePaths);

}

void VariousHash::caclMostHash(QString hashTypeStr, QString filePath)
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
    }
    QString hashValue = QString(cryptHash->result().toHex());
    qDebug() << hashValue;
    emit textBrowserAppendValue(hashTypeStr+"_value: "+hashValue);

    file.close();
    delete cryptHash;
    cryptHash = nullptr;
}
