#ifdef __linux__
#include <termios.h>
#include <stdio.h>
#define GETCH \
static struct termios old, _new;\
int nRet = -1;\
tcgetattr(0, &old);\
_new = old;\
_new.c_lflag &= ~ICANON;\
_new.c_lflag &= ~ECHO;\
tcsetattr(0, TCSANOW, &_new);\
nRet = (int) getchar();\
tcsetattr(0, TCSANOW, &old);\
return nRet;
#endif

#ifdef _WIN32
#include <conio.h>
#define GETCH \
return _getch();
#endif

char my_getch()
{
  GETCH
}
