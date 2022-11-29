#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
  char buff[1024];
  int id = open("mmmm", O_RDONLY);
  int lol = read(id,buff,1024);
  write(1,buff,lol);
  close(id);
  //write(1,buff,1024);
}
