TEMPLATE = app
TARGET = LazyNewbPack
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXXFLAGS += -std=c++0x
include(../3rdparty/qtcreator/fancywidgets.pri)

QT += testlib
QTILITIES = core logging coregui
include(Qtilities.pri)

LIBS += -lyaml-cpp
INCLUDEPATH += /usr/include/yaml-cpp

# Input
HEADERS += functions.h lnplauncher.h optionsframe.h advancedframe.h graphicsframe.h \
    DwarfFortress.h \
    DwarfFortressProcess.h \
    MainWindow.h \
    ConfigButton.h \
    OptionsTab.h \
    NumericOptionWidget.h \
    KeybindsWidget.h \
    IconLoader.h \
    SetupTab.h \
    ConfigSyntaxHighlighter.h \
    InitEditorWidget.h \
    GraphicsTab.h \
    IGraphicsPack.h \
    IGameDataProvider.h \
    IGraphicsProvider.h \
    LocalGameDataProvider.h \
    LocalGraphicsProvider.h \
    LocalGraphicsPack.h \
    IInitsProvider.h \
    LocalInitsProvider.h \
    IGameData.h \
    IInitsBundle.h \
    LocalGameData.h \
    InitsBundle.h \
    DFDataManager.h

SOURCES += functions.cpp lnplauncher.cpp main.cpp optionsframe.cpp advancedframe.cpp graphicsframe.cpp \
    DwarfFortress.cpp \
    DwarfFortressProcess.cpp \
    MainWindow.cpp \
    ConfigButton.cpp \
    OptionsTab.cpp \
    NumericOptionWidget.cpp \
    KeybindsWidget.cpp \
    IconLoader.cpp \
    SetupTab.cpp \
    ConfigSyntaxHighlighter.cpp \
    InitEditorWidget.cpp \
    GraphicsTab.cpp \
    IGraphicsPack.cpp \
    IGameDataProvider.cpp \
    IGraphicsProvider.cpp \
    LocalGameDataProvider.cpp \
    LocalGraphicsProvider.cpp \
    LocalGraphicsPack.cpp \
    IInitsProvider.cpp \
    LocalInitsProvider.cpp \
    IGameData.cpp \
    IInitsBundle.cpp \
    LocalGameData.cpp \
    InitsBundle.cpp \
    DFDataManager.cpp

FORMS += \
    ui/MainWindow.ui \
    ui/OptionsTab.ui \
    ui/SetupTab.ui \
    ui/InitEditorWidget.ui \
    ui/GraphicsTab.ui

RESOURCES += \
    ../fallback.qrc
