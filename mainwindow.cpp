#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this -> setCentralWidget(ui->textEdit); // centers the text edit space
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered() //open function
{
    QString File = QFileDialog::getOpenFileName(this,"Open a file"); //opening a window used to find a file
    // need to add error checking
    QFile sFile(File);
    if(sFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&sFile);
        QString text = in.readAll();
        sFile.close();

//        ui->textEdit->setPlainText(text);
    }

}

void MainWindow::on_actionNew_triggered() //new
{
    sFilename = "";
//    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionUndo_triggered() //undo
{
//    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered() //redo
{
//    ui->textEdit->redo();
}

void MainWindow::on_actionSave_triggered() //save (needs some more work)
{
    QFile sFile(sFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);

//        out << ui -> textEdit -> toPlainText();

        sFile.flush();
        sFile.close();

        QFileInfo fileInfo(sFile);
        Path = fileInfo.absoluteFilePath();

    }

}

void MainWindow::on_actionPreview_triggered() //Preview
{
    QDesktopServices::openUrl(QUrl(Path));
}

void MainWindow::on_actionSave_as_triggered()
{
    QString File = QFileDialog::getSaveFileName(this,"Saving a file");

    if(!File.isEmpty())
    {
        sFilename = File;
        on_actionSave_triggered();
    }
}

void MainWindow::getParsedItems() //Print the contents of the working area to console
{
    //reset everythinng
    QString addedElements = NULL;
    itemList.clear();

    //gets items in the ui and appends them to items vector
    for(int i = 0; i < ui->parseElements->count(); i++)
    {
        QListWidgetItem *item = ui->parseElements->item(i);
        itemList.append(item -> text());
    }

    //pushes items to string addedElements
    for(int i = 0; i < itemList.count(); i++)
    {
        addedElements.append(itemList[i]);
    }
    //prints the elements added by user and runs generation
    qDebug() << addedElements << endl;
    MainWindow::generateShittyHtml();
}

void MainWindow::generateShittyHtml() //Generates shit html and outputs it to the text box on the right.
//Still have not figured out how to do the tag closing.
{
    QString htmlString = NULL;
    html.clear();
    html.append("<!DOCTYPE html>");
    html.append("<head>");
    html.append("</head>");
    html.append("<body>");
    for(int i = 0; i < itemList.count(); i++)
    {
        html.append(itemList[i]);
    }
    html.append("</body>");
    html.append("</html>");

    for(int i = 0; i < html.count(); i++)
    {
        htmlString.append(html[i] + '\n');
    }
    ui->textEdit->setPlainText(htmlString);
}


void MainWindow::on_parseElements_itemDoubleClicked(QListWidgetItem *item) //Delete item by doubleclicking
{
    QListWidgetItem *it = ui->parseElements->takeItem(ui->parseElements->currentRow());
    delete it;
}

void MainWindow::on_actionDebug_triggered() //When clicking the "Debug" button write all of the elements to a vector for future use
{
    MainWindow::getParsedItems();
}
