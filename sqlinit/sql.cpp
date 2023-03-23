#include "sql.h"
#include "ui_sql.h"
#include<QDebug>
#include<QPushButton>
#include<QPainter>
#include<QPaintEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QApplication>
#include<QPainter>
#include<QString>
int max(int a,int b)
{
    return a>b?a:b;

}
int min(int a,int b)
{
    return a<b?a:b;

}

sql::sql(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sql)
{
    ui->setupUi(this);
}
bool sql::isIntersect(int E1, int E2) //非端点处相交
{

   int x1,x2,x3,x4,y1,y2,y3,y4;
   x1=point[edge[E1][0]][0];
   x2=point[edge[E1][1]][0];
   x3=point[edge[E2][0]][0];
   x4=point[edge[E2][1]][0];
   y1=point[edge[E1][0]][1];
   y2=point[edge[E1][1]][1];
   y3=point[edge[E2][0]][1];
   y4=point[edge[E2][1]][1];


    if (max(x1, x2) < min(x3, x4) || max(x3, x4) < min(x1, x2) || max(y1, y2) < min(y3, y4) || max(y3, y4) < min(y1, y2))
    {
        return false;
    }
    return (((((x1 - x3) * (y4 - y3)) - ((x4 - x3) * (y1 - y3))) * (((x2 - x3) * (y4 - y3)) - ((x4 - x3) * (y2 - y3)))) < 0);
}
void sql::edgeInit(){
     QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码


    db.open();

    QSqlQuery query;
    query.exec("select start_id,end_id from edges ");
    int i=0;
    while (true == query.next()) {  //一行一行遍历

       edge[i][0]=query.value(0).toInt();
       edge[i][1]=query.value(1).toInt();
       i++;

     }
}
void sql::pointInit(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码


    db.open();

    QSqlQuery query;
    query.exec("select x,y from points where x<=900 and y<=900");
    int i=0;
    while (true == query.next()) {  //一行一行遍历

       point[i][0]=query.value(0).toInt();
       point[i][1]=query.value(1).toInt();
       i++;

     }
}
void sql::graphInit()
{

}
sql::~sql()
{
    delete ui;
}
