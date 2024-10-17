#include "gamebox.h"
#include "QApplication"
using namespace s21;
using namespace std;
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Wrap game;
    return app.exec();
}
