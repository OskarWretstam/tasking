#ifndef HIQROBOT_H
#define HIQROBOT_H

#include <utility>

class HiQRobot{

public:

  enum Direction_e {LEFT = -90, RIGHT = 90};
  enum Orientation_e {INVALID = -1, NORTH = 0, EAST = 90, SOUTH = 180, WEST = 270};

  // Constuctor
  HiQRobot(std::pair<int,int> limits);

  // Public functions
  void print();
  bool isPlaced();
  int place(std::pair<int,int> pos, Orientation_e orientation);
  int move();
  void rotate(Direction_e direction);

private:

  std::pair<int, int> position = {-1, -1};
  std::pair<int,int> limits = {-1, -1};
  int orientation = INVALID;
  bool placed = false;

};

#endif // HIQROBOT_H
