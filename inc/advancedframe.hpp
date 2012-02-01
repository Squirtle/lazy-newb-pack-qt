/* advancedframe.hpp
 * This is the header file which contains the code for the "Advanced" tab.
 */
#ifndef ADVANCEDFRAME_HPP
#define ADVANCEDFRAME_HPP
#include <QtGui>

class SoundFrame : public QGroupBox
{
    Q_OBJECT

public:
    SoundFrame();
    void reload();

private slots:
    void sound_pressed();
    void volume_modified();
    void volume_finished();

private:
    QPushButton *sound;
    QLineEdit *volume;
    QLabel *maxvolume;
    QHBoxLayout *box;

};

class FPSFrame : public QGroupBox
{
    Q_OBJECT

public:
    FPSFrame();
    void reload();

private slots:
    void counter_pressed();
    void cFPScap_modified();
    void gFPScap_modified();
    void cFPScap_finished();
    void gFPScap_finished();

private:
    QPushButton *counter;
    QLineEdit *cFPScap, *gFPScap;
    QLabel *cFPSlabel, *gFPSlabel;
    QVBoxLayout *box;

};

class StartupFrame : public QGroupBox
{
    Q_OBJECT

public:
    StartupFrame();
    void reload();

private slots:
    void intro_pressed();
    void windowed_pressed();

private:
    QPushButton *intro, *windowed;
    QVBoxLayout *box;

};

class SaveFrame : public QGroupBox
{
    Q_OBJECT

public:
    SaveFrame();
    void reload();

private slots:
    void autosave_pressed();
    void autopause_pressed();
    void initsave_pressed();
    void pauseonload_pressed();
    void compress_pressed();
    void autobackup_pressed();

private:
    QPushButton *autosave, *autopause, *initsave, *pauseonload, *compress, *autobackup;
    QGridLayout *grid;

};

class AdvancedFrame : public QFrame
{
    Q_OBJECT

public:
    AdvancedFrame();
    void reload();

private slots:
    void procpriority_pressed();

private:
    QPushButton *procpriority;
    SoundFrame *soundframe;
    FPSFrame *fpsframe;
    StartupFrame *startupframe;
    SaveFrame *saveframe;
    QGridLayout *grid;

};
#endif //ADVANCEDFRAME_HPP
