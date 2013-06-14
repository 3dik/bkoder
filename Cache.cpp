#include "Cache.hpp"

namespace ip = boost::interprocess;

const std::string Cache::s_SignValid = "OK";

//Cache
Cache::Cache (std::string Path, std::string MutexName) :
  m_Path (Path), m_WriteMutex (MutexName)
{
  std::ifstream File;
  OpenCreateRO (Path, &File);
  m_Lock = ip::file_lock (Path.c_str ());
  m_Read = ip::sharable_lock<ip::file_lock> (m_Lock, ip::try_to_lock_type ());
  if (!m_Read.owns ()) throw UpdateByOther ();

  std::vector<std::string> Data;
  while (!File.eof ())
  {
    std::string Word;
    if (!(File>>Word)) break;
    Data.push_back (Word);
  }

  if (Data.empty () || Data[0] != s_SignValid) return;
  Data.erase (Data.begin ());
  m_Data = Data;
}//Cache


//~Cache
Cache::~Cache ()
{
  ip::named_recursive_mutex::remove (GetMutexName ().c_str ());
}//~Cache


//Get
std::vector<std::string> Cache::Get () const
{
  return m_Data;
}//Get


//Set
void Cache::Set (Getter *Data)
{
  ip::named_recursive_mutex Lock (ip::open_or_create_t (),
		GetMutexName ().c_str ());
  ip::scoped_lock<ip::named_recursive_mutex> Locker (Lock,
		ip::try_to_lock_type ());
  if (!Locker.owns ()) throw UpdateByOther ();

  m_Read.unlock ();
  try
  {
    Write (Data);
  }
  catch (...)
  {
    m_Read.lock ();
    throw;
  }
  m_Read.lock ();
}//Set


//Write
void Cache::Write (Getter *Data)
{
  ip::scoped_lock<ip::file_lock> Locker (m_Lock);
  using std::ios_base;
  std::ofstream File (m_Path.c_str (), ios_base::out | ios_base::trunc);
  if (!File) throw Err ("Could not open cache file");

  std::vector<std::string> New = (*Data) ();
  File<<s_SignValid;
  for (size_t i=0; i != New.size (); i++)
  {
    File<<" "<<New[i];
  }
  m_Data = New;
}//Write


//GetMutexName
std::string Cache::GetMutexName () const
{
  return "lochaplocha3851" + m_WriteMutex;
}//GetMutexName


//UpdateByOther
UpdateByOther::UpdateByOther () :
  Err ("Another bkoder process updates the cache currently")
{
}//UpdateByOther
