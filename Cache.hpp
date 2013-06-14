//Cache class
//Locks cache file until destruction

#pragma once

#include <fstream>
#include <vector>
#include "boost/interprocess/sync/file_lock.hpp"
#include <boost/interprocess/sync/named_recursive_mutex.hpp>
#include "boost/interprocess/sync/sharable_lock.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "boost/utility.hpp"

#include "String.hpp"
#include "File.hpp"

struct Getter
{
  virtual std::vector<std::string> operator() () = 0;
};

struct Cache : boost::noncopyable
{
  Cache (std::string Path, std::string MutexName);
  ~Cache ();
  std::vector<std::string> Get () const;
  //Call's only 'Data' if it obtaines write lock. LockPath must be defined
  void Set (Getter *Data);

  private:

  void Write (Getter *Data);
  std::string GetMutexName () const;

  std::vector<std::string> m_Data;
  mutable boost::interprocess::file_lock m_Lock;
  mutable boost::interprocess::sharable_lock<boost::interprocess::file_lock>
    m_Read;
  const std::string m_Path;
  const std::string m_WriteMutex;

  static const std::string s_SignValid;
};

struct UpdateByOther : Err
{
  UpdateByOther ();
};
