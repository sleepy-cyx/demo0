#ifndef SQL_H
#define SQL_H

#include <QMainWindow>

#include<QVector>
const int capacity=3000;
namespace Ui {
class sql;
}

class sql : public QMainWindow
{
    Q_OBJECT

public:
    int distance(int a,int b);
    int point[capacity][2];
    int edge[2*capacity][2];
    bool isIntersect(int E1, int E2);
    explicit sql(QWidget *parent = nullptr);

    void graphtidy();
    void edgeInit();
    void pointInit();
    void addedge();
    bool ok_to_add(QVector<int>res,int start,int end);
    ~sql();

private:
    Ui::sql *ui;
};

#endif // SQL_H
