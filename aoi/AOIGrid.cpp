#include "AOIGrid.h"

namespace AOI{

void AOIGrid::Enter(int id, int x, int y){
    int gid = GetGid(x, y);
    Enter(id, gid);
    EnterBroadcast(id, x, y);
}

void AOIGrid::ViewEntities(std::unordered_set<int>& view_grids, int x, int y){
    int gx = x / GX;
    int gy = y / GY;

    view_grids.insert(

    )
}


void InitGrids();
void EnterBroadcast(int id, int x, int y);
void LeaveBroadcast(int id, int x, int y);
void MoveBroadcast(int id, int x, int y);

int AOIGrid::GetGid(int x, int y) const{
    int gx = x / GX;
    int gy = y / GY;
    return GxGy2Gid(gx, gy);
}

int AOIGrid::GxGy2Gid(int x, int y) const{
    int gx1 = gx < 0 ? 0 : gx;
    int gy1 = gy < 0 ? 00 : gy;
    return gx1 * FACTOR + gy1;
}

void ViewEntities(std::unordered_set<int>& entities, int x, int y);
void ViewGrids(std::unordered_set<int>& view_grids, int x, int y);

void GridEntities(std::unordered_set<int>& entities, int gid);

void Notify(int id, std::unordered_set<int>& leave_girds, std::unordered_set<int>& enter_grids);

DIR GetDir(int x1, int y1, int x2, int y2);

void move_up(int id, int x, int y){
}

void move_down(int id, int x, int y);
void move_left(int id, int x, int y);
void move_right(int id, int x, int y);
void move_left_up(int id, int x, int y);
void move_right_up(int id, int x, int y);
void move_left_down(int id, int x, int y);
void move_right_down(int id, int x, int y);



}