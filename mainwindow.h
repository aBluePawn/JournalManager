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
#include <QPushButton>
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

    // Associate a string with a QPushButton
    // TO DO: implement this function in a more efficient way
    //bool findButton(const QString&, QPushButton*);

public slots:
    void on_actionNew_triggered();
    void on_actionLoad_Journals_triggered();
    void selectJournal();

private slots:
    void on_save_entry_clicked();

private:
    Ui::MainWindow *ui;
    JournalManager myJournals;
    QPushButton * buttons[5];
};

#endif // MAINWINDOW_H
