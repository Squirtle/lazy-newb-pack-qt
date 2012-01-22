TEMPLATE = app
TARGET = LazyNewbPack
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXXFLAGS += -std=c++0x
include(../3rdparty/qtcreator/fancywidgets.pri)
include(Qtilities.pri)

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
    LocalGraphicsPack.h

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
    LocalGraphicsPack.cpp

FORMS += \
    ui/MainWindow.ui \
    ui/OptionsTab.ui \
    ui/SetupTab.ui \
    ui/InitEditorWidget.ui \
    ui/GraphicsTab.ui

RESOURCES += \
    ../fallback.qrc
