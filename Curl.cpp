#include "Curl.hpp"

//Curl
Curl::Curl ()
{
  static bool IsCurlInit = false;
  if (!IsCurlInit && curl_global_init (CURL_GLOBAL_ALL))
    throw Err ("Could not init libcurl");
  IsCurlInit = true;
  m_Handle = curl_easy_init ();
  if (!m_Handle) throw Err ("Could not start easy session");
  Set (CURLOPT_SSL_SESSIONID_CACHE, 0);
  Set (CURLOPT_COOKIEFILE, ""); //enable cookies
}//Curl


//~Curl
Curl::~Curl ()
{
  curl_easy_cleanup (m_Handle);
}//~Curl


//SetPost
void Curl::SetPost (std::vector<std::pair<std::string, std::string> > Data)
{
  Set (CURLOPT_POST, 1);
  std::string End;
  for (size_t i = 0; i != Data.size (); i++)
  {
    if (i) End += "&";
    End += Encode (Data[i].first) + "=";
    End += Encode (Data[i].second);
  }
  Set (CURLOPT_COPYPOSTFIELDS, End.c_str ());
}//SetPost


//Perform
std::string Curl::Perform ()
{
  std::string Content;
  Set (CURLOPT_WRITEFUNCTION, GetBuf);
  Set (CURLOPT_WRITEDATA, &Content);
  if (curl_easy_perform (m_Handle)) throw Err ("There is a http error");
  return Decode (Content);
}//Perform


//SetHost
void Curl::SetHost (std::string Host)
{
  m_Host = Host;
}//SetHost


//SetPath
void Curl::SetPath (std::string Url)
{
  Set (CURLOPT_URL, (m_Host + Url).c_str ());
}//SetPath


//Encode
std::string Curl::Encode (std::string Var) const
{
  char *Buf = curl_easy_escape (m_Handle, Var.c_str (), 0);
  if (!Buf) throw Err ("Could not encode the given string");
  Var = Buf;
  curl_free (Buf);
  return Var;
}//Encode


//Decode
std::string Curl::Decode (std::string Var) const
{
  int EndSize;
  char *Buf = curl_easy_unescape (m_Handle, Var.c_str (), 0, &EndSize);
  if (!Buf) throw Err ("Could not decode the given string");
  Var.assign (Buf, EndSize);
  curl_free (Buf);
  return Var;
}//Decode


//GetContent
size_t Curl::GetBuf (void *Buf, size_t Size, size_t Multi, void *Target)
{
  reinterpret_cast<std::string *> (Target)->
    append (reinterpret_cast<char *> (Buf), Size * Multi);
  return Size * Multi;
}//GetContent
