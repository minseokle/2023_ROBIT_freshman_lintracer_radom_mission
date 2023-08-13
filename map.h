#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QFont>
#include <string>
#include <utility>

#define OB_NUM 10

class map
{
public:
    map();
    ~map();
    QGraphicsScene *getScene();
    std::string getMapArray();
    void viewShortRoot();
private:
    bool col_map[6][6];
    int dfs(bool map_[6][6]);
    QGraphicsScene *scene;

    std::pair<int,int> start_point,end_point;

};

#endif // MAP_H
