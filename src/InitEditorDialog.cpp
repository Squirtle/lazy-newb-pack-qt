#include "inc/InitEditorDialog.h"

#include "DwarfFortress.h"
#include "ConfigSyntaxHighlighter.h"

#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>
#include <QFile>

InitEditorDialog::InitEditorDialog(QWidget *parent) :
    QWidget(parent)
{
    save = new QPushButton(tr("Save"));
    load = new QPushButton(tr("Load"));
    grid = new QGridLayout(this);
    init = new QTextEdit(this);
    dinit = new QTextEdit(this);
    QSplitter *splitter = new QSplitter(this);

    QFile initfile(DwarfFortress::instance().getInitPath());
    QFile dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::ReadOnly);
    QString *inittext = new QString(initfile.readAll());
    initfile.close();
    dinitfile.open(QFile::ReadOnly);
    QString *dinittext = new QString(dinitfile.readAll());
    dinitfile.close();
    init->setPlainText(*inittext);
    dinit->setPlainText(*dinittext);

    new ConfigSyntaxHighlighter(init->document());
    new ConfigSyntaxHighlighter(dinit->document());

    connect(save, SIGNAL(pressed()), this, SLOT(save_pressed()));
    connect(load, SIGNAL(pressed()), this, SLOT(load_pressed()));

    splitter->addWidget(init);
    splitter->addWidget(dinit);
    grid->addWidget(splitter, 0, 0, 1, 5);
    grid->addWidget(load, 1, 3, 1, 1);
    grid->addWidget(save, 1, 4, 1, 1);

    setLayout(grid);
}


void InitEditorDialog::load_pressed()
{
    QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::ReadOnly);
    QString *inittext = new QString(initfile.readAll());
    initfile.close();
    dinitfile.open(QFile::ReadOnly);
    QString *dinittext = new QString(dinitfile.readAll());
    dinitfile.close();
    init->setPlainText(*inittext);
    dinit->setPlainText(*dinittext);
}

void InitEditorDialog::save_pressed()
{
    QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *inittext = new QString(init->toPlainText());
    initfile.write(inittext->toAscii());
    initfile.close();
    dinitfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *dinittext = new QString(dinit->toPlainText());
    dinitfile.write(dinittext->toAscii());
    dinitfile.close();
}
