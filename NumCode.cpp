#include "NumCode.hpp"

//GetNumCode
std::string GetNumCode ()
{
  srand (time (NULL));
  return NTS<char> (((rand () % 30000) + 3334) * 3); //from 3334 to 33333
}//GetNumCode
