#pragma once

//OpenCreateRO
template <class T>
void OpenCreateRO (std::string Path, std::basic_ifstream<T> *File)
{
  std::ofstream Create (Path.c_str (), std::ios_base::app);
  if (!Create) throw Err ("Could not open file in write mode");
  if (File->is_open ()) File->close ();
  File->open (Path.c_str ());
  if (!(*File)) throw Err ("Could not open file in read mode");
}//OpenCreateRO
