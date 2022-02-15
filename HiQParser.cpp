#include "HiQParser.h"
#include <iostream> // todo remove
#include <vector>
#include <sstream>

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

  // Read line from file
  std::string intermediate;
  std::getline(input_file, intermediate);

  // Create a stream from the read line and use it to fill a vector of string tokens
  std::stringstream line(intermediate);
  std::vector <std::string> tokens;

  std::getline(line, intermediate, ' ');
  tokens.push_back(intermediate);

  while(getline(line, intermediate, ',')){
    tokens.push_back(intermediate);
  }

  bool parse_ok = false;
  if((tokens.front().compare("PLACE") == 0) && (tokens.size() == 4)){
    parse_ok = true;

    // cmd = PLACE;
    // coordinate.first =
    //   coordinate.second =

  }

  if(tokens.size() == 1){

  }

  return parse_ok;
}

HiQParser::Cmd_Type_e HiQParser::Get_cmd(){
  return cmd;
}

std::pair<int,int> HiQParser::Get_Coord(){
  return coordinate;
}
