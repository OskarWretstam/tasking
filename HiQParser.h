#ifndef HIQPARSER_H
#define HIQPARSER_H

#include <fstream>
#include "HiQRobot.h"
#include <string>

class HiQParser{

public:

  enum Cmd_Type_e {INVALID, PLACE, MOVE, LEFT, RIGHT, REPORT};

  Cmd_Type_e cmd = INVALID;
  std::pair<int,int> coordinate = {-1, -1};
  HiQRobot::Orientation_e orientation = HiQRobot::INVALID;

  int open(std::string filename);
  int close();
  int Next_cmd();
  Cmd_Type_e Get_cmd();
  std::pair<int,int> Get_Coord();

private:

  std::ifstream input_file;

};

#endif // HIQPARSER_H
