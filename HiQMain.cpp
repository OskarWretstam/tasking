#include <iostream>
#include <string>
#include "HiQRobot.h"
#include "HiQParser.h"
#include "HiQTests.h"

enum Run_Mode_e {RUN, TEST};

int main(int argc, char* argv[]){

  std::string filename;
  Run_Mode_e run_mode;

  // Input arguments, if given try to run that as a file
  if(argc < 2){
    run_mode = TEST;
    filename.assign("N/A");
    std::cout << "Running testcases.." << std::endl;
  } else {
    run_mode = RUN;
    filename.assign(argv[1]);
    std::cout << "Running application with input file: " << filename << std::endl;
  }


  if(run_mode == RUN){

    // Setup robot
    std::pair<int,int> limits = {5, 5};
    HiQRobot r = HiQRobot(limits);

    // Setup parser
    HiQParser p = HiQParser();
    if(p.open(filename) == 1){
      std::cout << "Failed to open file: " << filename << ", exiting" << std::endl;
      return 1;
    }

    // Start execution
    while(p.Next_cmd() == 0){
      switch(p.Get_cmd()){
      case HiQParser::PLACE:
	r.place(p.Get_Coord(), HiQRobot::NORTH);
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


  } else if(run_mode == TEST) {

    // todo
    std::cout << "TODO" << std::endl;
    // HiQTests::test_robot_placement();

  } else {
    std::cout << "Internal error, invalid run_mode: " << run_mode << std::endl;
    return 1;
  }

  return 0;
}
