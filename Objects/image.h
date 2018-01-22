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
    explicit Image(QWidget *parent = 0, QString tag = ""); //Constructor, takes an extra parameter 'tag'
    ~Image(); //Destructor
    QString getFullString(); //Getter for full HTML tag with user input.

private slots:
    void on_OkButton_clicked(); //Private slot for OK Button
    void on_CancelButton_clicked(); //Private slot for Cancel Button

private:
    Ui::Image *ui; //UI for the user input
    void getUserInput(); //Function to save the user input in QStrings.

    QVector<QString> storage; //QVector of QStrings for storing all of the user variables in seperate elements
    QString element, address, height, width, fullString; //QStrings needed for tag processing
};

#endif // IMAGE_H
