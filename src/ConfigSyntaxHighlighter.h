#ifndef CONFIGSYNTAXHIGHLIGHTER_H
#define CONFIGSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextDocument;

class ConfigSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit ConfigSyntaxHighlighter(QTextDocument *parent);

protected:
    virtual void highlightBlock(const QString &text);
};

#endif // CONFIGSYNTAXHIGHLIGHTER_H
