#ifndef HIQPARSER_H
#define HIQPARSER_H

#include <fstream>

class HiQParser{

public:

  enum Command_e {PLACE, MOVE, LEFT, RIGHT, REPORT};


private:

  std::ifstream file;

};

#endif // HIQPARSER_H
