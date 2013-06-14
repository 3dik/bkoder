#pragma once

#include <fstream>

#include "Err.hpp"

//Opens a file for reading. Creates if it does not exist
template <class T>
void OpenCreateRO (std::string Path, std::basic_ifstream<T> *File);

#include "File.inl"
