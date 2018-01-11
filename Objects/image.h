#ifndef IMAGE_H
#define IMAGE_H

#include <QDialog>

namespace Ui {
class Image;
}

class Image : public QDialog
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = 0, QString tag = "");
    ~Image();
    QString getFullString();

private slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::Image *ui;
    void getUserInput();

    QVector<QString> storage;
    QString element, address, height, width, fullString;
};

#endif // IMAGE_H
