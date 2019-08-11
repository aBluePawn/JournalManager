#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>

// Check if a file exists
bool fileExists(const QString& filename);

// Read the content of a file
void readFromFile(const QString& filename, QVector<QString>& theContent);

// Write the content to a file
void writeToFile(const QString& filename, const QVector<QString>& theContent);

// Append the content to a file
void appendToFile(const QString& filename, const QVector<QString>& theContent);

#endif // HELPERFUNCTIONS_H
