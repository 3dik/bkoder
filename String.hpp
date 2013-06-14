//cool string functions

#pragma once

#include <string>
#include <cstdlib>
#include <sstream>

#include "Err.hpp"

//These cool function divides a string by the given separator string
template <class T>
std::basic_string<T> Cut (std::basic_string<T> Val, std::basic_string<T> Find,
                 bool LeftPast, bool LeftFind);

//number to string
template <class T, class Num>
std::basic_string<T> NTS (Num Var);
//string to number
template <class Num, class T>
Num STN (std::basic_string<T> Var);

enum DynChar
{
  SPACE,
  DASH,
  DOT,
  SLASH,
  BACKSLASH
};

template <class T>
T GetChar (DynChar);
template <>
char GetChar (DynChar);
template <>
wchar_t GetChar (DynChar);
template <class T>
std::basic_ostream<T> &operator<< (std::basic_ostream<T> &, DynChar);

struct ConversionErr : Err
{
  ConversionErr ();
};

template <class Type, class Var>
std::basic_string<Type> StreamOp (Var Val);

#include "String.inl"
