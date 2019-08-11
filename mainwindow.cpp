#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helperfunctions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    QTextStream out(stdout);
    // Get folder from setting file
    QString currentFolder = myJournals.Folder();
    // Get the name from the user
    out << "The folder is: " << currentFolder << endl;
    bool ok;
    QVector<QString> newJournalName;
      newJournalName.push_back(QInputDialog::getText(this, tr("Enter new journal name"),
                                                   tr("Name"), QLineEdit::Normal, "new_journal", &ok));
    // Create a new file in that folder
    if(ok && !newJournalName[0].isEmpty())
    {
        QString fullName = currentFolder+newJournalName[0]+".txt";
        out << fullName << endl;
        writeToFile(fullName, newJournalName );
        // Update the settings file
        // Method 1: read the existing files from the folder

        // Method 2: just add the new name to the settings file
        myJournals.addJournal(fullName);
    }
}

void MainWindow::on_actionLoad_Journals_triggered()
{
    //Test
    // get the home path, to be used to save/load journals location
    QTextStream out(stdout);
    out << "Home Path: " << QDir::homePath() << endl;
    //QDesktopServices::openUrl();

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    QString path = QFileDialog::getExistingDirectory();
    out << "selected: " << path << endl;
}
