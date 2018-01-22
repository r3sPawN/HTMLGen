#include "htmlstore.h"

//Constructor - Calls initHtml()
HTMLStore::HTMLStore()
{
    initHtml();
}

//Destructor for the class
HTMLStore::~HTMLStore()
{
    htmlText.clear(); //Clears all elements from the vector
    htmlText.squeeze(); //Frees up the memory.
}

//Funciton that inserts the basics needed for a functioning HTML File.
void HTMLStore::initHtml()
{
    //Appends the needed tags to the 'htmlText' to create a blank HTML File.
    htmlText.append("<!DOCTYPE html>");
    htmlText.append("<head>");
    htmlText.append("<style>");
    htmlText.append("");
    htmlText.append("</style>");
    htmlText.append("");
    htmlText.append("</head>");
    htmlText.append("<body>");
    htmlText.append("");
    htmlText.append("</body>");
    htmlText.append("</html>");
}

//Function to return the element at index i. Used for tidyness and completeness of getters
QString HTMLStore::getElementAt(int i)
{
    return htmlText[i]; //Returns element from QVector at index i
}

//Function to Return a string of all of the elements of the main storage vector
QString HTMLStore::getAllElements()
{
    QString fullText; //Initialize a QString 'fulltext'
    for(int i = 0; i < htmlText.length(); i++) //Iterates through the vector of HTML tags
    {
        fullText.append(getElementAt(i) + "\n"); //Appends each element of the vector to the string 'fullText'
    }

    return fullText; //Return string fullText
}

//Function to insert an element at a certain index. Takes an integer for the line to insert at and QString for the contents
void HTMLStore::insertElement(int line, QString text)
{
    htmlText.insert(line, text); //Inserts the given parameters in the main storage vector
}

//Returns the size of the main storage vector
int HTMLStore::getSize()
{
    return htmlText.size();
}

//Resets the main storage vector
void HTMLStore::reset()
{
    htmlText.clear(); //Empties the vector of all of the elements
    htmlText.squeeze(); //Frees up the memory
}
