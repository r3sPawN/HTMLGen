#include "image.h"
#include "ui_image.h"

Image::Image(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    element = tag;
}

Image::~Image()
{
    delete ui;
}
void Image::getUserInput()
{
    address = ui->address->text();
    height = ui->height->text();
    width = ui->width->text();

    if(height == "0")
        height = "auto";

    if(width == "0")
        width = "auto";
}

void Image::on_OkButton_clicked()
{
    Image::getUserInput();
    storage.append("<" + element);
    storage.append(" src=\""+ address + "\" ");
    storage.append("height=\"" + height + "\" ");
    storage.append("width=\"" + width + "\"");
    storage.append(">");
    this->close();
}

void Image::on_CancelButton_clicked()
{
    this->close();
}

QString Image::getFullString()
{
    for (int i = 0; i < storage.size(); i++)
    {
        fullString.append(storage[i]);

    }
    return fullString;
}
