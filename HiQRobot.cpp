#include "HiQRobot.h"

// Constructor takes the world limits as a parameter
//
HiQRobot::HiQRobot(int maxX, int maxY){
  position[0] = -1;
  position[1] = -1;
  orientation = NORTH;
  placed = false;

  limits[0] = maxX;
  limits[1] = maxY;
}

// Move one step forward in current facing direction
//
// Returns 1 on disallowed movement which would cause the robot to fall
bool HiQRobot::move(){
  if(!placed){
    return true;
  }

  switch(orientation){
  case NORTH:
    if(position[1] < limits[1]){
      position[1] += 1;
      return false;
    }
    break;

  case SOUTH:
    if(position[1] > 0){
      position[1] -= 1;
      return false;
    }
    break;

  case EAST:
    if(position[0] < limits[0]){
      position[0] += 1;
      return false;
    }
    break;

  case WEST:
    if(position[0] > 0){
      position[0] -= 1;
      return false;
    }
    break;

  default:
    return true;
  }

  return true;
}

// Place the robot at given x,y coordinates in dir facing direction
//
// Returns 1 on failed placement, where given coordinates are outside of this world, 0 otherwise
bool HiQRobot::place(int x, int y, Orientation_e orientation)
{
  if((x < 0) || (x > limits[0])){
    return true;
  }

  if((y < 0) || (y > limits[1])){
    return true;
  }

  this->orientation = orientation;
  position[0] = x;
  position[1] = y;
  placed = true;

  return 0;
}

// Rotate robot left of right 90 degrees relative to current facing direction
//
bool HiQRobot::rotate(Direction_e direction){
  if(!placed){
    return true;
  }

  orientation += direction;
  orientation %= 360;

  if(orientation < 0){
    orientation += 360;
  }

  return false;
}

// Print status
//
std::string HiQRobot::report(){
  if(!placed){
    return std::string("");
  }

  std::string posStr =  "<" + std::to_string(position[0]) + ", " + std::to_string(position[1]) + ">,";
  std::string orStr;
  switch(orientation){
  case NORTH:
    orStr.assign(" NORTH");
    break;

  case SOUTH:
    orStr.assign(" SOUTH");
    break;

  case WEST:
    orStr.assign(" WEST");
    break;

  case EAST:
    orStr.assign(" EAST");
    break;
  }

  return posStr.append(orStr);
}

// Get placed status
//
bool HiQRobot::isPlaced(){
  return placed;
}

// Get orientation
//
int HiQRobot::getOrientation(){
  return orientation;
}

// Get position tuple
//
std::tuple<int,int> HiQRobot::getPosition(){
  return {position[0], position[1]};
}
