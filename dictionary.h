#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class Dictionary;
}

class Dictionary : public QDialog
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = nullptr);
    ~Dictionary();

    void updateDictionaryList(QList<QString> dictionaryItems);

private slots:
    void on_buttonAdd_clicked();

    void on_buttonRemove_clicked();

    void on_buttonClose_clicked();

private:
    Ui::Dictionary *ui;

signals:
    void addDictionaryItem(QString appendableDictionaryItem);
    void removeDictionaryItem(QString removableDictionaryItem);
};

#endif // DICTIONARY_H
