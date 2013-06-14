#pragma once

//TErr
template <class T>
TErr<T>::TErr ()
{
}//TErr


//TErr
template <class T>
TErr<T>::TErr (std::basic_string<T> Msg)
{
  Set (Msg);
}//TErr


//Set
template <class T>
TErr<T> TErr<T>::Set (std::basic_string<T> Msg)
{
  m_Msg = Msg;
  return *this;
}//Set


//Get
template <class T>
std::basic_string<T> TErr<T>::Get (bool FillEmpty) const
{
  if (FillEmpty && m_Msg.empty ()) return Unknown ();
  return m_Msg;
}//Get


//operator<<
template <class T>
std::basic_ostream<T> &operator<< (std::basic_ostream<T> &Left,
                                   const TErr<T> &Msg)
{
  return Left<<Msg.Get (true);
}//operator<<
