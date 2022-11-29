#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <filesystem>
#include <dirent.h>
#include "hub.h"

using namespace std;

string directory = "/";

string dirsToGo[256];

void read(string path, bool type)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path.c_str());

  if (dir != NULL)
  {
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
      string name = entry->d_name;
      if(entry->d_type == 4)
      {
        if((name != ".")&&(name != ".."))
        {
          cout << name << " " << endl;
          dirsToGo[i] = name;
          i++;
        }
      }
      else
      {
        cout << "\033[31m" << name << " " << "\033[37m" << endl;
      }
    }
    closedir(dir);
  }
  else{cout << "opendir error" << endl;}
}

void get(string name)
{
  bool done = false;
  char buff[1024];
  int id = open(name.c_str(), O_RDONLY);
  while(!done)
  {
    int end = read(id,buff,1024);
    write(1,buff,end);
    if(end < 1024)
    {
      done = true;
    }
  }
  close(id);
}

string truncateToName(string dir)
{
  string output;
  int j;
  for(int i = dir.size() ; i >= 0 ; i--)
  {
    if(output[i] == '/')
    {
      j=i+1;
    }
  }
  for(int i = j ; i < dir.size() ; i++)
  {
    output += dir[i];
  }
  return output;
}

int main()
{
  input input;
  bool out = false; //if user wants to exit
  bool found = false; //if specified file exists on dirsToGo
  read(directory, true);
  cout <<"\033[32m"<< directory << " >>" <<"\033[37m";
  while(!out)
  {
    getline(cin, input.line);
    input.segregate();

    if(input.command == "cd")
    {
      if(input.parameter1 == "up")
      {
        if(directory != "/")
        {
          path curLine;
          curLine.line = directory;
          curLine.up();
          if(curLine.output != ""){  directory = curLine.output;}
          else{directory = "/";}
          read(directory, false); //fill dirsToGo with contents of up dir
        }
        else
        {
          system("clear");
          cout << "nope" << endl;
          sleep(2);
          system("clear");
        }
      }
      else
      {
        for(int i = 0;dirsToGo[i] != "";i++)
        {
          if(input.parameter1 == dirsToGo[i])
          {
            directory += input.parameter1 + "/";
            found = true;
          }
          dirsToGo[i] = "";
        }
        if(!found)
        {
          system("clear");
          cout << "No such folder" << endl;
          sleep(2);
          system("clear");
        }
        read(directory, false);//fill dirsToGo with contents of specified dir
      }
    }
    if(input.command == "help")
    {
      manual(input);
    }
    if(input.command == "lst")
    {
      read(directory, true);
    }
    if(input.command == "cl")
    {
      system("clear");
    }
    if(input.command == "show")
    {
      bool folder = false;
      for(int i = 0;dirsToGo[i] != "";i++)
      {
        if(input.parameter1 == dirsToGo[i])
        {
          system("clear");
          cout << "It's a folder" <<endl;
          sleep(2);
          system("clear");
          folder = true;
        }
      }
      if(folder){read(directory, true);}
      else{get(directory+input.parameter1);}
    }
    if(input.command == "exit"){out = true;}
    input.reset();
    found = false;
    cout <<"\033[32m"<< directory << " >>"<<"\033[37m";
  }
  cout << endl;
  return 0;
}
