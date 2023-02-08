#ifndef DIALOG01_H
#define DIALOG01_H

#include <QDialog>

namespace Ui {
class Dialog01;
}

class Dialog01 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog01(QWidget *parent = nullptr);
    ~Dialog01();

private:
    Ui::Dialog01 *ui;
};

#endif // DIALOG01_H
