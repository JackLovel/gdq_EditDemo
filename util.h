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
    static void setClipboardContent();
    static QString getClipboardContent();
    static QString getSplitLast(QString path, QString separator);
    static QString FileGbkToUtf8(QString path);
    static QString FileUtf8ToGbk(QString path);
    static QString GbkToUtf8(const char* szGBK);
    static void checkDirExist(const QString &path);
};

#endif // UTIL_H
