#include "richtextfont.h"
#include <QDebug>

RichTextFont::RichTextFont(QString _text, QString _color)
{
    text = _text;
    color = _color;
}

RichTextFont::~RichTextFont()
{

}

void RichTextFont::toString() {
  qDebug() << QString("text: %1, color: %2").arg(this->text)
              .arg(this->color);
}

QString RichTextFont::formatColor()
{
    return QString("<span style='background-color:\"%1\"'>%2</span>")
            .arg(this->color).arg(this->text);
}


