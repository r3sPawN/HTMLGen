#include "link.h"
#include "ui_link.h"

Link::Link(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Link)
{
    ui->setupUi(this);
    element = tag;
}

Link::~Link()
{
    delete ui;
}

void Link::getUserInput()
{
    address = ui->address->text();
    userText = ui->PlainText->toPlainText();
}

void Link::on_OkButton_clicked()
{
    Link::getUserInput();
    storage.append("<" + element);
    storage.append(" href=\"" + address + "\">");
    storage.append(userText);
    storage.append("</" + element + ">");
    this->close();
}

void Link::on_CancelButton_clicked()
{
    this->close();
}

QString Link::getFullString()
{
    for (int i = 0; i < storage.size(); i++)
    {
        fullString.append(storage[i]);

    }
    return fullString;
}
