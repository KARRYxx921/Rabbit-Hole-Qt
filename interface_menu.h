#ifndef INTERFACE_MENU_H
#define INTERFACE_MENU_H

#include <QDialog>
#include<QCheckBox>
#include<QLabel>
#include<QString>
#include<QStringList>


namespace Ui {
class Interface_menu;
}

class Interface_menu : public QDialog
{
    Q_OBJECT

public:
    explicit Interface_menu(QWidget *parent = 0, QString str = "",QString arr = "",int num =0 );
    ~Interface_menu();

private slots:
    void on_buttonBox_accepted();


private:
    Ui::Interface_menu *ui;

    //完整菜单（未切割）
    QString menuWhole;

    //上菜情况对应str
    QString menuArray;

    //桌号
    int table_number;

    QCheckBox *che_control[25];
    QLabel *lab_control[25];
    QStringList menuList;

signals:
    void iSignal(QString ,int);


};

#endif // INTERFACE_MENU_H
