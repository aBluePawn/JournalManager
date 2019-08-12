/* Settings File:
* 1st line: "Journal settings"
* 2nd line: "folder location"
* 3rd line forward: "journals names", one per line
*/


#include <QTextStream>
#include <QFile>
#include <QDir>
#include <string>
#include "journalmanager.h"
#include "helperfunctions.h"

JournalManager::JournalManager()
{
    // If path is set, load existing journals
    // If path is not set, create a file in the home folder
    // 1. Read in a txt file, where the folder location is stored

    settingsFile = QDir::homePath()+ "/journalSettings.txt";
    QFile file(settingsFile);
    if(fileExists(settingsFile))
    {
        readFromFile(settingsFile, savedDetails);
    }
    // Create a new file
    else
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << "Journal Settings" << endl; // I use this first line to identify a valid settings file
            QDir dir;
            QString folderName = QDir::homePath()+ "/myJournals/";
            dir.mkdir(folderName);
            stream << folderName << endl;
            readFromFile(settingsFile, savedDetails);
        }
        file.close();
    }
    folder = savedDetails[1];
}

// Return the path stored in settings
// At the moment this is the home directory, it may be different in the future
QString JournalManager::Folder()
{
    return folder;
}

// Return a string with all the names of existing journals
QString JournalManager::Journals()
{
    QString journals;
    if(savedDetails.size()>2)
    {
        for(int i = 2; i<savedDetails.size(); i++)
        {
            journals += savedDetails[i] + "\n";
        }
    }
    return journals;
}

// Add a journal name to the list in settings
void JournalManager::addJournal(const QString newJournalName)
{

    // Sort the list of journals and rewrite the settings file

    // Or just append the new name
    QVector<QString> name;
    QString linkName = "<a href>" + newJournalName + "</a><br>";
    savedDetails.push_back(linkName);
    name.push_back(linkName);

    appendToFile(settingsFile, name);
}
