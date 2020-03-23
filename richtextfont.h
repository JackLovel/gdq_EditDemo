#ifndef RICHTEXTFONT_H
#define RICHTEXTFONT_H

#include <QObject>
#include "color.h"

class RichTextFont
{
public:
    RichTextFont(QString _text = "", QString _color = WHITE);
    ~RichTextFont();

public:
    QString color;
    QString text;

    void toString();
    QString formatColor();
};

#endif // RICHTEXTFONT_H
