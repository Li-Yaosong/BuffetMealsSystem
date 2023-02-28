#ifndef LIBBMS_GLOBAL_H
#define LIBBMS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBBMS_LIBRARY)
#  define LIBBMS_EXPORT Q_DECL_EXPORT
#else
#  define LIBBMS_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBBMS_GLOBAL_H
