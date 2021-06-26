#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QThread>
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
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Open file...", "", "All files (*)");

    foreach (QString fileName, fileNames) {
        ui->textBrowser->append(fileName);
        ui->progressBar_file->setValue(100);
        QThread::sleep(2);
        ui->progressBar_file->reset();
        QThread::sleep(2);
    }
}


void XHash::on_pushButton_save_clicked()
{
    QString source = ui->textBrowser->toPlainText();
    if (source == ""){
        QMessageBox::warning(this, "Warning", "The Content can not be empty!", QMessageBox::Ok);
    }else{
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Result"), "", tr("Text (*.txt);;All Files (*)"));
        if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
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

