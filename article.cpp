#include "article.h"

Article::Article(QString _name, int _type)
{
    this->type = _type;
    this->name = _name;
    this->path = getPath();
    this->content = Util::readFile(this->path);
    this->wordSize = this->content.length();
    this->fileSize = getFileSize();
}

QString Article::getPath()
{
    QString prefix = "";
    if (this->type == 0) {
        prefix = qApp->applicationDirPath() + "/" + ARTICLE_DIR_FILE;
    } else if (this->type == 1) {
        prefix = ":/local_article";
    }
    this->path = prefix + "/" + this->name;
    return this->path;
}

QString Article::getFileSize()
{
    QFileInfo info(this->path);
    double size = info.size();
    QString unit = "b";
    QString result;
    QString format;

    if (size > 1024) {
        unit = "k";
        size = size / 1024;
    }

    if (size > 1024) {
        unit = "m";
        size = size / 1024;
    }

    if (size > 1024) {
        unit = "g";
        size = size / 1024;
    }

    // 保留两位小数
    format = QString::number(size, 'f', 2);
    result = QString("%1%2").arg(format).arg(unit);

    return result;
}




