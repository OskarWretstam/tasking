#ifndef HIQROBOT_H
#define HIQROBOT_H

#include <utility>

class HiQRobot{

public:

  enum Direction_e {LEFT = -90, RIGHT = 90};
  enum Orientation_e {NORTH = 0, EAST = 90, SOUTH = 180, WEST = 270};

  HiQRobot(std::pair<int,int> limits);
  void print();
  bool isPlaced();
  int place(int x, int y, Orientation_e orientation);
  int move();
  void rotate(Direction_e direction);

private:

  std::pair<int, int> position;
  std::pair<int,int> limits;
  int orientation;
  bool placed;

};

#endif // HIQROBOT_H
