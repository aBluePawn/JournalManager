/*
 * The Journal Manager responsibilities:
 * - knows where the journals are saved
 * - loads a file (settings/configuration type) on start and populates the mainwindow
 * - backups
 * -
 * TODO: improve the journals location - give options where it they are saved
 *      at the moment, save new folder, Journals, in the Home folder
 */
// Journal location on disk - folder name
// Number of journals
// Sort the journals by name
// Back up journals


#ifndef JOURNALMANAGER_H
#define JOURNALMANAGER_H

#include <QString>
#include <QVector>


class JournalManager
{
public:
    JournalManager();
    QString Folder();
    QString Journals(); // returns a QString with the name of the existing journals
    void addJournal(const QString);
private:
    QString folder;
    QString settingsFile;
    QVector<QString> savedDetails;
};

#endif // JOURNALMANAGER_H
