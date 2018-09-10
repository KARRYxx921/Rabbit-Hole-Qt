#include "tablewidget.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include <QString>

TableWidget::TableWidget()
{
    m_tableWidget -> setWindowTitle("就餐信息");
    QStringList headers;
    headers <<"编号" <<"桌号"<<"菜单"<<"支付状态"<<"支付金额";
    m_tableWidget ->setHorizontalHeaderLabels(headers);
    m_foodList<<"aaa"<<"bbb"<<"ccc";
    m_foodPrice<<"1"<<"2"<<"3";

    //设置每行内容不可编辑
    m_tableWidget ->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置只能选择一行，不能选择多行
    m_tableWidget ->setSelectionMode(QAbstractItemView::SingleSelection);

    //去掉每行行号
    QHeaderView *headerView = m_tableWidget->verticalHeader();
    headerView->setHidden(true);

    //指定行列大小
    m_tableWidget->setColumnWidth(3,200);
    m_tableWidget->setRowHeight(3,60);

    //设置表头字体加粗
    QFont font = m_tableWidget ->horizontalHeader()->font();
    font.setBold(true);
    m_tableWidget->horizontalHeader()->setFont(font);

    //设置表头高度
    m_tableWidget->horizontalHeader()->setFixedHeight(25);

}

//添加一行并返回编号
int TableWidget::addRow()
{
    int rowIndex = m_tableWidget -> rowCount();
    m_tableWidget -> setRowCount(rowIndex + 1);
    QString str = QString::number(rowIndex);
    QTableWidgetItem *item = new QTableWidgetItem(str);
    m_tableWidget ->setItem(m_tableWidget -> rowCount(),0,item);
    return (rowIndex);
}

//传编号获取桌号
int TableWidget::getTable(int num)
{
    int i = 1;
    for(;i<10;i++)
    {
        if(desNum[i] == 0 )
        {
            continue;
        }
        else
        {
            desNum[i] = num;
            break;
        }
    }
    if(i==10)
    {
        return 0;
    }
    else
    {
        return i;
    }
}

//传标号获取排队人数
int TableWidget::getFront(int num)
{
    int max = desNum[0];
    for(int i = 0;i<10;i++)
    {
        if( max <= desNum[i] )
        {
            max = desNum[i];
        }
    }
    int front = num - max;
    return front;
}

//接受桌号修改支付情况并返回下一个上桌编号
int TableWidget::acceptPay(int table)
{
    QTableWidgetItem *newItem = new QTableWidgetItem("1");
    int row = desNum[table];
    m_tableWidget -> setItem(row,3,newItem);
    return (desNum[table] +1);
}

//接受数字QString得到已点菜单
void TableWidget::acceptFood(int table, QString orderMenu)
{
    QString list = "";

    QStringList strList = orderMenu.split("#");
    for(int i = 0; i<strList.size();i++)
    {
        if(strList[i] == "1")
        {
            list += m_foodList[i];
            list += "#";
        }
    }

    QTableWidgetItem *item = new QTableWidgetItem(list);

    m_tableWidget -> setItem(desNum[table],2,item);
}

//获取某桌点餐情况
QString TableWidget::getOrdered(int table)
{
    int num = desNum[table];
    QString list = m_tableWidget->item(num,2)->text();
    return list;
}

//获取原始菜单
QString TableWidget::getList()
{
    QString list;
    for(int i = 0;i <m_foodList.size();i++)
    {
        list += m_foodList[i];
        list += "#";
        list += m_foodPrice[i];
        list += "#";
    }
    return list;
}

//显示表格
void TableWidget::show()
{
    m_tableWidget ->show();
}

//添加新菜品
void TableWidget::addFood(QString food, QString price)
{
    m_foodList<<food;
    m_foodPrice<<price;
}

//传桌号计算菜品总价
int TableWidget::sumPrice(int table)
{
    int sums = 0;
    int num = desNum[table];
    QString list = m_tableWidget -> item(num,2) -> text();

    QStringList strList = list.split("#");

    for(int i = 0;i < strList.size();i++ )
    {
        if(strList[i] == 1)
        {
           QString sum =  m_foodPrice[i];
            sums+=sum.toInt();
        }
    }
    return sums;
}










