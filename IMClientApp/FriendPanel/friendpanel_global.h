#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FRIENDPANEL_LIB)
#  define FRIENDPANEL_EXPORT Q_DECL_EXPORT
# else
#  define FRIENDPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define FRIENDPANEL_EXPORT
#endif
