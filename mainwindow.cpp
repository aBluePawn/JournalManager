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

    buttons[0] = ui->pushButton_1;
    buttons[1] = ui->pushButton_2;
    buttons[2] = ui->pushButton_3;
    buttons[3] = ui->pushButton_4;
    buttons[4] = ui->pushButton_5;

    /*
     *  use one private slot to connect the existing journals buttons
     * The sender() approach, see
     * https://doc.qt.io/archives/qq/qq10-signalmapper.html
     * Currently using 5 buttons
    */

    for (int i=0; i<5; i++)
    {
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(selectJournal()));
    }

    // Add a placeholder on the textEdit area for new entry
    ui->textEdit_2->setPlaceholderText("Load an existing Journal or create a New one.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// slot for the existing journals buttons
void MainWindow::selectJournal()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    ui->textEdit->setText(buttonSender->text());
    ui->current_journal->setTitle("Current Journal: " + buttonSender->text());
    ui->textEdit_2->setPlaceholderText("Enter text for your new entry here, then click Save");
}

void MainWindow::on_actionNew_triggered()
{
    // Get folder from setting file
    QString currentFolder = myJournals.Folder();
    // Get the name from the user
    bool ok;
    QVector<QString> newJournalName;
      newJournalName.push_back(QInputDialog::getText(this, tr("Enter new journal name"),
                                                   tr("Name"), QLineEdit::Normal, "new_journal", &ok));
    // Create a new file in that folder
    if(ok && !newJournalName[0].isEmpty())
    {
        QString fullName = currentFolder+newJournalName[0]+".txt";
        writeToFile(fullName, newJournalName );
        // Update the settings file
        // Method 1: read the existing files from the folder

        // Method 2: just add the new name to the settings file
        myJournals.addJournal(newJournalName[0]);
    }
}

void MainWindow::on_actionLoad_Journals_triggered()
{
    // Test

    QString existingJournals = myJournals.Journals();
    //QTextStream out(stdout);
    //out << existingJournals << endl;

    QStringList list = existingJournals.split(QRegExp("[\n]+"), QString::SkipEmptyParts);


    for(int i=list.size(); i<5; i++) // for now use only 5 journals
    {
        list.append("empty");
    }

    for(int i=0; i<5; i++)
    {
        buttons[i]->setText(list.at(i));
    }
    ui->textEdit_2->setPlaceholderText("Select an existing Journal or create a New one.");
}

/*
// https://forum.qt.io/topic/88768/how-to-use-string-as-ui-qpushbutton-typecast
bool MainWindow::findButton(const QString &buttonName, QPushButton* foundButton)
{
    QPushButton *button = ui->findChild<QPushButton *>("buttonName");
    if(button)
    {
        foundButton = button;
        return true;
    }
    else {
        return false;
    }

}
*/

void MainWindow::on_save_entry_clicked()
{
    QString entry = ui->textEdit_2->toPlainText();
    QString currentJournal = ui->current_journal->title();
    currentJournal = currentJournal.right(currentJournal.length()-17); // 17 is the length of "Current Journal:"
    currentJournal = myJournals.Folder()+currentJournal + ".txt";
    QVector<QString> newEntry;
    newEntry.push_back(entry);
    appendToFile(currentJournal , newEntry);

    ui->textEdit_2->setText("");
    ui->textEdit_2->setPlaceholderText("Entry saved! Enter text for your new entry here, then click Save");
}
