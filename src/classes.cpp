#include <unistd.h>
#include <iostream>
#include <string>
#include "hub.h"

using namespace std;


// INPUT SECTION
  void input::segregate()
  {
      int wordCount=0;
      int a=0;
      int b;
      for(int i = 0 ; i < line.size() ; i++)
      {
        if((int)line[i] != 32)
        {
          b = i - a;
          if(wordCount == 0){command += line[i];}
          if(wordCount == 1){parameter1 += line[i];}
        }
        else
        {
          a = i + 1;
          wordCount++;
        }
      }
      return;
  }

  void input::reset()
  {
      line="";
      command="";
      parameter1="";
      //parameter2="";
  }
//-------------------------------------------------


// CD SECTION
  void path::up()
  {
    string temp="";
    output = "";
    bool done=false;
    for(int i = line.size();!done;i--)
    {
      if(line[i] == '/')
      {
        for(int j = 0 ; j < i ; j++)
        {
          temp += line[j];
        }
        done = true;
      }
    }

    done = false;
    for(int i = temp.size();!done;i--)
    {
      if(temp[i] == '/')
      {
        for(int j = 0 ; j <= i ; j++)
        {
          output += line[j];
        }
        done = true;
      }
    }
  }

//-------------------------------------------------

// HELP SECTION

void manual(input input)
{
  if(input.parameter1 == "me")
  {
    cout << endl;
    cout << "help" << endl;
    sleep(1);
    cout << "me" << endl << endl;
  }
  else{cout << "COMMANDS:\n" << "help" << "     " << "exit"<< "     " << "lst" << "     " << "cl - clear screen\n" << "\e[5mshow *name of file*\e[0m to write file content on screen\n" << "\e[5mcd *name of a folder*\e[0m, or \e[5mcd up\e[0m to go out of folder you're in \n" << endl;}
}

//-------------------------------------------------
