#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCryptographicHash>
#include <QtConcurrentRun>
#include "xhash.h"
#include "ui_xhash.h"


XHash::XHash(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XHash)
{
    ui->setupUi(this);
    if (argc > 1){
        QString pathListStr;
        for (int i = 1; i < argc; i++) {
            pathListStr += argv[i];
            pathListStr += "\n";
        }
        ui->plainTextEdit->setPlainText(pathListStr);
    }
    ui->pushButton_stop->setDisabled(true);
    connect(this, &XHash::startWork, &variousHash, &VariousHash::doWork);
    connect(this, &XHash::stopWork, &variousHash, &VariousHash::on_stopWork);
    connect(&variousHash, &VariousHash::signal_setCalcStatus, this, &XHash::setCalcStatus);
    connect(&variousHash, &VariousHash::progressBarFileSetValue, this, &XHash::on_progressBarFileSetValue);
    connect(&variousHash, &VariousHash::progressBarFileSetMaximum, this, &XHash::on_progressBarFileSetMaximum);
    connect(&variousHash, &VariousHash::hashTypeLabelSetValue, this, &XHash::on_hashTypeLabelSetValue);
    connect(&variousHash, &VariousHash::progressBarTotalAddValue, this, &XHash::on_progressBarTotalAddValue);
    connect(&variousHash, &VariousHash::textBrowserAppendValue, this, &XHash::on_textBrowserAppendValue);
}

XHash::~XHash()
{
    delete ui;
}

void XHash::setCalcStatus(bool calcFlag)
{
    ui->checkBox_crc32->setDisabled(calcFlag);
    ui->checkBox_md5->setDisabled(calcFlag);
    ui->checkBox_sha1->setDisabled(calcFlag);
    ui->checkBox_sha256->setDisabled(calcFlag);
    ui->checkBox_sha512->setDisabled(calcFlag);

    ui->pushButton_browse->setDisabled(calcFlag);
    ui->pushButton_clear->setDisabled(calcFlag);
    ui->pushButton_copy->setDisabled(calcFlag);
    ui->pushButton_save->setDisabled(calcFlag);

    ui->pushButton_stop->setDisabled(!calcFlag);
}

void XHash::setPathList(QStringList pathList)
{
    QString pathListStr;
    foreach (QString tmpPath, pathList) {
        pathListStr += tmpPath;
        pathListStr += "\n";
    }
    ui->plainTextEdit->setPlainText(pathListStr);
}

void XHash::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void XHash::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QList<QUrl> urls = event->mimeData()->urls();

        QStringList filePaths;
        foreach (QUrl url, urls) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo = QFileInfo(filePath);
            if(fileInfo.isFile() || fileInfo.isSymLink())
                filePaths.append(filePath);
        }
        setPathList(filePaths);
    }
}

void XHash::prepareAndWork(QStringList filePaths)
{
    int filePaths_count = filePaths.count();

    if (filePaths_count==0)
        return;

    variousHash.crc32Checked = ui->checkBox_crc32->isChecked();
    variousHash.md5Checked = ui->checkBox_md5->isChecked();
    variousHash.sha1Checked = ui->checkBox_sha1->isChecked();
    variousHash.sha256Checked = ui->checkBox_sha256->isChecked();
    variousHash.sha512Checked = ui->checkBox_sha512->isChecked();

    setCalcStatus(true);

    ui->progressBar_total->setMaximum(filePaths_count);
    ui->progressBar_total->setValue(0);

    emit startWork(filePaths);
}


void XHash::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}


void XHash::on_pushButton_copy_clicked()
{
    QString source = ui->textBrowser->toPlainText();

    // 提示消息暂时使用QmessageBox，后面最好改成类似Android的Toast消息
    QMessageBox msgBox;
    if (source == ""){
        msgBox.setText(tr("Emtpy!"));
    }else{
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(source);

        msgBox.setText(tr("Copied"));
    }
    msgBox.exec();

}


void XHash::on_pushButton_browse_clicked()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open file..."), "", tr("All files (*)"), nullptr, QFileDialog::DontResolveSymlinks);
    setPathList(filePaths);
}


void XHash::on_pushButton_save_clicked()
{
    QString source = ui->textBrowser->toPlainText();
    if (source == ""){
        QMessageBox::warning(this, tr("Warning"), tr("The Content can not be empty!"), QMessageBox::Ok);
    }else{
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Result"), "hash.txt", tr("Text (*.txt);;All Files (*)"));
        if (filePath.isEmpty())
            return;
        else {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                                         file.errorString());
            }else{
                QTextStream out(&file);
                out << source;
            }
        }
    }
}

void XHash::on_pushButton_start_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();

    QTextStream stream(&text);
    QString line;
    QStringList filePaths;
    while (!stream.atEnd()) {
        line = stream.readLine();
        filePaths.append(line);
    }
    prepareAndWork(filePaths);
}

void XHash::on_pushButton_stop_clicked()
{
    emit stopWork();
}

void XHash::on_progressBarFileSetValue(qint64 i)
{
    ui->progressBar_file->setValue(i);
}

void XHash::on_progressBarFileSetMaximum(qint64 i)
{
    ui->progressBar_file->setMaximum(i);
}

void XHash::on_hashTypeLabelSetValue(QString theString)
{
    ui->label_hashType->setText(theString);
}

void XHash::on_progressBarTotalAddValue()
{
    ui->progressBar_total->setValue(ui->progressBar_total->value()+1);
}

void XHash::on_textBrowserAppendValue(QString theString)
{
    ui->textBrowser->append(theString);
}

void XHash::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("XHash "+version+"<br>"+tr("Calculate some file hash: ")+"<a href='https://github.com/qux-bbb/XHash'>https://github.com/qux-bbb/XHash</a>");
    msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse|Qt::LinksAccessibleByMouse);
    msgBox.exec();
}

