#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// The Other Header Files
#include <dictionary.h>
#include <entry.h>

// THE LIBRARIES THAT COULD BE USEFUL
// for json files
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>

// for file processing
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QString>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Variables
    QString filePath;
    QList<QString> roomValues,
                   groupValues,
                   classValues,
                   teacherValues;
    QList<int> dayValues,
               slotValues;

    QList<QString> activitiesRoomValues,
                   activitiesGroupValues,
                   activitiesClassValues,
                   activitiesTeacherValues;
    QList<int> activitiesDayValues,
               activitiesSlotValues;

    void hiddenMenuActions(QString filePath);
    void saveFile(QString saveFilePath);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionQuit_triggered();

    void on_actionRooms_triggered();

    void on_actionTeachers_triggered();

    void on_actionGroups_triggered();

    void on_actionClasses_triggered();

    void on_roomComboBox_currentTextChanged(const QString &arg1);

    void on_scheduleTableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H



























