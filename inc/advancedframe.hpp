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

private slots:
    void sound_pressed();
    void volume_modified();
    void volume_finished();
    void dataChanged();

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

private slots:
    void counter_pressed();
    void cFPScap_modified();
    void gFPScap_modified();
    void cFPScap_finished();
    void gFPScap_finished();
    void dataChanged();

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

private slots:
    void intro_pressed();
    void windowed_pressed();
    void dataChanged();

private:
    QPushButton *intro, *windowed;
    QVBoxLayout *box;

};

class SaveFrame : public QGroupBox
{
    Q_OBJECT

public:
    SaveFrame();

private slots:
    void autosave_pressed();
    void autopause_pressed();
    void initsave_pressed();
    void pauseonload_pressed();
    void compress_pressed();
    void autobackup_pressed();
    void dataChanged();

private:
    QPushButton *autosave, *autopause, *initsave, *pauseonload, *compress, *autobackup;
    QGridLayout *grid;

};

class AdvancedFrame : public QFrame
{
    Q_OBJECT

public:
    AdvancedFrame();

private slots:
    void procpriority_pressed();
    void dataChanged();

private:
    QPushButton *procpriority;
    SoundFrame *soundframe;
    FPSFrame *fpsframe;
    StartupFrame *startupframe;
    SaveFrame *saveframe;
    QGridLayout *grid;

};
#endif //ADVANCEDFRAME_HPP
