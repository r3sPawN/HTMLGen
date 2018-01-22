#ifndef HTMLSTORE_H
#define HTMLSTORE_H

#include <QVector>

class HTMLStore
{
public:
    HTMLStore(); //Class constructor
    ~HTMLStore(); //Class destructor

    void insertElement(int line, QString text); //Insert a QString at given index
    QString getElementAt(int i); //Return the QString of index i
    QString getAllElements(); //Return all elements from the HTML Storage Vector
    int getSize(); //Get size of the vector
    void reset(); //Reset the vector and free up the memory
    void initHtml(); //Initialize the basic HTML skeleton/template.

private:
    QVector<QString> htmlText; //QVector of QStrings that holds the skeleton plus user content

};

#endif // HTMLSTORE_H
