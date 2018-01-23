#include "mainwindow.h"
#include "ui_mainwindow.h"

//Constructor function for main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); //Initialize the UI
    on_actionNew_triggered(); //Does some upkeep and triggers the "New" slot when the program runs
    setWindowTitle("Simple Html Generator"); //Sets the title of the window
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Function
void MainWindow::on_actionOpen_triggered()
{
    QString File = QFileDialog::getOpenFileName(this,"Open a file"),
                    setFileMode("*html"); //opening a window used to find a file

    QFile sFile(File);
    if(!sFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("The program could not open the file!"),
                             tr("Can not open file %1:\n%2.").arg(sFilename)
                             .arg(sFile.errorString()));
    }
    else
    {
        QTextStream in(&sFile);
        QString text = in.readAll(); // reads from the stream and put it into a string
        sFile.close();

        ui->textEdit->setPlainText(text);
        ui->textEdit->textChanged();

        QFileInfo fileInfo(sFile); //provides information-file name
        sFilename = fileInfo.fileName();
        setWindowTitle(fileInfo.fileName());
        Path = fileInfo.absoluteFilePath(); //saves the path of the lattest saved file
    }

}

//Function that does the necessary steps to ensure the new file does not have leftovers from previous edits
void MainWindow::on_actionNew_triggered()
{
    sFilename = ""; //Set sFilename to an empty string
    htmlstore.reset(); //Call the storage class function reset()
    ui->parseElements->clear(); //Clear the elements from the QListWidget in the middle 'parseElements'
    ui->textEdit->clear(); //Clear the text from the rightmost pane 'textEdit'
}

//Function to undo user input in textEdit field
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo(); //QT Built in undo
}

//Function to redo user input in textEdit field
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo(); //QT Built in redo
}

//Function to save the file. If a file path has not been defined, the function calls to Save As.
void MainWindow::on_actionSave_triggered()
{
    QFile sFile(sFilename);

    if(sFilename.isEmpty()== true) //Check whether the file has a name
    {
        on_actionSave_as_triggered(); //If it is untitled, call the SaveAs function
    }
    else
    {
        if(!sFile.open(QFile::WriteOnly | QFile::Text)) // Printss error messege if it fails to open
        {
            QMessageBox::warning(this, tr("Error saving file"),
                                 tr("Cannot write file %1:\n%2.").arg(sFilename)
                                 .arg(sFile.errorString()));
        }

        QTextStream out(&sFile);

        out << ui -> textEdit -> toPlainText(); //Set the 'out' text stream to be the plaintext of 'textEdit'

        sFile.flush(); //Clear the sFile buffer
        sFile.close(); //Close the sFile buffer

        ui->statusBar->showMessage("Saved", 2000); //Show a message in the status bar for 2 seconds, indicating successful save

        QFileInfo fileInfo(sFile);
        setWindowTitle(fileInfo.fileName());
        Path = fileInfo.absoluteFilePath(); //saves the path of the lattest saved file
    }
}

//
void MainWindow::on_actionPreview_triggered() //Preview
{
    if (sFilename.isEmpty() == true) //Check if the file has a name
    {
        QMessageBox::StandardButton ret; //Create a messagebox that will show an error.
        //Display the error in the string below and give it two options
        ret = QMessageBox::warning (
            this, tr("Warning"),
            tr("The document has not been saved yet.\n"
            "Do you want to save it?"),
            QMessageBox::Save | QMessageBox::Discard //Option to save and to cancel
        );

        //If save is clicked, call slot Save
        if (ret == QMessageBox::Save)
            on_actionSave_triggered();
    }
    else
    {
        QDesktopServices::openUrl(QUrl(Path)); //Open the file in a browser for viewing
    }
}

//Save as function with a QT File browser
void MainWindow::on_actionSave_as_triggered()
{
    sFilename = QFileDialog::getSaveFileName(this,"Saving a file"); //Sets QString 'File' to the directory pickde by the user

    if(!sFilename.isEmpty()) //Check if 'File' is empty
    {
        on_actionSave_triggered(); //Call to the Save function
    }
}

