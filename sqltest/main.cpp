#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QApplication>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  //连接的MYSQL的数据库驱动
    db.setHostName("127.0.0.1");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("sql1");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("20030829mayayo");//密码
    qDebug()<<QSqlDatabase::drivers();

    db.open();
    qDebug()<<db.open();

    QSqlQuery query;
    query.exec("select * from points");
    while (true == query.next()) {  //一行一行遍历
         //取出当前行的内容，以列为单位
         qDebug()  //取第一列
                  << query.value(1).toString() //取第二列
                   //按名字查找
                  ;
     }

    return a.exec();
}
