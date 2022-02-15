#include "HiQRobot.h"
#include <iostream>

// Constructor takes the world limits as a parameter which are required when placing a robot
//
HiQRobot::HiQRobot(std::pair<int, int> limits){
  position.first = -1;
  position.second = -1;
  orientation = NORTH;
  placed = false;

  this->limits.first = limits.first;
  this->limits.second = limits.second;
}

// Move one step forward in current facing direction
//
// Returns 1 on disallowed movement which would cause the robot to fall
int HiQRobot::move(){
  if(placed){
    switch(orientation){
    case NORTH:
      if(position.second < limits.second){
	position.second += 1;
	return 0;
      }
      break;

    case SOUTH:
      if(position.second > 0){
	position.second -= 1;
	return 0;
      }
      break;

    case EAST:
      if(position.first < limits.first){
	position.first += 1;
	return 0;
      }
      break;

    case WEST:
      if(position.first > 0){
	position.first -= 1;
	return 0;
      }
      break;

    default:
      std::cout << "Error> Invalid orientation: " << orientation << "in HiQRobot::move()" << std::endl;
      break;
    }
  }

  std::cout << "Warning: Disregard invalid move command" << std::endl;

  return 1;
}

// Place the robot at given x,y coordinates in dir facing direction
//
// Returns 1 on failed placement, where given coordinates are outside of this world, 0 otherwise
int HiQRobot::place(std::pair<int,int> pos, Orientation_e orientation)
{
  if((pos.first < 0) || (pos.first > limits.first)){
    return 1;
  }

  if((pos.second < 0) || (pos.second > limits.second)){
    return 1;
  }

  this->orientation = orientation;
  position.first = pos.first;
  position.second = pos.second;
  placed = true;

  return 0;
}

// Rotate robot left of right 90 degrees relative to current facing direction
//
void HiQRobot::rotate(Direction_e direction){
  if(placed){
    orientation += direction;
    orientation %= 360;

    if(orientation < 0){
      orientation += 360;
    }
  }
}

// Print status
//
void HiQRobot::print(){
  if(placed){
    std::cout << "Robot position is: <" << this->position.first << ", " << this->position.second << ">" << std::endl;
  } else {
    std::cout << "Robot is not placed yet.." << std::endl;
  }
}
