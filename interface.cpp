#include "interface.h"
#include "ui_interface.h"
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<interface_menu.h>
#include<QString>
#include<QLabel>
#include<QStringList>
#include<QtCore>
#include<QMouseEvent>

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);


    //界面动画（渐变）
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();


    //显示时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(timeShow()));
    timer->start(1000);

    //设置默认颜色、默认状态（灰色）
    ui->table1->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table1->setEnabled(false);
    ui->table2->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table2->setEnabled(false);
    ui->table3->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table3->setEnabled(false);
    ui->table4->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table4->setEnabled(false);
    ui->table5->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table5->setEnabled(false);
    ui->table6->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table6->setEnabled(false);
    ui->table7->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table7->setEnabled(false);
    ui->table8->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table8->setEnabled(false);
    ui->table9->setStyleSheet("background-color:rgb(208,213,211)");
    ui->table9->setEnabled(false);


    //创建服务器
    m_port = 8888;
    m_server = new Server(this, m_port);

    //与服务器连接各类信息
    //新顾客上桌
    connect(m_server,&Server::newclientontable,this,&Interface::clientontable);
    connect(m_server,&Server::ordermenu,this,&Interface::orderSlot);
    connect(m_server,&Server::callserver,this,&Interface::serverSlot);
    connect(m_server,&Server::clientleave,this,&Interface::slotclientleave);

    //上菜情况对应str
    me1.fill('0', 25);
    me2.fill('0', 25);
    me3.fill('0', 25);
    me4.fill('0', 25);
    me5.fill('0', 25);
    me6.fill('0', 25);
    me7.fill('0', 25);
    me8.fill('0', 25);
    me9.fill('0', 25);

}

Interface::~Interface()
{
    delete ui;
}

void Interface::timeShow()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->timelabel->setText(str);
}

//新顾客上桌（暗蓝色）
void Interface::clientontable(int num, int table)
{
   int choose = table;
   switch(choose)
   {
   case 1:ui->table1->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table1->setEnabled(true);
          break;
   case 2:ui->table2->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table2->setEnabled(true);
          break;
   case 3:ui->table3->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table3->setEnabled(true);
          break;
   case 4:ui->table4->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table4->setEnabled(true);
          break;
   case 5:ui->table5->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table5->setEnabled(true);
          break;
   case 6:ui->table6->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table6->setEnabled(true);
          break;
   case 7:ui->table7->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table7->setEnabled(true);
          break;
   case 8:ui->table8->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table8->setEnabled(true);
          break;
   case 9:ui->table9->setStyleSheet("background-color:rgb(131,176,174)");
          ui->table9->setEnabled(true);
          break;
   default: qDebug()<<"wrong!";
          break;

   }


}

//是否需要服务（粉色）
void Interface::serverSlot(int table)
{
    int choose=table;
    switch(choose)
    {
    case 1:ui->table1->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 2:ui->table2->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 3:ui->table3->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 4:ui->table4->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 5:ui->table5->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 6:ui->table6->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 7:ui->table7->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 8:ui->table8->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    case 9:ui->table9->setStyleSheet("background-color:rgb(227,113,113)");
           break;
    default: qDebug()<<"serverSlot is wrong!";
           break;
    }
}


//点菜情况
void Interface::orderSlot(int table, QString menuorder)
{
    int choose=table;
    switch(choose)
    {
    
   //放入对应str
    case 1:m_menu1 = menuorder;
           break;
    case 2:m_menu2 = menuorder;
           break;
    case 3:m_menu3 = menuorder;
           break;
    case 4:m_menu4 = menuorder;
           break;
    case 5:m_menu5 = menuorder;
           break;
    case 6:m_menu6 = menuorder;
           break;
    case 7:m_menu7 = menuorder;
           break;
    case 8:m_menu8 = menuorder;
           break;
    case 9:m_menu9 = menuorder;
           break;
    default: qDebug()<<"orderSlot is wrong!";
             break;

    }
}

//顾客离开
void Interface::slotclientleave(int table)
{
    int choose=table;
    switch(choose)
    {
    case 1:ui->table1->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table1->setEnabled(false);
           break;
    case 2:ui->table2->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table2->setEnabled(false);
           break;
    case 3:ui->table3->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table3->setEnabled(false);
           break;
    case 4:ui->table4->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table4->setEnabled(false);
           break;
    case 5:ui->table5->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table5->setEnabled(false);
           break;
    case 6:ui->table6->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table6->setEnabled(false);
           break;
    case 7:ui->table7->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table7->setEnabled(false);
           break;
    case 8:ui->table8->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table8->setEnabled(false);
           break;
    case 9:ui->table9->setStyleSheet("background-color:rgb(208,213,211)");
           ui->table9->setEnabled(false);
           break;
    default: qDebug()<<"slotclientleave is wrong!";
             break;
    }
}



