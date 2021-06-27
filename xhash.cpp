#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCryptographicHash>
#include "xhash.h"
#include "ui_xhash.h"


XHash::XHash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XHash)
{
    ui->setupUi(this);

}

XHash::~XHash()
{
    delete ui;
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
    // TODO
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Open file...", "", "All files (*)");

    int filePaths_count = filePaths.count();

    if (filePaths_count==0)
        return;

    ui->progressBar_total->setValue(0);
    ui->progressBar_total->setMaximum(filePaths_count);

    foreach (QString filePath, filePaths) {
        ui->progressBar_file->setValue(0);

        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
        }else{
            QCryptographicHash crypto(QCryptographicHash::Md5);
            while(!file.atEnd()){
              crypto.addData(file.read(8192));
            }
            QByteArray source;
            QTextStream in(&file);
            in >> source;
            QString md5Value = QString(crypto.result().toHex());

            ui->textBrowser->append(filePath);
            ui->textBrowser->append("md5_value: "+md5Value+"\n");
            ui->progressBar_file->setValue(100);
        }

        ui->progressBar_total->setValue(ui->progressBar_total->value()+1);
    }
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
    // TODO
    ui->textBrowser->setText("on_pushButton_stop_clicked");
}
