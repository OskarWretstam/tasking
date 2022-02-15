#include "HiQTests.h"
#include "HiQParser.h"
#include "HiQRobot.h"
#include <cassert>

// Test robot place command, verifies that the robot can be placed, only on the table and
// that it can be re-placed
//
void testRobotPlacement(){
  // Setup
  HiQRobot r = HiQRobot(4, 4);
  HiQRobot::Orientation_e orientation = HiQRobot::EAST;

  // Verify that robot wont be placed outside the world
  r.place(-1, 1, orientation);
  assert(!r.isPlaced());
  r.place(1, -1, orientation);
  assert(!r.isPlaced());
  r.place(5, 1, orientation);
  assert(!r.isPlaced());
  r.place(1, 5, orientation);
  assert(!r.isPlaced());

  // Verify that robot can be placed correctly
  int x = 2, y = 2;
  r.place(x, y, orientation);
  assert(r.isPlaced());
  auto [x1, y1] = r.getPosition();
  assert((x1 == x) && (y1 == y));
  assert(r.getOrientation() == 90);

  // Verify that it can be re-placed
  x = 3, y = 3, orientation = HiQRobot::SOUTH;
  r.place(x, y, orientation);
  assert(r.isPlaced());
  auto [x2, y2] = r.getPosition();
  assert((x2 == x) && (y2 == y));
  assert(r.getOrientation() == 180);
}

// Test that the robot can be rotated in 90 deg steps around its axis with LEFT and RIGHT commands
//
void testRobotRotation(){
  // Setup
  HiQRobot r = HiQRobot(4, 4);
  HiQRobot::Orientation_e orientation = HiQRobot::NORTH;
  r.place(2, 2, orientation);
  assert(r.getOrientation() == 0);

  // Test a clockwise turn
  r.rotate(HiQRobot::RIGHT);
  assert(r.getOrientation() == 90);
  r.rotate(HiQRobot::RIGHT);
  assert(r.getOrientation() == 180);
  r.rotate(HiQRobot::RIGHT);
  assert(r.getOrientation() == 270);
  r.rotate(HiQRobot::RIGHT);
  assert(r.getOrientation() == 0);

  // And counter-clockwise turn
  r.rotate(HiQRobot::LEFT);
  assert(r.getOrientation() == 270);
  r.rotate(HiQRobot::LEFT);
  assert(r.getOrientation() == 180);
  r.rotate(HiQRobot::LEFT);
  assert(r.getOrientation() == 90);
  r.rotate(HiQRobot::LEFT);
  assert(r.getOrientation() == 0);
}

// Test that the robot can move and that it will not walk of the table
//
void testRobotMovement(){
  // Setup
  HiQRobot r = HiQRobot(4, 4);
  HiQRobot::Orientation_e orientation;

  // Disallowed movement

  // Bottom left "corner-case" :)
  orientation = HiQRobot::WEST;
  r.place(0, 0, orientation);
  assert(r.move());
  orientation = HiQRobot::SOUTH;
  r.place(0, 0, orientation);
  assert(r.move());

  // Bottom right
  orientation = HiQRobot::EAST;
  r.place(4, 0, orientation);
  assert(r.move());
  orientation = HiQRobot::SOUTH;
  r.place(4, 0, orientation);
  assert(r.move());

  // Top left
  orientation = HiQRobot::WEST;
  r.place(0, 4, orientation);
  assert(r.move());
  orientation = HiQRobot::NORTH;
  r.place(0, 4, orientation);
  assert(r.move());

  // Top right
  orientation = HiQRobot::EAST;
  r.place(4, 4, orientation);
  assert(r.move());
  orientation = HiQRobot::NORTH;
  r.place(4, 4, orientation);
  assert(r.move());

  // Allowed movement
  orientation = HiQRobot::EAST;
  r.place(3, 4, orientation);
  assert(!r.move());
}

// Test that the robot will ignore commands while it is not placed
//
void testRobotNotPlaced(){
  // Setup
  HiQRobot r = HiQRobot(4, 4);
  assert(!r.isPlaced());

  // Test
  assert(r.move());
  assert(r.print());
  assert(r.rotate(HiQRobot::LEFT));
}

// Test that we can parse a place command
//
void testParsePlace(){

}

// Test that we cannot parse a place command without the full set of parameters
//
void testParsePlaceWOParams(){

}

// Test that we can parse a move command
//
void testParseMove(){

}

// Test that we can parse a left command
//
void testParseLeft(){

}

// Test that we can parse a right command
//
void testParseRight(){

}

// Test that we can parse a report command
//
void testParseReport(){

}

// Test that we wont accept invalid input
//
void testParseInvalid(){

}

// Public function
void runTests(){
  // Test robot functionality
  testRobotPlacement();
  testRobotRotation();
  testRobotMovement();
  testRobotNotPlaced();

  // Test parser
  testParsePlace();
  testParsePlaceWOParams();
  testParseMove();
  testParseLeft();
  testParseRight();
  testParseReport();
  testParseInvalid();


}
