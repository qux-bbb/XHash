#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCryptographicHash>
#include <QtConcurrentRun>
#include "xhash.h"
#include "ui_xhash.h"


XHash::XHash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XHash)
{
    ui->setupUi(this);
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


void XHash::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}


void XHash::on_pushButton_copy_clicked()
{
    QString source = ui->textBrowser->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(source);
}


void XHash::on_pushButton_browse_clicked()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Open file...", "", "All files (*)");

    int filePaths_count = filePaths.count();

    if (filePaths_count==0)
        return;


    variousHash.md5Checked = ui->checkBox_md5->isChecked();
    variousHash.sha1Checked = ui->checkBox_sha1->isChecked();
    variousHash.sha256Checked = ui->checkBox_sha256->isChecked();
    variousHash.sha512Checked = ui->checkBox_sha512->isChecked();

    setCalcStatus(true);

    ui->progressBar_total->setMaximum(filePaths_count);
    ui->progressBar_total->setValue(0);

    emit startWork(filePaths);
}


void XHash::on_pushButton_save_clicked()
{
    QString source = ui->textBrowser->toPlainText();
    if (source == ""){
        QMessageBox::warning(this, "Warning", "The Content can not be empty!", QMessageBox::Ok);
    }else{
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Result"), "", tr("Text (*.txt);;All Files (*)"));
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
