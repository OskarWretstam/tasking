# HiQ Robot simulator

Compile & run with make installed

	$ make all && ./out/app ./test_files/large_example.txt

or just g++

	$ g++ HiQMain.cpp HiQParser.cpp HiQRobot.cpp HiQTests.cpp && ./a.out ./test_files/large_example.txt

The produced application will accept either a given file or 'test' as its only parameter.

Breifly explained the included files are:

- HiQRobot.{cpp,h} which implemenets a robot class
- HiQParser.{cpp,h} implementing  a class to parse the input file
- HiQTests.{cpp,h} that contains the unit tests (executed with parameter 'test')
- HiQMain.cpp that executes the application
