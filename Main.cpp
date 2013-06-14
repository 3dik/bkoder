//blblblblblblbkoderlblblblblblblb

#include "Main.hpp"

namespace po = boost::program_options;

//SetOpt
void Main::SetOpt (int argc, char *argv[])
{
  try
  {
    po::store (po::parse_command_line (argc, argv, GetSyntax ()), m_Var);
    po::notify (m_Var);
  }
  catch (po::error)
  {
    throw Err ("Syntax error. Run with '-h'");
  }
  po::notify (m_Var);
}//SetOpt


//Do
std::string Main::Do ()
{
  if (m_Var["help"].as<bool> ()) return ShowSyntax ();

  switch (m_Var["action"].as<char> ())
  {
    case 'f':
      return GetPreCode () + GetNumCode ();
    case 'p':
      return GetPreCode ();
    case 'n':
      return GetNumCode ();
    case 'u':
      return GetUpdate ();
    case 'i':
      return GetOutdated ();
    case 'c':
      return StreamOp<char> (OpenPreCode ()->GetCreated ());
    case 'e':
      return StreamOp<char> (OpenPreCode ()->GetExpiry ());
  }
  throw Err ("Invalid action mode");
}//Do


//WriteLog
void Main::WriteLog (Err Msg)
{
  if (!m_Var["log"].empty ()) AddErrLog (m_Var["log"].as<std::string> (), Msg);
}//WriteLog


//GetPreCode
std::string Main::GetPreCode ()
{
  switch (m_Var["source"].as<char> ())
  {
    case 'd':
      return OpenPreCode ()->Get ();
    case 'c':
      return OpenPreCode ()->GetCache ();
    case 'f':
      return GetFreshPreCode (m_Var["url"].as<std::string> ());
  }
  throw Err ("Invalid source mode");
}//GetPreCode


//OpenPreCode
std::auto_ptr<PreCode> Main::OpenPreCode ()
{
  return std::auto_ptr<PreCode> (new PreCode (
    m_Var["url"].as<std::string> (),
    boost::posix_time::seconds (m_Var["delay"].as<long> ()),
    m_Var["cache"].as<std::string> (),
    m_Var["mutex"].as<std::string> ()));
}//OpenPreCode


//GetOutdated
std::string Main::GetOutdated ()
{
  if (OpenPreCode ()->IsOutdated ()) return "YES";
  return "NO";
}//GetOutdated


//GetUpdate
std::string Main::GetUpdate ()
{
  OpenPreCode ()->Update ();
  return "";
}//GetUpdate


//ShowSyntax
std::string Main::ShowSyntax () const
{
  std::ostringstream O;
  O<<
    "########################################\n"
    "##               bkoder               ##\n"
    "##     Burger King Code Generator     ##\n"
    "########################################\n"
    "## Code: plocha (2012) Idea: Odmastah ##\n"
    "##  Still chilling in the DangerZone  ##\n"
    "########################################\n"
    "\n"
    "Features:\n"
    " - code extraction\n"
    " - cache system\n"
    " - interprocess communication: no conflicts on simultaneous cache\n"
    "   accesses by several bkoder processes\n"
    ;
  O<<GetSyntax ();
  return O.str ();
}//ShowSyntax


//GetSyntax
po::options_description Main::GetSyntax ()
{
  po::options_description General ("General");
  General.add_options ()
    ("help,h", po::value<bool> ()
      ->default_value (false)->implicit_value (true),
      "prints this info page")
    ("action,a", po::value<char> ()->default_value ('f'),
      "defines what to do.\n"
      "values:\n"
      " f: \tprints a full code\n"
      " p: \tprints the pre code\n"
      " n: \tprints a code number\n"
      " i: \tprints whether the cache is outdated\n"
      " u: \tupdates the cache\n"
      " c: \tprints the creation date of the current cache value\n"
      " e: \tprints the expiry of the current cache value\n")
    ("source,s", po::value<char> ()->default_value ('d'),
      "defines the source of the pre code\n"
      "values:\n"
      " d: \tdynamic mode. Uses the cache value if it is not outdated. "
        "Otherwise gets the new pre code and saves it to cache\n"
      " c: \tcache mode. Returns cache value although it is outdated\n"
      " f: \tfresh mode. Returns a fresh code\n")
    ("mutex", po::value<std::string> ()->default_value ("R3W3"),
      "mutex name");

  po::options_description Paths ("Paths");
  Paths.add_options ()
    ("log", po::value<std::string> (), "logfile path for errors")
    ("cache", po::value<std::string> ()->default_value (".bk-cache"),
      "path for cache file");

  po::options_description Site ("Site specific");
  Site.add_options ()
    ("delay", po::value<long> ()->default_value (86400),
      "delays the expiry in seconds. By default the expiry is on the second "
      "day of month\n")
    ("url", po::value<std::string> ()->
      default_value ("https://www.bk-feedback-de.com/"),
      "survey url");

  po::options_description All ;
  All.add (General).
      add (Paths).
      add (Site);

  return All;
}//GetSyntax
