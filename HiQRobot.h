#ifndef HIQROBOT_H
#define HIQROBOT_H

#include <utility>
#include <array>
#include <tuple>

class HiQRobot{

public:

  enum Direction_e {LEFT = -90, RIGHT = 90};
  enum Orientation_e {INVALID = -1, NORTH = 0, EAST = 90, SOUTH = 180, WEST = 270};

  // Constuctor
  explicit HiQRobot(int maxX, int maxY);

  // Public functions
  bool print();
  bool isPlaced();
  int getOrientation();
  std::tuple<int,int> getPosition();
  bool place(int x, int y, Orientation_e orientation);
  bool move();
  bool rotate(Direction_e direction);

private:

  std::array<int, 2> position = {-1, -1};
  std::array<int, 2> limits = {-1, -1};
  int orientation = INVALID;
  bool placed = false;

};

#endif // HIQROBOT_H
