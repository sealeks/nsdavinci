
#include <kernel/serviceapp.h>



#if defined(_DVN_WIN_)
#include <kernel/serviceapp_win.cpp>
#elif defined(_DVN_LIN_)
#include <kernel/serviceapp_lin.cpp>
#else
#error No define service menager
#endif


