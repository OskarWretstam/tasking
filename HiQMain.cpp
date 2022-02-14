#include <iostream>
#include <string>
#include "HiQRobot.h"

int main(int argc, char* argv[]){

  if(argc != 2 ||
     (*argv[1] != 0x30 && *argv[1] != 0x31)){
    std::cout << "Please provide argument 0|1, exiting." << std::endl;
    return 0;
  }

  int mode = *argv[1] - 0x30;
  std::cout << "Mode is: " << mode << std::endl;

  if(mode){
    // Run
    std::pair<int,int> lims(4,4);
    HiQRobot Robot = HiQRobot(lims);
    Robot.print();
  } else {
    // Test
  }


  std::cout << "Hello world!" << std::endl;

  return 0;
}
