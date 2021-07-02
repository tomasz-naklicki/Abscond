#ifndef WORLDGRID_HPP
#define WORLDGRID_HPP


class WorldGrid
{
public:
    //Constructor
    WorldGrid();

    //Public variables
    bool isPassable(short a, short b);
    void updateSlot(short a, short b, bool state);

private:
    //Private variables
    const short x = 29;
    const short y = 22;

    std::vector<bool> grid; //638
};

#endif // WORLDGRID_HPP
