#pragma once

//TAddLog
template <class T>
TAddLog<T>::TAddLog (std::string Path, std::basic_string<T> Msg)
{
  std::basic_ofstream<T> File (Path.c_str (), std::ios_base::app);
  if (!File) throw Err ("Could not access log file");

  using namespace boost::interprocess;
  file_lock Lock (Path.c_str ());
  scoped_lock<file_lock> WriteLock (Lock);

  using namespace boost::posix_time;
  ptime Time = second_clock::local_time ();

  File<<Time<<SPACE<<std::right<<Msg<<std::endl;
}//TAddLog
