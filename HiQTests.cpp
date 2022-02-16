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
  assert(r.rotate(HiQRobot::LEFT));
  assert(r.report().compare("") == 0);
}

// Test that we can parse a place command
//
void testParsePlace(){
  // Setup
  std::string filename("./test_files/place.txt");
  HiQParser p = HiQParser();
  assert(!p.open(filename));
  HiQParser::cmdStruct_t cmdStruct;

  // Test valid placements

  // PLACE 0,0,SOUTH
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == HiQParser::PLACE);
  assert(cmdStruct.coordinate[0] == 0);
  assert(cmdStruct.coordinate[1] == 0);
  assert(cmdStruct.orientation == HiQRobot::SOUTH);

  // PLACE 3,0,NORTH
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == HiQParser::PLACE);
  assert(cmdStruct.coordinate[0] == 3);
  assert(cmdStruct.coordinate[1] == 0);
  assert(cmdStruct.orientation == HiQRobot::NORTH);

  // PLACE 0,3,WEST
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == HiQParser::PLACE);
  assert(cmdStruct.coordinate[0] == 0);
  assert(cmdStruct.coordinate[1] == 3);
  assert(cmdStruct.orientation == HiQRobot::WEST);

  // PLACE 3,3,EAST
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == HiQParser::PLACE);
  assert(cmdStruct.coordinate[0] == 3);
  assert(cmdStruct.coordinate[1] == 3);
  assert(cmdStruct.orientation == HiQRobot::EAST);

  // PLACE 1b,13,WEST
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == HiQParser::PLACE);
  assert(cmdStruct.coordinate[0] == 1);
  assert(cmdStruct.coordinate[1] == 13);
  assert(cmdStruct.orientation == HiQRobot::WEST);

  // Test some invalid placements

  // PLACE
  assert(p.nextCmd());
  // PLACE a1,b,SOUTH
  assert(p.nextCmd());
  // PLACE 0,0,QWE
  assert(p.nextCmd());
  // PLACE 3,
  assert(p.nextCmd());

  // Free resource
  p.close();
}

// Test that we can parse a command without parameters
//
void testParseParameterless(std::string testFile, HiQParser::cmdType_e result){
  // Setup
  std::string filename(testFile);
  HiQParser p = HiQParser();
  assert(!p.open(filename));
  HiQParser::cmdStruct_t cmdStruct;

  // Valid move command

  // COMMAND
  assert(!p.nextCmd());
  cmdStruct = p.getCmd();
  assert(cmdStruct.cmd == result);

  // Invalid

  // COMMANDQ
  assert(p.nextCmd());

  // COMMAND Q - command takes no parameters
  assert(p.nextCmd());

  // Free resource
  p.close();
}

// Test that we wont accept invalid input
//
void testParseInvalid(){
  // Setup
  std::string filename("./test_files/invalid.txt");
  HiQParser p = HiQParser();
  assert(!p.open(filename));

  // File just contains some jibberish to test
  // for crashes, verify that all the lines just
  // return invalid cmd
  assert(p.nextCmd());
  assert(p.nextCmd());
  assert(p.nextCmd());
  assert(p.nextCmd());
  assert(p.nextCmd());
  assert(p.nextCmd());

  // Free resource
  p.close();
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
  testParseParameterless("./test_files/move.txt", HiQParser::MOVE);
  testParseParameterless("./test_files/left.txt", HiQParser::LEFT);
  testParseParameterless("./test_files/right.txt", HiQParser::RIGHT);
  testParseParameterless("./test_files/report.txt", HiQParser::REPORT);
}
