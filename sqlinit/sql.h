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

    int point[capacity][2];
    int edge[capacity][2];
    bool isIntersect(int E1, int E2);
    explicit sql(QWidget *parent = nullptr);

    void graphInit();
    void edgeInit();
    void pointInit();
    ~sql();

private:
    Ui::sql *ui;
};

#endif // SQL_H
