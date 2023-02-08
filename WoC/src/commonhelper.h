#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QFile>
#include <QApplication>
#include "QFontDatabase"

class CommonHelper
{
public:
    //风格设置
    static void setStyle(const QString &style) {
        QFile qss(QString(":")+style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    //字体设置
    static void onLoadFont()
    {
        int font_Id = QFontDatabase::addApplicationFont(":/SmileySans.ttf");
        QStringList font_list = QFontDatabase::applicationFontFamilies(font_Id);
//        qDebug()<<font_Id;
//        qDebug()<<font_list;
        if(!font_list.isEmpty())
        {
            QFont f;
            f.setFamily(font_list[0]);
            qApp->setFont(f);
        }

    }

};

#endif // COMMONHELPER_H
