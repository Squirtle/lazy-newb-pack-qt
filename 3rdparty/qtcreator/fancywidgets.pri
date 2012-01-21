
SOURCES += $$PWD/fancywidgets/styleanimator.cpp \
    $$PWD/fancywidgets/minisplitter.cpp \
    $$PWD/fancywidgets/manhattanstyle.cpp \
    $$PWD/fancywidgets/fancytabwidget.cpp \
    $$PWD/fancywidgets/fancyactionbar.cpp \
    $$PWD/utils/stylehelper.cpp \
    $$PWD/utils/styledbar.cpp \
    $$PWD/utils/fancymainwindow.cpp \
    $$PWD/utils/filterlineedit.cpp \
    $$PWD/utils/fancylineedit.cpp


HEADERS += $$PWD/fancywidgets/styleanimator.h \
    $$PWD/fancywidgets/manhattanstyle.h \
    $$PWD/fancywidgets/fancytabwidget.h \
    $$PWD/fancywidgets/fancyactionbar.h \
    $$PWD/fancywidgets/minisplitter.h \
    $$PWD/fancywidgets/coreconstants.h \
    $$PWD/utils/stylehelper.h \
    $$PWD/utils/styledbar.h \
    $$PWD/utils/fancymainwindow.h \
    $$PWD/utils/qtcassert.h \
    $$PWD/utils/filterlineedit.h \
    $$PWD/utils/fancylineedit.h

INCLUDEPATH += $$PWD/fancywidgets/ \
                $$PWD/utils/
DEPENDPATH += $$PWD/fancyactionbar/ \
                $$PWD/utils/

RESOURCES += $$PWD/fancywidgets/core.qrc
