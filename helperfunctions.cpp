#include "helperfunctions.h"
#include <sys/stat.h>
#include <QFile>
#include <QTextStream>



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

void readFromFile(const QString& filename, QVector<QString>& theContent)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            theContent.push_back(in.readLine());
        }
    }
    file.close();
}

void writeToFile(const QString& filename, const QVector<QString>& theContent)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << theContent[0] << endl;
    }
}

void appendToFile(const QString& filename, const QVector<QString>& theContent)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << theContent[0] << endl;
    }
}
