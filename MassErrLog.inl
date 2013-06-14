#pragma once

//AddErrLog
template <class T>
void AddErrLog (std::string Path, TErr<T> Msg)
{
  TAddLog<T> a (Path, Msg.Get (true));
}//AddErrLog
