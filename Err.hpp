//Exception class

#pragma once

#include <iostream>

template <class T>
struct TErr
{
  TErr ();
  TErr (std::basic_string<T> Msg);
  TErr Set (std::basic_string<T> Msg);
  //Returns error message. Returns a default error message if message is empty
  std::basic_string<T> Get (bool FillEmpty=false) const;

  static std::basic_string<T> Unknown ();

  private:

  std::basic_string<T> m_Msg;
};

template <class T>
std::basic_ostream<T> &operator<< (std::basic_ostream<T> &, const TErr<T> &);

typedef TErr<char> Err;
typedef TErr<wchar_t> WErr;

template <>
std::string TErr<char>::Unknown ();
template <>
std::wstring TErr<wchar_t>::Unknown ();

#include "Err.inl"
