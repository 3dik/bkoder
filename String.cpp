#include "String.hpp"

//GetChar
template <>
char GetChar (DynChar Char)
{
  switch (Char)
  {
    case SPACE: return ' ';
    case DASH: return '-';
    case DOT: return '.';
    case SLASH: return '/';
    case BACKSLASH: return '\\';
    default: throw Err ("Unknown DynChar");
  }
}//GetChar


//GetChar
template <>
wchar_t GetChar (DynChar Char)
{
  std::string S (1, GetChar<char> (Char));
  std::wstring W (S.begin (), S.end ());
  return W[0];
}//GetChar


//ConversionErr
ConversionErr::ConversionErr () :
  Err ("String conversion error")
{
}//ConversionErr
