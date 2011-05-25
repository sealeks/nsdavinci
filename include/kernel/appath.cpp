
#include <kernel/constdef.h>

#if defined(_DVN_WIN_)
#include <kernel/appath_win.cpp>
#elif defined(_DVN_LIN_)
#include <kernel/appath_lin.cpp>
#else
#error No define path manager
#endif




