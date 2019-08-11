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
    // Test
    // Write some data to the textBrowser
    //ui->MainWindow->centralWidget->textBrowser->setText("Hello");
    ui->textEdit->setText("Hello World");
    ui->textBrowser->setText("Hello World");
}
