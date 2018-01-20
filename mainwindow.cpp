#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionNew_triggered();
    setWindowTitle("Simple Html Generator");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered() //open function
{
    QString File = QFileDialog::getOpenFileName(this,"Open a file"), setFileMode("*html"); //opening a window used to find a file
    // need to add error checking
    QFile sFile(File);
    if(sFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&sFile);
        QString text = in.readAll();
        sFile.close();

        ui->textEdit->setPlainText(text);
        ui->textEdit->textChanged();

        QFileInfo fileInfo(sFile);
        setWindowTitle(fileInfo.fileName());
    }
}

void MainWindow::on_actionNew_triggered() //new
{
    sFilename = "";
    isUntitled = true;
    htmlstore.reset();
    ui->parseElements->clear();
    ui->textEdit->clear();
}


void MainWindow::on_actionUndo_triggered() //undo
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered() //redo
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSave_triggered()
{

    if(isUntitled == true)
    {
        return on_actionSave_as_triggered();
    }
    else
    {
        QFile sFile(sFilename);
        if(sFile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&sFile);

            out << ui -> textEdit -> toPlainText();

            sFile.flush();
            sFile.close();

            ui->statusBar->showMessage("Saved", 2000);

            QFileInfo fileInfo(sFile);
            setWindowTitle(fileInfo.fileName());
            Path = fileInfo.absoluteFilePath();
        }
    }
}

void MainWindow::on_actionPreview_triggered() //Preview
{
    if (isUntitled == true)
    {
        QMessageBox::StandardButton ret;
               ret = QMessageBox::warning(this, tr("Warning"),
                            tr("The document has not been saved yet.\n"
                               "Do you want to save it?"),
                            QMessageBox::Save | QMessageBox::Discard);
               if (ret == QMessageBox::Save)
                   return on_actionSave_triggered();
    }
    else
    {
        QDesktopServices::openUrl(QUrl(Path));
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString File = QFileDialog::getSaveFileName(this,"Saving a file");

    if(!File.isEmpty())
    {
        sFilename = File;
        isUntitled = false;
        on_actionSave_triggered();
    }
}

void MainWindow::generateHtml() //Generates html and outputs it to the text box on the right.
{
    htmlstore.reset();
    htmlstore.initHtml();
    QListWidgetItem* nthItem;
    QVariant itemData;

    for(int i = 0; i < ui->parseElements->count(); i++)
    {
        nthItem = ui->parseElements->item(i);
        if(nthItem->text().at(0) == "<")
            nthItem->setData(32, nthItem->text());

        itemData = nthItem->data(32);

        if (itemData.value<QString>() == NULL)
            nthItem->setData(32, "Element still uninitialized. Doubleclick it to get started!");

        itemData = nthItem->data(32);
        htmlstore.insertElement(i + 8, itemData.value<QString>());
    }

    QString bodyContent = htmlstore.getAllElements();
    ui->textEdit->setPlainText(bodyContent);
}

void MainWindow::on_parseElements_itemDoubleClicked()
{
    QListWidgetItem* currentItem = ui->parseElements->currentItem();
    QString currentItemString = currentItem->text();

    if (currentItemString.at(0) == "<")
    {
        qDebug() << "Nothing to edit!" << endl;
    }

    else if (currentItemString == "img")
    {
        Image* img = new Image(0, currentItemString);
        img->setModal(true);
        img->exec();
        currentItem->setData(32, img->getFullString());
    }

    else if (currentItemString == "a")
    {
        Link* url = new Link(0, currentItemString);
        url->setModal(true);
        url->exec();
        currentItem->setData(32, url->getFullString());
    }

    else
    {
        Text* txt = new Text(0, currentItemString);
        txt->setModal(true);
        txt->exec();
        currentItem->setData(32, txt->getFullString());
    }

}

void MainWindow::on_actionGenerate_triggered() //When clicking the "Debug" button write all of the elements to a vector for future use
{
    if(htmlstore.getSize() <= 0)
        htmlstore.initHtml();
    MainWindow::generateHtml();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
