
#include <QtCore/qglobal.h>
#ifndef BUILD_STATIC
# if defined(QTTOOL_LIB)
#  define QTTOOL_EXPORT Q_DECL_EXPORT
# else
#  define QTTOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTTOOL_EXPORT
#endif
