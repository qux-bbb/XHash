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
    connect(this, &XHash::startWork, &variousHash, &VariousHash::doWork);
    connect(&variousHash, &VariousHash::progressBarFileSetValue, this, &XHash::on_progressBarFileSetValue);
    connect(&variousHash, &VariousHash::progressBarTotalAddValue, this, &XHash::on_progressBarTotalAddValue);
    connect(&variousHash, &VariousHash::textBrowserAppendValue, this, &XHash::on_textBrowserAppendValue);
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
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Open file...", "", "All files (*)");

    int filePaths_count = filePaths.count();

    if (filePaths_count==0)
        return;

    ui->progressBar_total->setValue(0);
    ui->progressBar_total->setMaximum(filePaths_count);

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
    // TODO
    ui->textBrowser->setText("on_pushButton_stop_clicked");
}

void XHash::on_progressBarFileSetValue(int i)
{
    ui->progressBar_file->setValue(i);
}

void XHash::on_progressBarTotalAddValue()
{
    ui->progressBar_total->setValue(ui->progressBar_total->value()+1);
}

void XHash::on_textBrowserAppendValue(QString theString)
{
    ui->textBrowser->append(theString);
}
