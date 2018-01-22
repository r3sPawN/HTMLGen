#include "image.h"
#include "ui_image.h"

/*Initialize the class. Takes an extra parameter 'tag' which is passed
by MainWindow to store HTML tag type */
Image::Image(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    element = tag; //Local QString 'element' set to the 'tag' passed.
}

//Destructor
Image::~Image()
{
    delete ui;
}

//Function to store user input in local variables.
void Image::getUserInput()
{
    address = ui->address->text(); //Sets 'address' to the user input from UI field 'address'
    height = ui->height->text(); //Sets 'height' to the user input from UI field 'height'
    width = ui->width->text(); //Sets 'width' to the user input from UI field 'width'

    //If user input from height field is 0, sets height to auto
    if(height == "0")
        height = "auto";

    //If user input from width field is 0, sets width to auto
    if(width == "0")
        width = "auto";


    //Appends the tag variables into a QVector of QStrings
    storage.append("<" + element);
    storage.append(" src=\""+ address + "\" ");
    storage.append("height=\"" + height + "\" ");
    storage.append("width=\"" + width + "\">");
}

//OK Button Action
void Image::on_OkButton_clicked()
{
    getUserInput(); //Processes user input
    this->close(); //Closes window
}

//Cancel Button Action
void Image::on_CancelButton_clicked()
{
    this->close(); //Just closes the window.
}

/* Function to get all of the elements from the 'storage'
 * vector and merge them into a single string.
 * Returns a QString
*/
QString Image::getFullString()
{
    for (int i = 0; i < storage.size(); i++) //Iterates through the QVector elements.
    {
        fullString.append(storage[i]); //Append each element to the string

    }
    return fullString; //Return the complete string which will represent the element.
}
