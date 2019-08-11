/*
* The app has two panels:
* - on the left, the names of the existing journals, ordered alphabetically,
* - on the right, the journal content, on two columns:
*       1. tasks
*       2. entries
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "journalmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionLoad_Journals_triggered();

private:
    Ui::MainWindow *ui;
    JournalManager myJournals;
};

#endif // MAINWINDOW_H
