#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QIcon>

namespace {
    int _sizes[6] = {16, 22, 32, 48, 64, 128};
}

namespace IconLoader {
    QIcon load(const QString &name);
}
#endif
