#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QDir>

class Util
{
public:
    static QString readFile(const QString fileName);
    static QStringList getFileNames(const QString &path);

};

#endif // UTIL_H
