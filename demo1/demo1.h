#ifndef DEMO1_H
#define DEMO1_H

const int capacity=3000;//点的数量

#include <QMainWindow>
#include<QVector>
namespace Ui {
class demo1;
}
struct node
{
    int id;
    int length;
    node* next;
};
struct edge
{
    int start_id;
    int end_id;
    int len;
};

class demo1 : public QMainWindow
{
    Q_OBJECT

public:
    int location[capacity][2];
    explicit demo1(QWidget *parent = nullptr);
    void PE(QPaintEvent* eve,int x,int y);
    void paintEvent(QPaintEvent*);

    QVector<int>shortest_path(QVector<node*> graph,int start,int end);
    ~demo1();

private:
    Ui::demo1 *ui;
};

#endif // DEMO1_H
