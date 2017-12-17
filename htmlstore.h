#ifndef HTMLSTORE_H
#define HTMLSTORE_H

#include <QVector>

class HTMLStore
{
public:
    HTMLStore();
    ~HTMLStore();

    void insertElement(int line, QString text);
    QString getElementAt(int i);
    QString getAllElements();
    int getSize();
    void reset();
    void initHtml();

private:
    QVector<QString> htmlText;

};

#endif // HTMLSTORE_H
