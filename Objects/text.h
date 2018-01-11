#ifndef TEXT_H
#define TEXT_H

#include <QDialog>
#include <QString>
#include <QDebug>

namespace Ui {
class Text;
}

class Text : public QDialog
{
    Q_OBJECT

public:
    explicit Text(QWidget *parent = 0, QString tag = "");
    ~Text();

    QString getFullString();

private slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::Text *ui;
    void getUserInput();

    QVector<QString> storage;
    QString element, color, align, usertext, fullString;
};

#endif // TEXT_H
