#ifndef HIQPARSER_H
#define HIQPARSER_H

#include <fstream>
#include "HiQRobot.h"
#include <string>
#include <map>

class HiQParser{

public:

  // Public typedefinitions
  enum Cmd_Type_e {INVALID, PLACE, MOVE, LEFT, RIGHT, REPORT};

  // Public function declarations
  int open(std::string filename);
  int close();
  int Next_cmd();
  Cmd_Type_e Get_cmd();
  std::pair<int,int> Get_Coord();
  HiQRobot::Orientation_e Get_Orientation();

private:

  // Private variables
  Cmd_Type_e cmd = INVALID;
  std::pair<int,int> coordinate = {-1, -1};
  HiQRobot::Orientation_e orientation = HiQRobot::INVALID;
  std::ifstream input_file;

  // Map valid commands
  const std::map<std::string, Cmd_Type_e> cmd_map = {{"PLACE", PLACE},
						     {"MOVE", MOVE},
						     {"LEFT", LEFT},
						     {"RIGHT", RIGHT},
						     {"REPORT", REPORT}};

  // Map valid orientations
  const std::map<std::string, HiQRobot::Orientation_e> orientation_map = {{"NORTH", HiQRobot::NORTH},
									  {"SOUTH", HiQRobot::SOUTH},
									  {"EAST", HiQRobot::EAST},
									  {"WEST", HiQRobot::WEST}};

};

#endif // HIQPARSER_H
