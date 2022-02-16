#include "HiQParser.h"
#include <vector>
#include <sstream>

// Open file in parser
//
// returns true if unsucessful
bool HiQParser::open(std::string filename)
{
  if(inputFile.is_open()){
    inputFile.close();
  }

  inputFile.open(filename);

  return(!inputFile.is_open());
}

// Close file in parser
//
// returns true if unsucessful
bool HiQParser::close()
{
  if(inputFile.is_open()){
    inputFile.close();
  }

  return(inputFile.is_open());
}

// Try to parse next line & command, updates cmd state in parser
//
// returns true if unsucessful
bool HiQParser::nextCmd(){
  if(!inputFile.is_open()){
    return true;
  }

  if(!inputFile.good()){
    return true;
  }

  // Read line from file
  std::string intermediate;
  std::getline(inputFile, intermediate);

  // Create a stream from the read line and use it to fill a vector of string tokens
  std::stringstream line(intermediate);
  std::vector <std::string> tokens;

  std::getline(line, intermediate, ' ');
  tokens.push_back(intermediate);

  // Add potential additional parameters to string vector, maximum of 4 tokens for place command
  while(getline(line, intermediate, ',') && (tokens.size() <= 4)){
    tokens.push_back(intermediate);
  }

  // Check if command exists in our map
  auto searchCmd = cmdMap.find(tokens.front());
  if(searchCmd == cmdMap.end()){
    return 1;
  }

  cmdStruct.cmd = searchCmd->second;

  if(cmdStruct.cmd == PLACE){
    // Place commands takes parameters, verify that we read them and assign
    if(tokens.size() != 4){
      return true;
    }

    // Verify that coordinates are digits and convert to numbers
    if(!std::isdigit(tokens[1][0])){ // stoi only needs a single digit to work
      return true;
    }
    cmdStruct.coordinate[0] = stoi(tokens[1]);

    if(!std::isdigit(tokens[2][0])){
      return true;
    }
    cmdStruct.coordinate[1] = stoi(tokens[2]);

    // Given orientation should be in our map of valids
    auto searchOrient = orientationMap.find(tokens[3]);
    if(searchOrient == orientationMap.end()){
      return true;
    }

    cmdStruct.orientation = searchOrient->second;
  }
  else {
    // The remaining commands comes without parameters, ergo no more tokens
    if(tokens.size() != 1){
      return true;
    }
  }

  // Will always be true once the first valid commad was parsed
  cmdStruct.valid = true;

  return 0;
}

// Get current cmd state from parser
//
HiQParser::cmdStruct_t HiQParser::getCmd(){
  return cmdStruct;
}
