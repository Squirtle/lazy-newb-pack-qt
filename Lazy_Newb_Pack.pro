TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = qtilities \
          src

qtilities.file = 3rdparty/qtilities/src/Qtilities.pro
src.depends = 3rdparty/qtilities/src
