#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QDir>

class Util
{
public:
    static QString readFile(const QString fileName);
    static QStringList getFileNames(const QString &path);
    static int cellWithPercent(int n, int m); // 求两数的百分比
    static void writeSetting(const QString &key, const QString &value);
    static QMap<QString, QString> readSetting();


};

#endif // UTIL_H
