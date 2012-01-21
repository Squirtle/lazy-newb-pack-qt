#include "inc/ConfigSyntaxHighlighter.h"
#include <QDebug>

ConfigSyntaxHighlighter::ConfigSyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void ConfigSyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
    QString pattern = "^\\s*\\[.*\\]\\s*$";

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }
}
