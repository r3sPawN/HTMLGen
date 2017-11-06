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

        ui->textEdit->setPlainText(text);
    }

}

void MainWindow::on_actionNew_triggered() //new
{
    sFilename = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionUndo_triggered() //undo
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered() //redo
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSave_triggered() //save (needs some more work)
{
    QFile sFile(sFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);

        out << ui -> textEdit -> toPlainText();

        sFile.flush();
        sFile.close();

        //QFileInfo info(sFile);
        //Path = info.absoluteDir();
    }

}

void MainWindow::on_actionPreview_triggered()
{
    QString link = "https://www.google.bg";
    QDesktopServices::openUrl(QUrl(link));
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
