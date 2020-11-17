#include "dictionary.h"
#include "ui_dictionary.h"

#include <QList>

Dictionary::Dictionary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);
    setWindowTitle("Edit Dictionary");
}

Dictionary::~Dictionary()
{
    delete ui;
}

void Dictionary::updateDictionaryList(QList<QString> dictionaryItems) {
    for (int i = 0; i < dictionaryItems.length(); ++i) {
        ui->dictionaryList->addItem(dictionaryItems[i]);
    }
}

void Dictionary::on_buttonAdd_clicked()
{

    QDialog *newEntry = new QDialog;
    newEntry->setGeometry(this->geometry().x(), this->geometry().y(),(this->geometry().width()-53), (this->geometry().height()-200));
    QVBoxLayout *vLayout = new QVBoxLayout(newEntry);

    QLabel *enterValueLabel = new QLabel("Enter value");
    QLineEdit *lineEdit = new QLineEdit;
    QPushButton *buttonOK = new QPushButton("OK");

    vLayout->addWidget(enterValueLabel);
    vLayout->addWidget(lineEdit);
    vLayout->addWidget(buttonOK);

    newEntry->show();

    connect(buttonOK, &QPushButton::clicked, [=]() {
        if(!lineEdit->text().isEmpty()) {
            ui->dictionaryList->addItem(lineEdit->text());
            emit addDictionaryItem(lineEdit->text());
            newEntry->close();
        }
    });

}

void Dictionary::on_buttonRemove_clicked()
{
    emit removeDictionaryItem(ui->dictionaryList->currentItem()->text());
    ui->dictionaryList->takeItem(ui->dictionaryList->currentRow());
}

void Dictionary::on_buttonClose_clicked()
{
    this->close();
}
