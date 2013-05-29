#ifndef GRID_H
#define GRID_H


class Grid
{
public:
    enum Item
    {
        ItemWall,
        ItemBomb,
        ItemPlayer,
        ItemFree
    };

private:
    unsigned int m_gridrows;
    unsigned int m_gridcolums;

};


#endif


