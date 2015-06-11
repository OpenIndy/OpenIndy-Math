#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(OI_MATH_LIB)
#  define OI_MATH_EXPORT Q_DECL_EXPORT
#else
#  define OI_MATH_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H
