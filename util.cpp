#include "util.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QtMath>

// 读取文本内容
QString Util::readFile(const QString fileName)
{
    QString content = "";
    QTextCodec *code = QTextCodec::codecForName("utf8"); // utf-8 编码读取
    if (!fileName.isEmpty()) {
        QFile *file = new QFile();
        file->setFileName(fileName);
        bool ok = file->open(QIODevice::ReadOnly);
        if (ok) {
            QTextStream read(file);
            read.setCodec(code);
            content = read.readAll();
            file->close();
            delete file;
        } else {
            content = "";
        }
    }

    return content;
}

QStringList Util::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}

int Util::cellWithPercent(int n, int m)
{
    return qCeil((double(n) / double(m)) * 100);
}



