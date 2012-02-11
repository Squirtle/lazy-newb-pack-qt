#include "InitEditorWidget.h"
#include "ui_InitEditorWidget.h"

#include "DwarfFortress.h"
#include "ConfigSyntaxHighlighter.h"

#include <QAbstractButton>
#include <QFile>

InitEditorWidget::InitEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitEditorWidget)
{
    ui->setupUi(this);
    read_files();
    new ConfigSyntaxHighlighter(ui->initEdit->document());
    new ConfigSyntaxHighlighter(ui->dinitEdit->document());
}

InitEditorWidget::~InitEditorWidget()
{
    delete ui;
}

void InitEditorWidget::on_buttonBox_clicked(QAbstractButton *button)
{
   const QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole(button);
   if( role == QDialogButtonBox::ResetRole ) {
       //reset / reload
       read_files();
   } else if( role == QDialogButtonBox::AcceptRole ) {
       QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
       initfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
       initfile.write(ui->initEdit->toPlainText().toAscii());
       dinitfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
       dinitfile.write(ui->dinitEdit->toPlainText().toAscii());

       dinitfile.close();
       initfile.close();

   }
}


void InitEditorWidget::read_files()
{
   QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
   initfile.open(QFile::ReadOnly);
   dinitfile.open(QFile::ReadOnly);
   ui->initEdit->setPlainText(initfile.readAll());
   ui->dinitEdit->setPlainText(dinitfile.readAll());

   initfile.close();
   dinitfile.close();
}
