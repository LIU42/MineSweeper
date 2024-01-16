#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    window.init();
    window.show();

    return application.exec();
}
