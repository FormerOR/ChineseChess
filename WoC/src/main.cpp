#include "loginui.h"
#include "commonhelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载QSS样式
    CommonHelper::setStyle("style.qss");
    //设置字体
    CommonHelper::onLoadFont();

    auto w = new LoginUI;
    w->show();
    return a.exec();
}
