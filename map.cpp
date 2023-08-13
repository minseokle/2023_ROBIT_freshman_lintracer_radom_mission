#include "map.h"
#include <random>
#include <queue>
#include <QDebug>
map::map():start_point(std::make_pair(5,4)),end_point(std::make_pair(0,0))
{    // 시드값을 얻기 위한 random_device 생성.
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    //0~7(좌표 범위)까지 나오는 랜덤 정의
    std::uniform_int_distribution<int> pos_ran(0, 5);

    while(1){
        for(int i=0;i<OB_NUM;i++){
            while(1){
                int x,y;
                x=pos_ran(gen);
                y=pos_ran(gen);
                if(!col_map[x][y]&&(!(x==start_point.first&&y==start_point.second)&&!(x==start_point.first&&y==start_point.second))){
                    col_map[x][y]=true;
                    break;
                }
            }
        }
        if(dfs(col_map)>12){
            break;
        }else{
            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    col_map[i][j]=false;
                }
            }
        }
    }



    scene=new QGraphicsScene;

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(10);
    for(int i=0;i<6;i++)
    {
        scene->addLine(100,100+i*700/5,800,100+i*700/5,pen);
        scene->addLine(100+i*700/5,100,100+i*700/5,800,pen);
    }
    pen.setColor(Qt::red);
    pen.setWidth(30);
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(col_map[i][j]){
                int x=(100+i*700/5);
                int y=(100+j*700/5);
                scene->addLine(x-40,y-40,x+40,y+40,pen);
                scene->addLine(x+40,y-40,x-40,y+40,pen);
            }
        }
    }
    QFont font;
    font.setPixelSize(60);
    font.setBold(true);



    QGraphicsTextItem *text = scene->addText("");
    text->setHtml("<div style='background-color:#42ecab;'>START</div>");
    text->setFont(font);
    int start_x=100+start_point.first*700/5-90
        ,start_y=100+start_point.second*700/5-45;

    text->setPos(start_x,start_y);




    text = scene->addText("");
    text->setHtml("<div style='background-color:#42ecab;'>END</div>");
    start_x=100+end_point.first*700/5-54;
    start_y=100+end_point.second*700/5-45;
    text->setPos(start_x,start_y);
    text->setFont(font);
}
map::~map(){
    delete scene;
}

int map::dfs(bool map_[6][6]){
    std::queue<std::pair<int,int>> visited_node;
    visited_node.push(start_point);
    int dx[4]={1,0,-1,0};
    int dy[4]={0,1,0,-1};
    int value_map[6][6]={0,};
    while (!visited_node.empty()) {
        int x=visited_node.front().first,y=visited_node.front().second;
        for(int i=0;i<4;i++){
            int px=x+dx[i];
            int py=y+dy[i];


            if(px<0||px>5||py<0||py>5||(px==start_point.first&&py==start_point.second)){
                continue;
            }


            if(value_map[px][py]==0&&!map_[px][py]){
                value_map[px][py]=value_map[x][y]+1;
                visited_node.push(std::make_pair(px,py));
            }
        }
        visited_node.pop();
    }
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(col_map[i][j]){
                value_map[i][j]=-1;
            }
        }
    }
    //    for(int i=0;i<6;i++){
    //        qDebug()<<value_map[0][i]<<"\t"<<value_map[1][i]<<"\t"<<value_map[2][i]<<"\t"<<value_map[3][i]<<"\t"<<value_map[4][i]<<"\t"<<value_map[5][i];
    //    }
    //    qDebug()<<' ';
    return value_map[end_point.first][end_point.second];
}
QGraphicsScene * map::getScene(){
    return this->scene;
}
std::string map::getMapArray(){
    std::string res;
    res="{{";
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            res+=std::to_string(static_cast<int>(col_map[j][i]))+", ";
        }
        res.pop_back();
        res.pop_back();
        res+="}, {";
    }
    res.pop_back();
    res.pop_back();
    res.pop_back();
    res+="}";
    return res;
}
void map::viewShortRoot(){
    std::queue<std::pair<int,int>> visited_node;
    visited_node.push(start_point);
    int dx[4]={1,0,-1,0};
    int dy[4]={0,1,0,-1};
    int value_map[6][6]={0,};
    while (!visited_node.empty()) {
        int x=visited_node.front().first,y=visited_node.front().second;
        for(int i=0;i<4;i++){
            int px=x+dx[i];
            int py=y+dy[i];


            if(px<0||px>5||py<0||py>5||(px==start_point.first&&py==start_point.second)){
                continue;
            }


            if(value_map[px][py]==0&&!col_map[px][py]){
                value_map[px][py]=value_map[x][y]+1;
                visited_node.push(std::make_pair(px,py));
            }
        }
        visited_node.pop();
    }
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(col_map[i][j]){
                value_map[i][j]=-1;
            }
        }
    }
    int x=end_point.first,y=end_point.second;
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(15);
    while (!(x==start_point.first&&y==start_point.second)) {
        for(int i=0;i<4;i++){
            int px=x+dx[i];
            int py=y+dy[i];

            if(px<0||px>5||py<0||py>5||(px==end_point.first&&py==end_point.second)){
                continue;
            }

            if(value_map[px][py]==value_map[x][y]-1){
                scene->addLine((100+px*700/5),(100+py*700/5),(100+x*700/5),(100+y*700/5),pen);
                x=px;
                y=py;
                break;
            }
        }
    }

    QFont font;
    font.setPixelSize(60);
    font.setBold(true);

    QGraphicsTextItem *text = scene->addText("");
    text->setHtml("<div style='background-color:#42ecab;'>START</div>");
    text->setFont(font);
    int start_x=100+start_point.first*700/5-90
        ,start_y=100+start_point.second*700/5-45;

    text->setPos(start_x,start_y);




    text = scene->addText("");
    text->setHtml("<div style='background-color:#42ecab;'>END</div>");
    start_x=100+end_point.first*700/5-54;
    start_y=100+end_point.second*700/5-45;
    text->setPos(start_x,start_y);
    text->setFont(font);
}
