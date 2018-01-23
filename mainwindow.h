#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "htmlstore.h"
#include "Objects/text.h"
#include "Objects/image.h"
#include "Objects/link.h"
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QDesktopServices> //needed for opening a browser
#include <QUrl> //needed for opening a browser
#include <QFileInfo>
#include <QDebug>
#include <QtDebug> // for testing
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); //Constructor for the main window
    ~MainWindow(); //Destructor


//Slots for all the buttons in the menu bar and dropdown.
private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_triggered();

    void on_actionPreview_triggered();

    void on_actionSave_as_triggered();

    void on_parseElements_itemDoubleClicked();

    void on_actionGenerate_triggered();

    void on_actionExit_triggered();

    void on_actionDelete_triggered();

private:
    Ui::MainWindow *ui; //UI for the main window
    HTMLStore htmlstore; //HTMLStore class for data storage

    void generateHtml(); //Function to generate the HTML
    QString sFilename, Path; //QStrings that contain the Filename and file path
};

#endif // MAINWINDOW_H
