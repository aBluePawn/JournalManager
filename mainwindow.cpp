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

    displayJournal(buttonSender->text());

    ui->textEdit_2->setPlaceholderText("Enter text for your new entry here, then click Save");
    // Enalble the Save button
    ui->save_entry->setEnabled(true);
}

void MainWindow::displayJournal(QString jurnalName)
{
    // Read the content of the selected journal
    QString fullName = myJournals.Folder() + jurnalName + ".txt";
    QVector<QString> content;
    readFromFile(fullName, content);
    QString strContent;
    for(int i=0; i<content.size(); i++)
    {
        strContent = strContent + content[i] + "\n";
    }
    ui->textEdit->setText(strContent);
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
    QMessageBox msgBox;
    // Create a new file in that folder
    if(ok && !newJournalName[0].isEmpty())
    {
        QString fullName = currentFolder+newJournalName[0]+".txt";
        writeToFile(fullName, newJournalName );
        // Update the settings file
        // Method 1: read the existing files from the folder

        // Method 2: just add the new name to the settings file
        myJournals.addJournal(newJournalName[0]);
        msgBox.setText("Journal " + newJournalName[0] + " created.");
    }
    else
    {
        msgBox.setText("The journal name cannot be empty, please try again.");
    }
    msgBox.exec();
}

void MainWindow::on_actionLoad_Journals_triggered()
{
    QString existingJournals = myJournals.Journals();
    QStringList list = existingJournals.split(QRegExp("[\n]+"), QString::SkipEmptyParts);

    for(int i=0; i<list.size() && i<5; i++) // 5 is the # of journals available to display at the moment
    {
        buttons[i]->setText(list.at(i));
        buttons[i]->setEnabled(true);
    }
    /*
    for(int i=list.size(); i<5; i++) // for now use only 5 journals
    {
        list.append("empty");
        buttons[i]->setText(list.at(i));
    }
    */
    ui->textEdit_2->setPlaceholderText("Select an existing Journal or create a New one.");
}

void MainWindow::on_save_entry_clicked()
{
    QString entry = ui->textEdit_2->toPlainText();
    QString currentJournal = ui->current_journal->title();
    currentJournal = currentJournal.right(currentJournal.length()-17); // 17 is the length of "Current Journal:"
    QString journalFullPath = myJournals.Folder()+currentJournal + ".txt";
    QVector<QString> newEntry;
    newEntry.push_back(entry);
    appendToFile(journalFullPath , newEntry);

    // Display the updated content
    displayJournal(currentJournal);

    // Reset the entry area
    ui->textEdit_2->setText("");
    ui->textEdit_2->setPlaceholderText("Entry saved! Enter text for your new entry here, then click Save");
}
