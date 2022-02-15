#include <iostream>
#include <string>
#include "HiQRobot.h"
#include "HiQParser.h"
#include "HiQTests.h"

int main(int argc, char* argv[]){

  std::string inputParam;

  // Input arguments, could be filename to run or test
  if(argc == 2){
    inputParam.assign(argv[1]);
    std::cout << "Running application with input: " << inputParam << std::endl;
  }
  else{
    std::cout << "Please provide argument filepath|test" << std::endl;
  }

  // Potentially Run unit tests
  if(inputParam.compare("test") == 0){
    std::cout << "Running test suite ... ";
    runTests();

    return 0;
  }

  // Setup robot, note that limits are 0-indices
  HiQRobot r = HiQRobot(4, 4);

  // Setup parser for input file
  HiQParser p = HiQParser();
  if(p.open(inputParam) == 1){
    std::cout << "Failed to open file: " << inputParam << ", exiting" << std::endl;
    return 1;
  }

  // todo
  std::pair<int,int> coord;
  // Start execution
  while(p.Next_cmd() == 0){
    switch(p.Get_cmd()){
    case HiQParser::PLACE:
      coord = p.Get_Coord();
      r.place(coord.first, coord.second, p.Get_Orientation());
      break;

    case HiQParser::MOVE:
      r.move();
      break;

    case HiQParser::LEFT:
      r.rotate(HiQRobot::LEFT);
      break;

    case HiQParser::RIGHT:
      r.rotate(HiQRobot::RIGHT);
      break;

    case HiQParser::REPORT:
      r.print();
      break;

    case HiQParser::INVALID:
      std::cout << "Invalid command from parser.." << std::endl;
      return 1;
      break;
    }
  }

  // Free resource
  p.close();

  return 0;
}
