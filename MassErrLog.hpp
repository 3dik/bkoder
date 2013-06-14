//mass log file for errors

#pragma once

#include "MassLog.hpp"

template <class T>
void AddErrLog (std::string Path, TErr<T> Msg);

#include "MassErrLog.inl"
