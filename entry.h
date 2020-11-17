#ifndef ENTRY_H
#define ENTRY_H

#include "ui_entry.h"
#include <QDialog>

namespace Ui {
class Entry;
}

class Entry : public QDialog
{
    Q_OBJECT

public:
    explicit Entry(QWidget *parent = nullptr);
    ~Entry();

    void transferData(QString room, QList<QString> groupList, QList<QString> classList, QList<QString> teacherList);
    void updateData(QString room,QString group, QString clas, QString teacher);
    void hiddenUnassignButton();
    void visibleUnassignButton();

private slots:
    void on_buttonUnassign_clicked();

    void on_buttonSave_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::Entry *ui;

signals:
    void unAssign();
    void assign(QString group, QString clas, QString teacher);
};

#endif // ENTRY_H
