#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QDesktopServices> //needed for opening a browser
#include <QUrl> //needed for opening a browser
#include <QFileInfo>
#include <QtDebug> // for testing

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

private:
    Ui::MainWindow *ui;
    QString sFilename;
    QString Path;
};

#endif // MAINWINDOW_H
