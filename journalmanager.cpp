/* Settings File:
* 1st line: "Journal settings"
* 2nd line: "folder location"
* 3rd line forward: "journals names", one per line
*/

#include <sys/stat.h>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <string>
#include "journalmanager.h"

// Helper functions
bool fileExists(const QString& filename);

JournalManager::JournalManager()
{
    // If path is set, load existing journals
    // If path is not set, create a file in the home folder
    // 1. Read in a txt file, where the folder location is stored

    QString settingsFile = QDir::homePath()+ "/journalSettings.txt";
    QFile file(settingsFile);
    if(fileExists(settingsFile))
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                savedDetails.push_back(in.readLine());
            }
        }
        file.close();
    }
    // Create a new file
    else
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << "Journals Settings" << endl;
            stream << QDir::homePath()+ "/" << endl;
        }
        file.close();
    }
}

// https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
// https://doc.qt.io/qt-5/qstring.html#toStdString
// Check if a file exists
bool fileExists(const QString& filename)
{
    struct stat buf;
    if (stat(filename.toStdString().c_str(), & buf) != -1)
        return true;
    return false;
}

