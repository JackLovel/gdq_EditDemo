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



