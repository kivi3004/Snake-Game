#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

static struct termios old, newa;

void initTermios(int echo)
{
    tcgetattr(0, &old);
    newa = old;
    newa.c_lflag &= ~ICANON;
    newa.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newa);
}

void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char _getch(void)
{
    return getch_(0);
}

bool _kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}
