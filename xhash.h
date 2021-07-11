#ifndef XHASH_H
#define XHASH_H

#include <QMainWindow>
#include <varioushash.h>

QT_BEGIN_NAMESPACE
namespace Ui { class XHash; }
QT_END_NAMESPACE

class XHash : public QMainWindow
{
    Q_OBJECT

public:
    XHash(QWidget *parent = nullptr);
    ~XHash();

private slots:
    void on_pushButton_clear_clicked();
    void on_pushButton_copy_clicked();
    void on_pushButton_browse_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_stop_clicked();

    void on_progressBarFileSetValue(int i);
    void on_progressBarTotalAddValue();
    void on_textBrowserAppendValue(QString theString);

signals:
    void startWork(QStringList filePaths);

private:
    Ui::XHash *ui;
    VariousHash variousHash;
};
#endif // XHASH_H