/*Generates html and outputs it to the text box on the right.
 *Important to note that for each QListWidgetItem(QLWI) there exists a "Role" with corresponding data
 *
 *Roles from 0 to 31 are reserved for QT
 *First available Role for the application is 32, used in the function.
 */
void MainWindow::generateHtml()
{
    htmlstore.reset(); //Resets the HTML vector storage
    htmlstore.initHtml(); //Reinitializes the HTML vector storage
    QListWidgetItem* nthItem; //Creates a pointer to QLWI 'nthItem'
    QVariant itemData; //Creates a QVariant 'itemData' which is the way to access a QLWI data slot.

    for(int i = 0; i < ui->parseElements->count(); i++) //Iterates through the elements of the QLW 'parseElements'
    {
        nthItem = ui->parseElements->item(i); //Sets 'nthItem' to the QLWI with the corresponding index

        //Performs several checks to determine the type of tag
        if(nthItem->text().at(0) == "<") //If the text of the QLWI starts with a "<"
            nthItem->setData(32, nthItem->text()); //Set the full string of the QLWI as the item data for role 32

        itemData = nthItem->data(32); //Set 'itemData' to nthItem's data from role 32.

        //Show an error message if the element has not been configured by the user.
        if (itemData.value<QString>() == NULL)//Check if itemData's role 32 string is empty.
            nthItem->setData(32, "Element still uninitialized. Doubleclick it to get started!");

        itemData = nthItem->data(32);

        //Insert the element at row 8+i. The reason behind that is because that's where the body tag in the HTML storage opens
        htmlstore.insertElement(i + 8, itemData.value<QString>());
    }

    //Set the plain text of 'textEdit' to the returned value from the storage.
    ui->textEdit->setPlainText(htmlstore.getAllElements());
}

void MainWindow::on_parseElements_itemDoubleClicked()
{
    QListWidgetItem* currentItem = ui->parseElements->currentItem(); //Creates a pointer to the doubleclicked item
    QString currentItemString = currentItem->text(); //Creates a QString which is the text of 'currentItem'

    //If it starts with "<", there's nothing to do, since it does not have user input to be edited.
    if (currentItemString.at(0) == "<")
    {
        qDebug() << "Nothing to edit!" << endl; //Print out an error message in the Application output
    }

    //If the string of the current item is "img"
    else if (currentItemString == "img")
    {
        Image* img = new Image(0, currentItemString); //Create a new object of type Image, passing the tag needed for the class constructor
        img->setModal(true); //Required user input, be it "OK" or "Cancel"
        img->exec(); //Show the user input dialog
        currentItem->setData(32, img->getFullString()); //Set the data of the current item to the fullstring returned from that object
    }

    //If the string of the current item is "img"
    else if (currentItemString == "a")
    {
        Link* url = new Link(0, currentItemString); //Create a new object of type Link, passing the tag needed for the class constructor
        url->setModal(true);
        url->exec();
        currentItem->setData(32, url->getFullString());
    }

    //If the string of the current item is anything else (other options already covered), assume it is h1-6 or p
    else
    {
        Text* txt = new Text(0, currentItemString); //Create a new object of type Text, passing the tag needed for the class constructor
        txt->setModal(true);
        txt->exec();
        currentItem->setData(32, txt->getFullString());
    }
}

//When clicking the Generate button call check for empty storage and call generateHtml()
void MainWindow::on_actionGenerate_triggered()
{
    if(htmlstore.getSize() <= 0) //Check if the size of the Storage vector class is 0 using implemented getSize()
        htmlstore.initHtml(); //If true use the storage vector member function initHtml
    generateHtml(); //Generate HTML function
}

//Function to quit the application when the exit button is pressed
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

//Function to delete an element from the list
void MainWindow::on_actionDelete_triggered()
{
    QListWidgetItem* toDelete = ui->parseElements->currentItem();
    delete ui->parseElements->takeItem(ui->parseElements->row(toDelete));
    on_actionGenerate_triggered();
}
