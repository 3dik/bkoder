//entry point

#include "Main.hpp"

using namespace std;

void ShowErr (Err Msg);

Main Base;

//main
int main (int argc, char *argv[])
{
  try
  {
    Base.SetOpt (argc, argv);
    cout<<Base.Do ()<<endl;
  }
  catch (Err Msg)
  {
    ShowErr (Msg);
    return 1;
  }
  catch (...)
  {
    ShowErr (Err ());
    throw;
  }
  return 0;
}//main


//ShowErr
void ShowErr (Err Msg)
{
  try
  {
    Base.WriteLog (Msg);
  }
  catch (...)
  {
    Msg.Set ("Could not write to logfile");
  }
  cerr<<"Error: "<<Msg<<std::endl;
}//ShowErr
