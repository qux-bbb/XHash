#include "varioushash.h"


VariousHash::VariousHash()
{

}

void VariousHash::calcHash(QStringList filePaths)
{
    // TODO add crc32/sha1/sha256/sha512 hash calc
    // TODO think progress bar update logic
    foreach(QString filePath, filePaths){
        emit textBrowserAppendValue(filePath);
        emit progressBarFileSetValue(0);


        QFile file(filePath);
        file.size();

        file.open(QFile::ReadOnly);

        QCryptographicHash crypto(QCryptographicHash::Md5);
        while(!file.atEnd()){
            crypto.addData(file.read(8192));
        }
        emit progressBarFileSetValue(100);

        QString md5Value = QString(crypto.result().toHex());
        file.close();
        qDebug() << md5Value;

        emit textBrowserAppendValue("md5_value: "+md5Value+"\n");
        emit progressBarTotalAddValue();
    }

}

void VariousHash::doWork(QStringList filePaths)
{
    QtConcurrent::run(this, &VariousHash::calcHash, filePaths);

}
