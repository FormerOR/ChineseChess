#ifndef MAINUI_H
#define MAINUI_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include "board.h"

#include "network.h"

class Cell;
class MainUI : public QDialog
{
    Q_OBJECT

    QVBoxLayout* layout;
    QGridLayout* boardLayout;
    QLabel *h[8 * 10], *v1[9 * 4], *v2[9 * 4], *l[8], *chu, *han;
    Cell* cells[9 * 10];
    QLineEdit* text;
    QLabel* message_area;
signals:
    void setup(Cell**);
    void onMes(QString);
public slots:
    void onFind(const QString opp_name) {
        emit setup(cells);
        this->opp_name=opp_name;
    }
    void setOppMes(const QString message){
        message_area->setText(opp_name+QString("说：")+message);
    }
    void sendMes(){
        emit onMes(text->text());
    }
    void sendAdmit(){
        emit onMes("我认输！");
    }
public:
    MainUI();
private:
    QString opp_name;
};

#endif // MAINUI_H