//餐桌1
void Interface::on_table1_clicked()
{   
    //判断颜色，若为服务色则表示已服务变回顾客色，否则跳出菜单
    QString color1=ui->table1->styleSheet();
    if(color1=="background-color:rgb(227,113,113)")
    {
        ui->table1->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color1=="background-color:rgb(131,176,174)")
    {
        //构建菜单
        Interface_menu *menu1= new Interface_menu(0,m_menu1,me1,1);
        connect(menu1,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString ,int)));
        menu1->show();
    }
}

//餐桌2
void Interface::on_table2_clicked()
{
    QString color2=ui->table2->styleSheet();
    if(color2=="background-color:rgb(227,113,113)")
    {
        ui->table2->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color2=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu2= new Interface_menu(0,m_menu2,me2,2);
        connect(menu2,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu2->show();
    }
}

//餐桌3
void Interface::on_table3_clicked()
{
    QString color3=ui->table3->styleSheet();
    if(color3=="background-color:rgb(227,113,113)")
    {
        ui->table3->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color3=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu3= new Interface_menu(0,m_menu3,me3,3);
        connect(menu3,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu3->show();
    }
}

//餐桌4
void Interface::on_table4_clicked()
{
    QString color4=ui->table1->styleSheet();
    if(color4=="background-color:rgb(227,113,113)")
    {
        ui->table4->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color4=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu4= new Interface_menu(0,m_menu4,me4,4);
        connect(menu4,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu4->show();
    }
}

//餐桌5
void Interface::on_table5_clicked()
{
    QString color5=ui->table5->styleSheet();
    if(color5=="background-color:rgb(227,113,113)")
    {
        ui->table5->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color5=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu5= new Interface_menu(0,m_menu5,me5,5);
        connect(menu5,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu5->show();
    }
}

//餐桌6
void Interface::on_table6_clicked()
{
    QString color6=ui->table6->styleSheet();
    if(color6=="background-color:rgb(227,113,113)")
    {
        ui->table6->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color6=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu6= new Interface_menu(0,m_menu6,me6,6);
        connect(menu6,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu6->show();
    }
}

//餐桌7
void Interface::on_table7_clicked()
{
    QString color7=ui->table7->styleSheet();
    if(color7=="background-color:rgb(227,113,113)")
    {
        ui->table7->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color7=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu7= new Interface_menu(0,m_menu7,me7,7);
        connect(menu7,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu7->show();
    }
}

//餐桌8
void Interface::on_table8_clicked()
{
    QString color8=ui->table8->styleSheet();
    if(color8=="background-color:rgb(227,113,113)")
    {
        ui->table8->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color8=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu8= new Interface_menu(0,m_menu8,me8,8);
        connect(menu8,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu8->show();
    }
}

//餐桌9
void Interface::on_table9_clicked()
{
    QString color9=ui->table9->styleSheet();
    if(color9=="background-color:rgb(227,113,113)")
    {
        ui->table9->setStyleSheet("background-color:rgb(131,176,174)");
    }
    else if(color9=="background-color:rgb(131,176,174)")
    {
        Interface_menu *menu9= new Interface_menu(0,m_menu9,me9,9);
        connect(menu9,SIGNAL(iSignal(QString ,int)),SLOT(iSlot(QString,int)));
        menu9->show();
    }
}

//槽函数
void Interface::iSlot(QString array, int table)
{
    int choose=table;
    switch(choose)
    {
    case 1:me1=array;
           break;
    case 2:me2=array;
           break;
    case 3:me3=array;
           break;
    case 4:me4=array;
           break;
    case 5:me5=array;
           break;
    case 6:me6=array;
           break;
    case 7:me7=array;
           break;
    case 8:me8=array;
           break;
    case 9:me9=array;
           break;
    default: qDebug()<<"Solt is wrong!";
             break;
    }
}


//双击
void Interface::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
#if 0
        if (this->isMaximized())
        {
            this->showNormal();
        }
        else
        {
            this->showMaximized();
        }
#endif
        if (this->windowState() == Qt::WindowMaximized)
        {
            this->showNormal();
        }
        else if (this->windowState() == Qt::WindowNoState)
        {
            this->showMaximized();
        }
        else{}
    }
}

//移动
void Interface::mouseMoveEvent(QMouseEvent *event)
{


    QPoint endPoint = event->globalPos();
    QPoint endPos = endPoint - m_offset;
    this->move(endPos);
}

//点击拖动
void Interface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QCursor cursor(Qt::ClosedHandCursor);
        //    this->setCursor(cursor);
        QApplication::setOverrideCursor(cursor);



        QPoint startPoint = event->globalPos();
        QPoint startPos = this->pos();
        m_offset = startPoint - startPos;

    }
    else if (event->button() == Qt::RightButton)
    {
        QPixmap pix(":/imgs/imges/3.PNG");
        QCursor cursor(pix);
        QApplication::setOverrideCursor(cursor);
    }
    else{}

}

//放开
void Interface::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
}



//添加菜单
void Interface::on_action1_triggered()
{

}

//修改菜单
void Interface::on_action2_triggered()
{

}
