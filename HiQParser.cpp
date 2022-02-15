#include "HiQParser.h"
#include <iostream> // todo remove
#include <vector>

int HiQParser::open(std::string filename)
{
  if(input_file.is_open()){
    input_file.close();
  }

  input_file.open(filename);

  return(!input_file.is_open());
}

int HiQParser::close()
{
  if(input_file.is_open()){
    input_file.close();
  }

  return(input_file.is_open());
}

int HiQParser::Next_cmd(){
  if(!input_file.is_open()){
    return 1;
  }

  if(!input_file.good()){
    return 1;
  }

  std::string intermediate;

  std::getline(input_file, intermediate, ' ');
  std::cout << "First token " << intermediate << std::endl;

  if(intermediate.compare("PLACE")){
    cmd = PLACE;
  } else if(intermediate.compare("MOVE")){
    cmd = MOVE;
  } else if(intermediate.compare("LEFT")){
    cmd = LEFT;
  } else if(intermediate.compare("RIGHT")){
    cmd = RIGHT;
  } else if(intermediate.compare("REPORT")){
    cmd = REPORT;
  } else {
    std::cout << "Invalid command read " << intermediate << std::endl;
    return 1;
  }

  return 0;
}

HiQParser::Cmd_Type_e HiQParser::Get_cmd(){
  return cmd;
}

std::pair<int,int> HiQParser::Get_Coord(){
  return coordinate;
}
