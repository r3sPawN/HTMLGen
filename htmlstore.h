#ifndef HTMLSTORE_H
#define HTMLSTORE_H

#include <mainwindow.h>
#include <QVector>

class HTMLStore
{
public:
    HTMLStore();
    ~HTMLStore();

    void insertElement(int line, QString text);
    QString getElementAt(int i);
    QString getAllElements();



private:
    QVector<QString> htmlText;
    void initHtml();
};

#endif // HTMLSTORE_H
