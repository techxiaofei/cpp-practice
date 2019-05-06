#pragma once

#include <unordered_set>
#include <unordered_map>

#define GX 8
#define GY 8
#define FACTOR 100

namespace AOI{

class AOIGrid{

public:
    AOIGrid(int width, int height);

public:
    //aoi api
    void Enter(int id, int gid);
    void Leave(int id, int gid);
    void Move(int id, int x, int y);

    int width() const{return width_;}
    int height() const{return height_;}


private:
    int width_;  //scene width
    int height_;  //scene height

    typedef std::unordered_map<int, std::unordered_set<int>> Grids;  //gid=>(idlist)

    enum DIR {
        DIR_NULL = 0,
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_LEFT_UP,
        DIR_RIGHT_UP,
        DIR_RIGHT_DOWN,
        DIR_RIGHT_DOWN
    };


private:
    void InitGrids();
    void EnterBroadcast(int id, int x, int y);
    void LeaveBroadcast(int id, int x, int y);
    void MoveBroadcast(int id, int x, int y);

    int GetGid(int x, int y) const;
    int GxGy2Gid(int gx, int gy) const;

    void ViewEntities(std::unordered_set<int>& entities, int x, int y);
    void ViewGrids(std::unordered_set<int>& view_grids, int x, int y);

    void GridEntities(std::unordered_set<int>& entities, int gid);

    void Notify(int id, std::unordered_set<int>& leave_girds, std::unordered_set<int>& enter_grids);

    DIR GetDir(int x1, int y1, int x2, int y2);

    void move_up(int id, int x, int y);
    void move_down(int id, int x, int y);
    void move_left(int id, int x, int y);
    void move_right(int id, int x, int y);
    void move_left_up(int id, int x, int y);
    void move_right_up(int id, int x, int y);
    void move_left_down(int id, int x, int y);
    void move_right_down(int id, int x, int y);

};

}