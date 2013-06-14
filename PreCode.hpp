//Pre code extractor

#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"

#include "Survey.hpp"
#include "String.hpp"
#include "Cache.hpp"

struct PreCode : boost::noncopyable
{
  PreCode (std::string URL, boost::posix_time::time_duration Delay,
           std::string Cache, std::string Lock);
  //Checks for expiry. Mby updates. Returns current pre code
  std::string Get ();
  bool IsOutdated () const;
  void Update ();
  std::string GetCache () const;
  boost::gregorian::date GetCreated () const;
  boost::posix_time::ptime GetExpiry () const;

  //Updates if outdated
  static void AutoUpdate (PreCode *);

  private:

  bool IsCacheValid () const;
  boost::posix_time::ptime ExpiryOfMonth (boost::gregorian::date Month) const;

  std::string m_URL;
  Cache m_Cache;
  boost::posix_time::time_duration m_Delay;
};


struct GetData : Getter
{
  GetData (std::string URL);
  std::vector<std::string> operator() ();

  private:

  std::string m_URL;
};
