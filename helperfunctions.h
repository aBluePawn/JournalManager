#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>

// Check if a file exists
bool fileExists(const QString& filename);

// Read the content of a file
void readFromFile(const QString& filename, QVector<QString>& theContent);

#endif // HELPERFUNCTIONS_H
