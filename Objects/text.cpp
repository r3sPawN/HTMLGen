#include "text.h"
#include "ui_text.h"

/*Initialize the class. Takes an extra parameter 'tag' which is passed
by MainWindow to store HTML tag type */
Text::Text(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Text)
{
    ui->setupUi(this);
    element = tag; //Local QString 'element' set to the 'tag' passed.
}

//Destructor
Text::~Text()
{
    delete ui;
}

//Function to store user input in local variables.
void Text::getUserInput()
{
    color = ui->colorBox->text(); //Sets 'color' to the user input from UI field 'colorBox'
    fontface = ui->fontFaceBox->text(); //Sets 'fontface' to the user input from UI field 'fontFaceBox'
    align = ui->alignBox->currentText(); //Sets 'align' to the user input from UI field 'alignBox'
    usertext = ui->PlainText->toPlainText(); //Sets 'usertext' to the user input from UI field 'PlainText'

    //Appends the tag variables into a QVector of QStrings which represents a valid HTML tag
    storage.append("<" + element + " style=\"");
    storage.append("color: " + color + "; ");

    //Checks if user input for font face is empty and ommits it in the tag generation
    if (fontface != "")
        storage.append("font-family: " + fontface + "; ");

    storage.append("text-align: " + align + ";\">");
    storage.append(usertext);
    storage.append("</" + element + ">");
}

//OK Button Action
void Text::on_OkButton_clicked()
{
    Text::getUserInput(); //Processes user input
    this->close(); //Closes window
}

//Cancel Button Action
void Text::on_CancelButton_clicked()
{
   this->close(); //Just closes the window.
}

/* Function to get all of the elements from the 'storage'
 * vector and merge them into a single string.
 * Returns a QString
*/
QString Text::getFullString()
{
    for (int i = 0; i < storage.size(); i++) //Iterates through the QVector elements.
    {
        fullString.append(storage[i]); //Append each element to the string

    }
    return fullString; //Return the complete string which will represent the element.
}




