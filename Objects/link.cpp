#include "link.h"
#include "ui_link.h"

/*Initialize the class. Takes an extra parameter 'tag' which is passed
by MainWindow to store HTML tag type */
Link::Link(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Link)
{
    ui->setupUi(this);
    element = tag; //Local QString 'element' set to the 'tag' passed.
}

//Destructor
Link::~Link()
{
    delete ui;
}

//Function to store user input in local variables.
void Link::getUserInput()
{
    address = ui->address->text(); //Sets 'address' to the user input from UI field 'address'
    userText = ui->PlainText->toPlainText(); //Sets 'userText' to the user input from UI field 'PlainText'


    //Appends the tag variables into a QVector of QStrings which represents a valid HTML tag
    storage.append("<" + element);
    storage.append(" href=\"" + address + "\">");
    storage.append(userText);
    storage.append("</" + element + ">");
}

//OK Button Action
void Link::on_OkButton_clicked()
{
    getUserInput(); //Processes user input
    this->close(); //Closes window
}

//Cancel Button Action
void Link::on_CancelButton_clicked()
{
    this->close(); //Just closes the window.
}

/* Function to get all of the elements from the 'storage'
 * vector and merge them into a single string.
 * Returns a QString
*/
QString Link::getFullString()
{
    for (int i = 0; i < storage.size(); i++) //Iterates through the QVector elements.
    {
        fullString.append(storage[i]); //Append each element to the string
    }

    return fullString; //Return the complete string which will represent the element.
}
