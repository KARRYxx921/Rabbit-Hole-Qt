#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QStringList>

class TableWidget
{
public:
    TableWidget();

    //添加一行并返回编号
    int addRow();

    //传编号获取桌号
    int getTable(int num);

    //传编号获取排队人数
    int getFront(int num);

    //接受桌号修改支付情况并返回下一个上桌编号
    int acceptPay(int table );

    //接受QString得到已点菜单
    void acceptFood(int table ,QString oederMenu);

    //获取某桌点餐情况
    QString getOrdered(int table);

    //获取原始菜单
    QString getList();

    //显示表格
    void show();

    //添加新菜品
    void addFood(QString food,QString price);

    //传桌号计算菜品总价
    int sumPrice(int table);
private:
    int desNum[10];
    QTableWidget *m_tableWidget = new QTableWidget(1,5);

    //菜品价格
    QStringList m_foodPrice;
    //菜单
    QStringList m_foodList;
};

#endif // TABLEWIDGET_H
