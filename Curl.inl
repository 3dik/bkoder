//look at Curl.hpp

#pragma once

//Set
template <class T>
Curl &Curl::Set (CURLoption Opt, T Val)
{
  if (curl_easy_setopt (m_Handle, Opt, Val)) throw Err("Could not set option");
  return *this;
}//Set
