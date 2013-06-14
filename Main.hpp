//blah blah blargh

#pragma once

#include <iostream>
#include "boost/program_options.hpp"

#include "PreCode.hpp"
#include "NumCode.hpp"
#include "MassErrLog.hpp"

struct Main
{
  void SetOpt (int argc, char *argv[]);
  std::string Do ();
  void WriteLog (Err Msg);

  private:
  
  std::string GetPreCode ();
  std::auto_ptr<PreCode> OpenPreCode ();
  std::string GetOutdated ();
  std::string GetUpdate ();
  std::string ShowSyntax () const;

  static boost::program_options::options_description GetSyntax ();

  boost::program_options::variables_map m_Var;
};
