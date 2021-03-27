#include "GetPot"

#include <iostream>
#include <string>

int
main(int argc, char **argv)
{
  GetPot            command_line(argc, argv);
  const std::string filename = command_line.follow("data", 2, "-f", "--file");

  GetPot            datafile(filename.c_str());
  const std::string section = "integration/domain/";

<<<<<<< HEAD
  double a = datafile((section1 + "a").data(), 0.);
=======
  double a = datafile((section + "a").data(), 0.);
>>>>>>> d29353d33503b636e621e7c30f46234b00f70114
  /* ... */
  return 0;
}
