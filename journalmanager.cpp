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

    QString settingsFile = QDir::homePath()+ "/journalSettings.txt";
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
        }
        file.close();
    }
}
