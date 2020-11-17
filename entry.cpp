#include "entry.h"
#include "ui_entry.h"

Entry::Entry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entry)
{
    ui->setupUi(this);
    setWindowTitle("Edit Entry");

    hiddenUnassignButton();
}

Entry::~Entry()
{
    delete ui;
}

void Entry::hiddenUnassignButton()
{
    ui->buttonUnassign->setHidden(true);
}

void Entry::visibleUnassignButton()
{
    ui->buttonUnassign->setVisible(true);
}

void Entry::transferData(QString room, QList<QString> groupList, QList<QString> classList, QList<QString> teacherList)
{
    ui->roomText->setText(room);
    ui->groupComboBox->addItems(groupList);
    ui->classComboBox->addItems(classList);
    ui->teacherComboBox->addItems(teacherList);
}

void Entry::updateData(QString room, QString group, QString clas, QString teacher)
{
    ui->roomText->setText(room);
    ui->groupComboBox->setCurrentText(group);
    ui->classComboBox->setCurrentText(clas);
    ui->teacherComboBox->setCurrentText(teacher);
}


void Entry::on_buttonUnassign_clicked()
{
    emit unAssign();
    this->close();
}

void Entry::on_buttonSave_clicked()
{
    emit assign(ui->groupComboBox->currentText(),
                ui->classComboBox->currentText(),
                ui->teacherComboBox->currentText());
    this->close();
}

void Entry::on_buttonCancel_clicked()
{
    this->close();

}
