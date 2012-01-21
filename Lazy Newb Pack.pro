TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += ./inc

QMAKE_CXXFLAGS += -std=c++0x
include(3rdparty/qtcreator/fancywidgets.pri)

# Input
HEADERS += inc/functions.hpp inc/lnplauncher.hpp inc/optionsframe.hpp inc/advancedframe.hpp inc/graphicsframe.hpp \
    inc/DwarfFortress.h \
    inc/DwarfFortressProcess.h \
    inc/MainWindow.h \
    inc/ConfigButton.h \
    inc/OptionsTab.h \
    inc/NumericOptionWidget.h \
    inc/InitEditorDialog.h \
    inc/KeybindsWidget.h \
    inc/IconLoader.h \
    inc/SetupTab.h
SOURCES += src/functions.cpp src/lnplauncher.cpp src/main.cpp src/optionsframe.cpp src/advancedframe.cpp src/graphicsframe.cpp \ 
    src/DwarfFortress.cpp \
    src/DwarfFortressProcess.cpp \
    src/MainWindow.cpp \
    src/ConfigButton.cpp \
    src/OptionsTab.cpp \
    src/NumericOptionWidget.cpp \
    src/InitEditorDialog.cpp \
    src/KeybindsWidget.cpp \
    src/IconLoader.cpp \
    src/SetupTab.cpp

FORMS += \
    ui/MainWindow.ui \
    ui/OptionsTab.ui \
    ui/SetupTab.ui

RESOURCES += \
    fallback.qrc
