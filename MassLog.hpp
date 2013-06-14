//mass logging class
//multiple processes can access to the same log file

#pragma once

#include <fstream>
#include "boost/interprocess/sync/file_lock.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Err.hpp"
#include "String.hpp"

template <class T>
struct TAddLog
{
  TAddLog (std::string Path, std::basic_string<T> Msg);
};

typedef TAddLog<char> AddLog;
typedef TAddLog<wchar_t> WAddLog;

#include "MassLog.inl"
