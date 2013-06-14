#include "PreCode.hpp"

namespace gg = boost::gregorian;
namespace pt = boost::posix_time;

//PreCode
PreCode::PreCode (std::string URL, pt::time_duration Delay,
                  std::string Cache, std::string Lock) :
  m_URL (URL), m_Cache (Cache, Lock), m_Delay (Delay)
{
}//PreCode


//Get
std::string PreCode::Get ()
{
  AutoUpdate (this);
  return GetCache ();
}//Get


//IsOutdated
bool PreCode::IsOutdated () const
{
  try
  {
    return (pt::second_clock::local_time () >= GetExpiry ());
  }
  catch (Err)
  {
    return true;
  }
}//IsOutdated


//Update
void PreCode::Update ()
{
  GetData Data (m_URL);
  m_Cache.Set (&Data);
}//Update


//GetCache
std::string PreCode::GetCache () const
{
  if (!IsCacheValid ()) throw Err ("There is no valid cache value");
  return m_Cache.Get ()[1];
}//GetCache


//GetCreated
gg::date PreCode::GetCreated () const
{
  if (!IsCacheValid ()) throw Err ("Invalid creation date");
  gg::date Min (gg::min_date_time);
  return Min + gg::days (STN<long> (m_Cache.Get ()[0]));
}//GetCreated


//GetExpiry
pt::ptime PreCode::GetExpiry () const
{
  gg::date Created (GetCreated ());
  //is creation date on another month as the expiry
  if (pt::ptime (Created) >= ExpiryOfMonth (Created))
    Created += gg::months (1);
  return ExpiryOfMonth (Created);
}//GetExpiry


//AutoUpdate
void PreCode::AutoUpdate (PreCode *Val)
{
  if (Val->IsOutdated ()) Val->Update ();
}//AutpUpdate


//IsCacheValid
bool PreCode::IsCacheValid () const
{
  return (m_Cache.Get ().size () > 1);
}//IsCacheValid


//ExpiryOfMonth
pt::ptime PreCode::ExpiryOfMonth (gg::date Month) const
{
  return pt::ptime (gg::date (Month.year (), Month.month (), 1), m_Delay);
}//ExpiryOfMonth


//GetData
GetData::GetData (std::string URL) :
  m_URL (URL)
{
}//GetData


//operator()
std::vector<std::string> GetData::operator() ()
{
  std::vector<std::string> Data (2);
  gg::date Cur = gg::day_clock::local_day ();
  Data[0] = NTS<char> ((Cur - gg::date (gg::min_date_time)).days ());
  Data[1] = GetFreshPreCode (m_URL);

  return Data;
}//operator()
