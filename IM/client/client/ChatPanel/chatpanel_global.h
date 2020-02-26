#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CHATPANEL_LIB)
#  define CHATPANEL_EXPORT Q_DECL_EXPORT
# else
#  define CHATPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define CHATPANEL_EXPORT
#endif
