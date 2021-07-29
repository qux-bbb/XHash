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
    XHash(QWidget *parent = nullptr);
    ~XHash();
    void setCalcStatus(bool calcFlag);
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

    void on_pushButton_about_clicked();

signals:
    void startWork(QStringList filePaths);
    void stopWork();

private:
    Ui::XHash *ui;
    VariousHash variousHash;
};
#endif // XHASH_H
