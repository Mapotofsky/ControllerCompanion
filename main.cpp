#include "widget.h"
#include <QApplication>

/* In some cases, SDL will redefine the main() function,
   which may cause compilation problems.
   In order to fix this, you may need to use this ugly hack.
*/
#ifdef Q_OS_WIN
#   ifdef main
#      undef main
#   endif
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
