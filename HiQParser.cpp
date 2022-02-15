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

  // Add potential additional parameters to string vector
  while(getline(line, intermediate, ',')){
    tokens.push_back(intermediate);
  }

  // Check if command exists in our map
  auto search_cmd = cmd_map.find(tokens.front());
  if(search_cmd == cmd_map.end()){
    return 1;
  }

  cmd = search_cmd->second;

  if(cmd == PLACE){
    // Place commands takes parameters, verify that we read them and assign
    if(tokens.size() != 4){
      return 1;
    }

    coordinate.first = stoi(tokens[1]);
    coordinate.second = stoi(tokens[2]);

    auto search_orient = orientation_map.find(tokens[3]);
    if(search_orient == orientation_map.end()){
      return 1;
    }

    orientation = search_orient->second;
  }
  else {
    // The remaining commands comes without parameters, ergo no more tokens
    if(tokens.size() != 1){
      return 1;
    }
  }

  return 0;
}

HiQParser::Cmd_Type_e HiQParser::Get_cmd(){
  return cmd;
}

std::pair<int,int> HiQParser::Get_Coord(){
  return coordinate;
}

HiQRobot::Orientation_e HiQParser::Get_Orientation(){
  return orientation;
}
