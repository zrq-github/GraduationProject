
#include <QtCore/qglobal.h>
#ifndef BUILD_STATIC
# if defined(QDEBUGTOOL_LIB)
#  define QDEBUGTOOL_EXPORT Q_DECL_EXPORT
# else
#  define QDEBUGTOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define QDEBUGTOOL_EXPORT
#endif
