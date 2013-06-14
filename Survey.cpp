#include "Survey.hpp"

void Welcome (Curl *Site);
void Surveys (Curl *Site);
std::string Finish (Curl *Site);

//GetFreshPreCode
std::string GetFreshPreCode (std::string URL)
{
  Curl Site;
  Site.SetHost (URL);
  Site.Set (CURLOPT_SSL_VERIFYHOST, 0);
  Site.Set (CURLOPT_SSL_VERIFYPEER, 0);
  Welcome (&Site);
  Surveys (&Site);
  return Finish (&Site);
}//GetFreshPreCode


//Welcome
void Welcome (Curl *Site)
{
  //These requests are required to get alle cookies and set the server internal
  //variables of the cookie session
  Site->SetPath ("");
  Site->Perform ();
  Site->SetPath ("Index.aspx?AspxAutoDetectCookieSupport=1");
  Site->Perform ();

  std::vector<std::pair<std::string,std::string> > Post;
  Post.push_back (std::make_pair ("FIP", ""));
  Post.push_back (std::make_pair ("JavaScriptEnabled", "1"));
  Site->SetPath ("Survey.aspx");
  Site->SetPost (Post);
  Site->Perform ();
  Site->Perform ();
}//Welcome


//Surveys
void Surveys (Curl *Site)
{
  std::string Content;
  while (1)
  {
    Content = Site->Perform ();
    try
    {
      Content = Cut<char> (Content, "IoNF\" value=\"", 1, 0);
    }
    catch (Err)
    {
      break; //If the IoNF value could be not found
    }
    Content = Cut<char> (Content, "\"", 0, 0);
    std::vector<std::pair<std::string,std::string> > Post;
    Post.push_back (std::make_pair ("IoNF", Content));
    Site->SetPost (Post);
  }
  //Check for the finish forwarding
  if (Content.find ("Finish.aspx") == std::string::npos)
    throw Err ("No IoNF value");
}//Surveys


//Finish
std::string Finish (Curl *Site)
{
  Site->SetPath ("Finish.aspx");
  std::string Content = Site->Perform ();

  Content = Cut<char> (Content, "ValCode\">", 1, 0);
  Content = Cut<char> (Content, ": ", 1, 0).substr (0, 2);
  return Content;
}//Finish
