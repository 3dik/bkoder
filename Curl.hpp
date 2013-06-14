//curl class
//It must not be copied because the curl handle duplicate function does not
//copy cookies, connections, ssl sessions etc..

#pragma once

#include <string>
#include <vector>
#include "curl/curl.h"
#include "boost/utility.hpp"

#include "Err.hpp"

struct Curl : boost::noncopyable
{
  Curl ();
  ~Curl ();
  template <class T>
  Curl &Set (CURLoption Opt, T Val);
  void SetPost (std::vector<std::pair<std::string,std::string> > Data);
  std::string Perform ();
  //Sets the host address (e.g. 'http://www.example.com/')
  void SetHost (std::string Host);
  //Sets the "path" (e.g. 'index.php?id=23')
  void SetPath (std::string Path);

  private:

  std::string Encode (std::string Var) const;
  std::string Decode (std::string Var) const;

  //callback for 'perform' of libcurl
  static size_t GetBuf (void *Buf, size_t Size, size_t Multi, void *Target);

  CURL *m_Handle;
  std::string m_Host;
};

#include "Curl.inl"
