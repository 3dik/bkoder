#include "Err.hpp"

//Unknown
template <>
std::string TErr<char>::Unknown ()
{
  return "An unknown error has occured";
}//Prepare


//Unknown
template <>
std::wstring TErr<wchar_t>::Unknown ()
{
  std::string Ascii = TErr<char>::Unknown (); //I hate redundancy :P
  return std::wstring (Ascii.begin (), Ascii.end ());
}//Unknown
