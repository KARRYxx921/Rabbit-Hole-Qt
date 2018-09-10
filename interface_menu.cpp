#include "interface_menu.h"
#include "ui_interface_menu.h"
#include <QString>
#include <QCheckBox>
#include <QStringList>
#include <QLabel>
#include <QDebug>

Interface_menu::Interface_menu(QWidget *parent, QString str ,QString arr,int num) :
    QDialog(parent),
    menuWhole(str),
    menuArray(arr),
    table_number(num),
    ui(new Ui::Interface_menu)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(243,233,219)");

    //拆分
    menuList = menuWhole.split("#");
    for(int i = 0;i < (menuList.size()/2);i++)
    {
      QString name = menuList[i*2];
      QString money = menuList[i*2+1];

      //创建CheckBox
      if(menuArray.mid(i,1)=="0")
      {

      che_control[i] = new QCheckBox(this);
      che_control[i]->setText(name+"     "+money);
      che_control[i]->setGeometry(20,20+i*40,50,10);

      }

      //创建Label
      else if(menuArray.mid(i,1)=="1")
      {
      lab_control[i] = new QLabel(this);
      lab_control[i]->setText(name+"     "+money);
      lab_control[i]->setGeometry(20,20+i*40,50,10);

      }
    }
}

Interface_menu::~Interface_menu()
{
    delete ui;
}

void Interface_menu::on_buttonBox_accepted()
{
    //将checkbox转化（通过数组）
    for(int i=0; i<(menuList.size()/2); i++)
    {
        if(che_control[i]->isChecked())
        {
         menuArray.replace(i,1,"1");
        }
    }
    emit iSignal(menuArray, table_number);
}


