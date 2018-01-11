#ifndef LINK_H
#define LINK_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Link;
}

class Link : public QDialog
{
    Q_OBJECT

public:
    explicit Link(QWidget *parent = 0, QString tag = "");
    ~Link();

    QString getFullString();

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::Link *ui;

    QVector<QString> storage;
    QString element, address, userText, fullString;

    void getUserInput();
};

#endif // LINK_H
