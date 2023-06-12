#ifndef XHASH_H
#define XHASH_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <varioushash.h>

QT_BEGIN_NAMESPACE
namespace Ui { class XHash; }
QT_END_NAMESPACE

class XHash : public QMainWindow
{
    Q_OBJECT

public:
    XHash(int argc, char *argv[], QWidget *parent = nullptr);
    ~XHash();
    void setCalcStatus(bool calcFlag);
    void setPathList(QStringList pathList);
protected:
    void dragEnterEvent(QDragEnterEvent*event);
    void dropEvent(QDropEvent *event);
private:
    void prepareAndWork(QStringList filePaths);

private slots:
    void on_pushButton_clear_clicked();
    void on_pushButton_copy_clicked();
    void on_pushButton_browse_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_stop_clicked();

    void on_progressBarFileSetValue(qint64 i);
    void on_progressBarFileSetMaximum(qint64 i);
    void on_hashTypeLabelSetValue(QString theString);
    void on_progressBarTotalAddValue();
    void on_textBrowserAppendValue(QString theString);

    void on_pushButton_start_clicked();

    void on_actionAbout_triggered();

signals:
    void startWork(QStringList filePaths);
    void stopWork();

public:
    QString version = "v1.1.0";

private:
    Ui::XHash *ui;
    VariousHash variousHash;
};
#endif // XHASH_H
