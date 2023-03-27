#include "demo1.h"
#include "ui_demo1.h"
#include<QMenuBar>
#include<QToolBar>
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


demo1::demo1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::demo1)
{
    ui->setupUi(this);
    resize(900,900);
    QMenuBar* bar=menuBar();




    setMenuBar(bar);
    QMenu* menu=bar->addMenu("地图缩放");
    menu->addAction("放大");
    menu->addSeparator();
    menu->addAction("缩小");

}
//初始化有关点的变量

//最短路径-dijkstra
 QVector<int> demo1::shortest_path(QVector<node*> graph,int start,int end)
 {
     QVector<int>distance(capacity,6666);//记录当前每个点的最短路径
     QVector<QVector<int>>res(capacity,{start});//记录最短路径途径点
     //连通图保证函数一定跳出循环
     while(1){
         int min_index=-1;
         int min=99999;
         node* now_start=graph[start];//循环起点
     while(now_start->next)
     {
         int i=now_start->next->id;
         //取较小值，若存在数组更新，判定下一循环节点是否变化
         if(distance[i]<distance[now_start->next->id]+now_start->next->length)
         {
             distance[i]=distance[now_start->next->id]+now_start->next->length;
             res[i].push_back(now_start->next->id);
             if(min>distance[i])
             {
                 min=distance[i];
                 min_index=now_start->next->id;
             }
         }
         now_start=now_start->next;
     }
     if(distance[end]!=6666)
         return res[end];
     now_start=graph[min_index];
     }
 }
 //画图
void demo1::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);

    p.setPen(pen);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码


    db.open();
    QVector<QPoint>res;
    QSqlQuery query;
    query.exec("select x,y from points where x<=900 and y<=900");
    while (true == query.next()) {  //一行一行遍历

        res.push_back(QPoint(query.value(0).toInt(),query.value(1).toInt()));
        p.drawPoint(query.value(0).toInt(),query.value(1).toInt());

     }
    QSqlQuery query1;
    query1.exec("select start_id,end_id from edges");
    while (true == query1.next()) {  //一行一行遍历


        p.drawLine(res[query1.value(0).toInt()-1],res[query1.value(1).toInt()-1]);

     }
}

demo1::~demo1()
{
    delete ui;
}
