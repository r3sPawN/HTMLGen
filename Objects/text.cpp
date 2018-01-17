#include "text.h"
#include "ui_text.h"

Text::Text(QWidget *parent, QString tag) :
    QDialog(parent),
    ui(new Ui::Text)
{
    ui->setupUi(this);
    element = tag;
}

Text::~Text()
{
    qDebug() << "Destroy" << endl;
    delete ui;
}

void Text::getUserInput()
{
    color = ui->colorBox->text();
    fontface = ui->fontFaceBox->text();
    align = ui->alignBox->currentText();
    usertext = ui->PlainText->toPlainText();
}

void Text::on_OkButton_clicked()
{
    Text::getUserInput();
    storage.append("<");
    storage.append(element);
    storage.append(" style=\"");
    storage.append("color: " + color + "; ");
    storage.append("font-family: \"" + fontface + "\"; ");
    storage.append("text-align: " + align + ";\"");
    storage.append(">");
    storage.append(usertext);
    storage.append("</" + element + ">");
    this->close();
}

void Text::on_CancelButton_clicked()
{
   this->close();
}

QString Text::getFullString()
{
    for (int i = 0; i < storage.size(); i++)
    {
        fullString.append(storage[i]);

    }
    return fullString;
}




