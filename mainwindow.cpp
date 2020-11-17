// The Own Header Files
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("School Planner");
    hiddenMenuActions(filePath);

    for (int i = 0; i < ui->scheduleTableWidget->columnCount(); i++) {
        ui->scheduleTableWidget->setColumnWidth(i, 150);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hiddenMenuActions(QString menuFilePath) {

    if(menuFilePath.isEmpty()) {
        ui->actionRooms->setEnabled(false);
        ui->actionTeachers->setEnabled(false);
        ui->actionClasses->setEnabled(false);
        ui->actionGroups->setEnabled(false);

        ui->actionSave->setEnabled(false);
        ui->actionSave_As->setEnabled(false);

    } else {
        ui->actionRooms->setEnabled(true);
        ui->actionTeachers->setEnabled(true);
        ui->actionClasses->setEnabled(true);
        ui->actionGroups->setEnabled(true);

        ui->actionSave->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    filePath = QFileDialog::getOpenFileName(this, "Choose a JSON File", QDir::homePath(),
                                            tr("JSON File (*.json);; All Files(*)"));
    if (filePath.isEmpty()) {
        return ;

    } else {
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Warning!", "JSON File Opening Process Went Wrong!");
            qDebug() << "Failed to Open! " << filePath;
            exit(1);

        } else {
            QTextStream fileText(&file);
            QString jsonString = fileText.readAll();
            file.close();
            QByteArray jsonBytes = jsonString.toLocal8Bit();
            auto jsonDocument = QJsonDocument::fromJson(jsonBytes);

            if (jsonDocument.isNull()) {
                qDebug() << "Failed to Create JSON Document!";
                exit(2);

            } else {

                if (!jsonDocument.isObject()) {
                    qDebug() << "JSON File has no any object!";
                    exit(3);

                } else {
                    QJsonObject jsonObject = jsonDocument.object();

                    if (jsonObject.isEmpty()) {
                        qDebug() << "JSON Object is empty!";
                        exit(4);

                    } else {

                        if (jsonObject.contains(QStringLiteral("rooms"))) {
                            roomValues.clear();
                            //ui->roomComboBox->clear();
                            QJsonArray roomArray = jsonObject["rooms"].toArray();

                            foreach (QJsonValue room, roomArray) {
                                roomValues.append(room.toString());
                            }
                            //renewRoomComboBox() fonksiyonu ve onun da içinde ui->roomComboBox->clear() olacak.

                            for(int i = 0; i < roomArray.count(); i++) {
                                roomArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'rooms'!";
                        }

                        if (jsonObject.contains(QStringLiteral("groups"))) {
                            groupValues.clear();
                            QJsonArray groupArray = jsonObject["groups"].toArray();

                            foreach (QJsonValue group, groupArray) {
                                groupValues.append(group.toString());
                            }

                            for(int i = 0; i < groupArray.count(); i++) {
                                groupArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'groups'!";
                        }

                        if (jsonObject.contains(QStringLiteral("classes"))) {
                            classValues.clear();
                            QJsonArray classArray = jsonObject["classes"].toArray();

                            foreach (QJsonValue xclass, classArray) {
                                classValues.append(xclass.toString());
                            }

                            for(int i = 0; i < classArray.count(); i++) {
                                classArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'classes'!";
                        }

                        if (jsonObject.contains(QStringLiteral("teachers"))) {
                            teacherValues.clear();
                            QJsonArray teacherArray = jsonObject["teachers"].toArray();

                            foreach (QJsonValue teacher, teacherArray) {
                                teacherValues.append(teacher.toString());
                            }

                            for(int i = 0; i < teacherArray.count(); i++) {
                                teacherArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'teachers'!";
                        }

                        if (jsonObject.contains(QStringLiteral("days"))) {
                            dayValues.clear();
                            QJsonArray dayArray = jsonObject["days"].toArray();

                            foreach (QJsonValue day, dayArray) {
                                dayValues.append(day.toInt());
                            }

                            for(int i = 0; i < dayArray.count(); i++) {
                                dayArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'days'!";
                        }

                        if (jsonObject.contains(QStringLiteral("slots"))) {
                            slotValues.clear();
                            QJsonArray slotArray = jsonObject["slots"].toArray();

                            foreach (QJsonValue slot, slotArray) {
                                slotValues.append(slot.toInt());
                            }

                            for(int i = 0; i < slotArray.count(); i++) {
                                slotArray.removeAt(i);
                            }

                        } else {
                            qDebug() << "JSON File has no key what is named as 'slots'!";
                        }

                        if (jsonObject.contains(QStringLiteral("activities"))) {
                            activitiesRoomValues.clear();
                            activitiesGroupValues.clear();
                            activitiesClassValues.clear();
                            activitiesTeacherValues.clear();
                            activitiesDayValues.clear();
                            activitiesSlotValues.clear();

                            QJsonArray activitiesArray = jsonObject["activities"].toArray();

                            foreach (const QJsonValue &activity, activitiesArray) {
                                QJsonObject activityObject = activity.toObject();

                                activitiesRoomValues.append(activityObject["room"].toString());
                                activitiesGroupValues.append(activityObject["group"].toString());
                                activitiesClassValues.append(activityObject["class"].toString());
                                activitiesTeacherValues.append(activityObject["teacher"].toString());
                                activitiesDayValues.append(activityObject["day"].toInt());
                                activitiesSlotValues.append(activityObject["slot"].toInt());
                            }

                        } else {
                            QMessageBox::warning(this, "Warning!", "JSON File has no key what is named as 'activities'!");
                            this->close();
                        }
                    }
                }
            }
        }
    }

    ui->roomComboBox->clear();
    ui->roomComboBox->addItems(roomValues);
    /*
    foreach (const QString &room, roomValues) {
        ui->roomComboBox->addItem(room);
    }
    */

    hiddenMenuActions(filePath);
}

void MainWindow::saveFile(QString saveFilePath)
{
    QJsonArray roomArray,
               groupArray,
               classArray,
               teacherArray,
               dayArray,
               slotArray,
               activitiesArray;

    for (int i = 0; i < roomValues.length(); i++) {
        roomArray.append(roomValues[i]);
    }

    for (int i = 0; i < groupValues.length(); i++) {
        groupArray.append(groupValues[i]);
    }

    for (int i = 0; i < classValues.length(); i++) {
        classArray.append(classValues[i]);
    }

    for (int i = 0; i < teacherValues.length(); i++) {
        teacherArray.append(teacherValues[i]);
    }

    for (int i = 0; i < dayValues.length(); i++) {
        dayArray.append(dayValues[i]);
    }

    for (int i = 0; i < slotValues.length(); i++) {
        slotArray.append(slotValues[i]);
    }


    for (int i = 0; i < activitiesRoomValues.length(); i++) {
        QJsonObject activitiesObject;
        activitiesObject.insert("room", activitiesRoomValues.at(i));
        activitiesObject.insert("group", activitiesGroupValues.at(i));
        activitiesObject.insert("class", activitiesClassValues.at(i));
        activitiesObject.insert("teacher", activitiesTeacherValues.at(i));
        activitiesObject.insert("day", activitiesDayValues.at(i));
        activitiesObject.insert("slot", activitiesSlotValues.at(i));
        activitiesArray.append(activitiesObject);
    }

    QJsonObject jsonObject;
    jsonObject.insert("rooms", roomArray);
    jsonObject.insert("groups", groupArray);
    jsonObject.insert("classes", classArray);
    jsonObject.insert("teachers", teacherArray);
    jsonObject.insert("days", dayArray);
    jsonObject.insert("slots", slotArray);
    jsonObject.insert("activities", activitiesArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);

    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::JsonFormat());
    QFile savedFile(saveFilePath);
    savedFile.open(QIODevice::WriteOnly);
    savedFile.write(byteArray);
    savedFile.close();
}

void MainWindow::on_actionSave_triggered()
{
    saveFile(filePath);
}

void MainWindow::on_actionSave_As_triggered()
{
    QString saveFilePath = QFileDialog::getSaveFileName(this, "Determine a Path for JSON File", QDir::homePath(),
                                            tr("JSON File (*.json);; All Files(*)"));
    if (saveFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "The path is NOT Determined!");

    } else {
        saveFile(saveFilePath);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionRooms_triggered()
{
    Dictionary *roomDictionary = new Dictionary;
    roomDictionary->updateDictionaryList(roomValues);
    roomDictionary->show();

    connect(roomDictionary, &Dictionary::addDictionaryItem, [=](QString item) {
        roomValues.append(item);
        ui->roomComboBox->clear();
        ui->roomComboBox->addItems(roomValues);
    });

    connect(roomDictionary, &Dictionary::removeDictionaryItem, [=](QString item) {
        roomValues.removeOne(item);
        ui->roomComboBox->clear();
        ui->roomComboBox->addItems(roomValues);
    }); 
}

void MainWindow::on_actionTeachers_triggered()
{
    Dictionary *teacherDictionary = new Dictionary;
    teacherDictionary->updateDictionaryList(teacherValues);
    teacherDictionary->show();

    connect(teacherDictionary, &Dictionary::addDictionaryItem, [=](QString item) {
        teacherValues.append(item);
    });

    connect(teacherDictionary, &Dictionary::removeDictionaryItem, [=](QString item) {
        teacherValues.removeOne(item);
    });
}

void MainWindow::on_actionGroups_triggered()
{
    Dictionary *groupDictionary = new Dictionary;
    groupDictionary->updateDictionaryList(groupValues);
    groupDictionary->show();

    connect(groupDictionary, &Dictionary::addDictionaryItem, [=](QString item) {
        groupValues.append(item);
    });

    connect(groupDictionary, &Dictionary::removeDictionaryItem, [=](QString item) {
        groupValues.removeOne(item);
    });
}

void MainWindow::on_actionClasses_triggered()
{
    Dictionary *classDictionary = new Dictionary;
    classDictionary->updateDictionaryList(classValues);
    classDictionary->show();

    connect(classDictionary, &Dictionary::addDictionaryItem, [=](QString item) {
        classValues.append(item);
    });

    connect(classDictionary, &Dictionary::removeDictionaryItem, [=](QString item) {
        classValues.removeOne(item);
    });
}

void MainWindow::on_roomComboBox_currentTextChanged(const QString &selectedRoom)
{
    ui->scheduleTableWidget->clearContents();

    for (int indexRoom = 0; indexRoom < activitiesRoomValues.length(); indexRoom++) {
        QTableWidgetItem *item = new QTableWidgetItem(tr("(%1)[%2]{%3}").
                                                      arg(activitiesGroupValues[indexRoom]).
                                                      arg(activitiesClassValues[indexRoom]).
                                                      arg(activitiesTeacherValues[indexRoom]));

        if (selectedRoom == activitiesRoomValues[indexRoom]) {
            ui->scheduleTableWidget->setItem(activitiesSlotValues[indexRoom],
                                             activitiesDayValues[indexRoom], item);
        }
    }
}

void MainWindow::on_scheduleTableWidget_doubleClicked(const QModelIndex &index)
{
    Entry *newEntry = new Entry;
    newEntry->transferData(ui->roomComboBox->currentText(),
                           groupValues, classValues, teacherValues);


    if (index.data().toString() == "") {

    } else {
        newEntry->visibleUnassignButton();

        for (int i = 0; i < activitiesRoomValues.length(); i++) {
            if (activitiesRoomValues[i] == ui->roomComboBox->currentText() &&
                    activitiesSlotValues[i] == slotValues[index.row()] &&
                    activitiesDayValues[i] == dayValues[index.column()]) {

                newEntry->updateData(activitiesRoomValues[i],
                                     activitiesGroupValues[i],
                                     activitiesClassValues[i],
                                     activitiesTeacherValues[i]);
                break;
            }
        }
    }

    newEntry->show();

    connect(newEntry, &Entry::assign, [=](QString group, QString clas, QString teacher) {
        QList<QString> tempActivitiesGroupValues,
                       tempActivitiesClassValues,
                       tempActivitiesTeacherValues,
                       tempActivitiesRoomValues;

       QList<int> tempActivitiesDayValues,
                  tempActivitiesSlotValues;

       tempActivitiesGroupValues.append(group);
       tempActivitiesClassValues.append(clas);
       tempActivitiesTeacherValues.append(teacher);

        if (index.data().toString().isEmpty()) {

            tempActivitiesRoomValues.append(ui->roomComboBox->currentText());
            tempActivitiesDayValues.append(dayValues[index.column()]);
            tempActivitiesSlotValues.append(slotValues[index.row()]);

        } else {

            tempActivitiesRoomValues.append(activitiesRoomValues);
            tempActivitiesSlotValues.append(activitiesSlotValues);
            tempActivitiesDayValues.append(activitiesDayValues);

            activitiesRoomValues.removeOne(index.data().toString());
            activitiesGroupValues.removeOne(index.data().toString());
            activitiesClassValues.removeOne(index.data().toString());
            activitiesTeacherValues.removeOne(index.data().toString());
            activitiesDayValues.removeOne(index.column());
            activitiesSlotValues.removeOne(index.row());
        }

        activitiesRoomValues.append(tempActivitiesRoomValues);
        activitiesGroupValues.append(tempActivitiesGroupValues);
        activitiesClassValues.append(tempActivitiesClassValues);
        activitiesTeacherValues.append(tempActivitiesTeacherValues);
        activitiesDayValues.append(tempActivitiesDayValues);
        activitiesSlotValues.append(tempActivitiesSlotValues);

        on_roomComboBox_currentTextChanged(ui->roomComboBox->currentText());
    });

    connect(newEntry, &Entry::unAssign, [=]() {
        if (!(index.data().toString().isEmpty())) {

            QString scheduledData = index.data().toString();

            int i = scheduledData.split(QString()).indexOf("{");
            QString groupName;
            for (;i < scheduledData.split(QString()).indexOf("}")-1; i++) {
                groupName = groupName + scheduledData[i];
            }

            int j = scheduledData.split(QString()).indexOf("[");
            QString className;
            for (; j < scheduledData.split(QString()).indexOf("]")-1; j++) {
                className = className + scheduledData[j];
            }

            int k = scheduledData.split(QString()).indexOf("{");
            QString teacherName;
            for (; k < scheduledData.split(QString()).indexOf("}")-1; k++) {
                teacherName = teacherName + scheduledData[k];
            }

            activitiesRoomValues.removeOne(ui->roomComboBox->currentText());
            activitiesGroupValues.removeOne(groupName);
            activitiesClassValues.removeOne(className);
            activitiesTeacherValues.removeOne(teacherName);
            activitiesDayValues.removeOne(index.column());
            activitiesSlotValues.removeOne(index.row());
        }

        on_roomComboBox_currentTextChanged(ui->roomComboBox->currentText());
    });
}

























