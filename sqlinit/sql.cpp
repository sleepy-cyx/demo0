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
#include<math.h>
#include<QQueue>
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
int sql:: distance(int a,int b){
    int x1,x2,y1,y2;
    x1=point[a][0];
    y1=point[a][1];
    x2=point[b][0];
    y2=point[b][1];
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void sql::graphtidy()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码


    db.open();
    QSqlQuery query1;
    query1.exec("select start_id,end_id from edges");
    while (true == query1.next()) {  //一行一行遍历



        QString sql = QString("update  edges set length= '%1' where start_id='%2' and end_id='%3'").arg(distance(query1.value(0).toInt(),query1.value(1).toInt())).arg(query1.value(0).toInt()).arg(query1.value(1).toInt());
              QSqlQuery query;
              query.exec(sql);
     }

    QVector<bool> is_deleted(2*capacity,false);
    QSqlQuery query;
    query.exec("select id from edges where length>300");
    while (true == query.next()) {  //一行一行遍历


      is_deleted[ query1.value(0).toInt()]=true;
      QString qstr=QString("delete from edges where id='%1'").arg(query1.value(0).toInt());
      QSqlQuery q;
      q.exec(qstr);

     }
    QVector<int> x;
    for(int i=0;i<2*capacity;i++)
    {
        for(int j=i+1;j<2*capacity;j++)
        {
            if(!is_deleted[i]&&isIntersect(i-1,j-1))
            {
                is_deleted[i]=true;


                x.push_back(i);
            }
        }
    }
    for(int i=0;i<x.size();i++)
   {    QString sql = QString("delete from edges where id = '%1'").arg(x[i]);
       QSqlQuery query;
       query.exec(sql);
    }

}
//bfs添加边
void sql::addedge()
{
    QQueue<int>res;
    QVector<int>edges;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码


    db.open();
    QVector<bool> isvisited(capacity,false);
    QSqlQuery query;
    query.exec("select * from edges ");
    while (true == query.next()) {  //一行一行遍历

      edges.push_back(query.value(0).toInt());
      res.push_back(query.value(1).toInt());
      isvisited[query.value(1).toInt()]=true;
      res.push_back(query.value(2).toInt());
      isvisited[query.value(2).toInt()]=true;
     }
    while(!res.empty())
    {   int now_index=res.front();
        res.pop_front();
        for(int i=0;i<capacity;i++)
        {

            if(distance(now_index,i)<30)
            {

            }
        }
    }
}
bool sql::ok_to_add(QVector<int>res,int start,int end)
{

}
sql::~sql()
{
    delete ui;
}
