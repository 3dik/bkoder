#pragma once

//Cut
template <class T>
std::basic_string<T> Cut (std::basic_string<T> Val, std::basic_string<T> Find,
                 bool LeftPast, bool LeftFind)
{
  if (Val.empty () || Find.empty ()) throw Err ("nub arguments");
  
  size_t Pos = Val.find (Find);
  if (Pos == std::basic_string<T>::npos)
    throw Err ("Could not find the string, ling ling");
  size_t Remain = 0;
  if (LeftFind) Remain = Find.size ();
  if (LeftPast) return Val.substr (Pos + Find.size () - Remain);
  return Val.substr (0, Pos + Remain);
}//Cut


//NTS
template <class T, class Num>
std::basic_string<T> NTS (Num Var)
{
  return StreamOp<T> (Var);
}//NTS


//STN
template <class Num, class T>
Num STN (std::basic_string<T> Var)
{
  std::basic_stringstream<T> Str (Var);
  int Val;
  if (!(Str>>Val)) throw ConversionErr ();
  return Val;
}//STN


//operator<<
template <class T>
std::basic_ostream<T> &operator<< (std::basic_ostream<T> &Target, DynChar Char)
{
  return Target<<GetChar<T> (Char);
}//operator<<


//StreamOp
template <class Type, class Var>
std::basic_string<Type> StreamOp (Var Val)
{
  std::basic_ostringstream<Type> Str;
  Str<<Val;
  return Str.str ();
}//StreamOp
