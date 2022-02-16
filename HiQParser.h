#ifndef HIQPARSER_H
#define HIQPARSER_H

#include <fstream>
#include <string>
#include <map>

#include "HiQRobot.h"

class HiQParser{

public:

  // Public type definitions
  enum cmdType_e {INVALID, PLACE, MOVE, LEFT, RIGHT, REPORT};

  typedef struct{
    bool valid = false;
    cmdType_e cmd;
    std::array<int, 2> coordinate;
    HiQRobot::Orientation_e orientation;
  } cmdStruct_t;

  // Public function declarations
  bool open(std::string filename);
  bool close();
  bool nextCmd();
  cmdStruct_t getCmd();

private:

  // Private variables
  cmdStruct_t cmdStruct;
  std::ifstream inputFile;

  // Map valid commands
  const std::map<std::string, cmdType_e> cmdMap = {{"PLACE", PLACE},
						    {"MOVE", MOVE},
						    {"LEFT", LEFT},
						    {"RIGHT", RIGHT},
						    {"REPORT", REPORT}};

  // Map valid orientations
  const std::map<std::string, HiQRobot::Orientation_e> orientationMap = {{"NORTH", HiQRobot::NORTH},
									 {"SOUTH", HiQRobot::SOUTH},
									 {"EAST", HiQRobot::EAST},
									 {"WEST", HiQRobot::WEST}};

};

#endif // HIQPARSER_H
