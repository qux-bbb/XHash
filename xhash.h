#ifndef XHASH_H
#define XHASH_H

#include <QMainWindow>

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

private:
    Ui::XHash *ui;
};
#endif // XHASH_H
