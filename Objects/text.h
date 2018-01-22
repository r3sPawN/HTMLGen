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
    explicit Text(QWidget *parent = 0, QString tag = ""); //Constructor, takes an extra parameter 'tag'
    ~Text(); //Destructor

    QString getFullString(); //Getter for full HTML tag with user input.

private slots:
    void on_OkButton_clicked(); //Private slot for OK Button
    void on_CancelButton_clicked(); //Private slot for Cancel Button

private:
    Ui::Text *ui; //UI for the user input
    void getUserInput(); //Function to save the user input in QStrings.

    QVector<QString> storage; //QVector of QStrings for storing all of the user variables in seperate elements
    QString element, color, align, fontface, usertext, fullString; //QStrings needed for tag processing
};

#endif // TEXT_H
