#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMTITLEBARPANEL_LIB)
#  define IMTITLEBARPANEL_EXPORT Q_DECL_EXPORT
# else
#  define IMTITLEBARPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMTITLEBARPANEL_EXPORT
#endif
