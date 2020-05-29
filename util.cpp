#include "util.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QtMath>
#include <QSettings>
#include <QClipboard>
#include <QMessageBox>
#include <QApplication>

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

// 写入配置文件
void Util::writeSetting(const QString &key, const QString &value)
{
    QString  settingFile = QDir::currentPath() + "/setting.ini";
    QSettings setting(settingFile, QSettings::IniFormat);
    const QString group = "RectFile";
    setting.beginGroup(group);
    setting.setValue(key, value);
    setting.endGroup();
}

// 读取配置文件
QMap<QString, QString> Util::readSetting()
{
    QMap<QString, QString> map;
    QString  settingFile = QDir::currentPath() + "/setting.ini";
    QSettings setting(settingFile, QSettings::IniFormat);
    const QString group = "RectFile";
    setting.beginGroup(group);
    for(int i = 0; i < setting.allKeys().length(); i++) {
        QString k = setting.allKeys().at(i);
        QString v = setting.value(k).toString();
        map[k] = v;
    }
    setting.endGroup();

    return map;
}

// 设置剪贴板的内容
void Util::setClipboardContent()
{
    QClipboard *b = QApplication::clipboard();
    b->setText("Text from Qt Application");
}

// 从剪贴板中读取内容
QString Util::getClipboardContent()
{
    QClipboard *b = QApplication::clipboard();
    return b->text();
}

QString Util::getSplitLast(QString path, QString separator)
{
    return path.split(separator).last();
}

QString Util::FileGbkToUtf8(QString path)
{
    QString content = "";
    QTextCodec *code = QTextCodec::codecForName("GB2312");  // "GB2312" 编码读取
    if (!path.isEmpty()) {
        QFile *file = new QFile();
        file->setFileName(path);
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

        QFile fw(path);
        fw.open(QIODevice::WriteOnly | QIODevice::Text);
        fw.write(content.toUtf8());
        fw.close();
    }

    return content;
}

// bug
QString Util::FileUtf8ToGbk(QString path)
{
    QString content = "";
    QTextCodec *gbk = QTextCodec::codecForName("GB2312");
    QTextCodec *code = QTextCodec::codecForName("UTF-8");  // "GB2312" 编码读取
    if (!path.isEmpty()) {
        QFile *file = new QFile();
        file->setFileName(path);
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

        QFile fw(path);
        fw.open(QIODevice::WriteOnly | QIODevice::Text);
        const char* str = gbk->toUnicode(content.toLocal8Bit()).toLatin1();
        fw.write(str);
        fw.close();
    }

    return content;
}

//https://www.cnblogs.com/kinglxg/p/12845974.html
QString Util::GbkToUtf8(const char* szGBK)
{
    if (szGBK == nullptr) {
        return "";
    }

    QString content = "";
    QTextCodec* pGBKCodec = QTextCodec::codecForName("GB2312");

    return pGBKCodec->toUnicode(szGBK);
}

// 如果目录不存在，我们就创建它
void Util::checkDirExist(const QString &path) {
    QDir dir;
    QFileInfo info(path);
    if (!info.exists()) {
        dir.mkpath(path);
    }
}
