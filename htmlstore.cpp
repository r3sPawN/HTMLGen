#include "htmlstore.h"

HTMLStore::HTMLStore()
{
    HTMLStore::initHtml();
}

HTMLStore::~HTMLStore()
{
    htmlText.clear();
    htmlText.squeeze();
}

void HTMLStore::initHtml()
{
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


QString HTMLStore::getElementAt(int i)
{
    return htmlText[i];
}

QString HTMLStore::getAllElements()
{
    QString fullText;
    for(int i = 0; i < htmlText.length(); i++)
    {
        fullText.append(HTMLStore::getElementAt(i) + "\n");
    }
    return fullText;
}

void HTMLStore::insertElement(int line, QString text)
{
    htmlText.insert(line, text);
}
