#ifndef ARTICLE_H
#define ARTICLE_H

#include <QApplication>
#include <QObject>

#include "util.h"
#include "Config.h"

class Article
{
public:
    Article(QString _name, int _type);

    QString content;
    QString name;
    QString path;
    int type; // my/local
    int wordSize;
    QString fileSize;

    QString getPath();
    QString getFileSize();
};

#endif // ARTICLE_H
