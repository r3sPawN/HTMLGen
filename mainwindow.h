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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    QString sFilename;
    QString Path;
    bool isUntitled;

    void generateHtml();
    HTMLStore htmlstore;
};

#endif // MAINWINDOW_H
