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
    explicit Link(QWidget *parent = 0, QString tag = ""); //Constructor, takes an extra parameter 'tag'
    ~Link(); //Destructor

    QString getFullString(); //Getter for full HTML tag with user input.

private slots:
    void on_OkButton_clicked(); //Private slot for OK Button
    void on_CancelButton_clicked(); //Private slot for Cancel Button

private:
    Ui::Link *ui; //UI for the user input
    void getUserInput(); //Function to save the user input in QStrings.

    QVector<QString> storage; //QVector of QStrings for storing all of the user variables in seperate elements
    QString element, address, userText, fullString; //QStrings needed for tag processing
};

#endif // LINK_H
