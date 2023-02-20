#include "createSpline.h"

#include <QApplication>

#define DOT_AMOUNT          1000
#define LEFT_POINT_RANGE    1.0
#define RIGHT_POINT_RANGE   6.0

double func(double x) { return qLn(x); };

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CCreateSpline spline(func, LEFT_POINT_RANGE, RIGHT_POINT_RANGE, DOT_AMOUNT);

    return app.exec();
}
