#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class input //klasa odpowiedzialna za przyjęcie i przetwarzanie wpisanych poleceń
{
public:
  string line;
  string command;
  string parameter1;

  void segregate(); //metoda dzieląca wpisaną linią na komendą i jej argumenty
  void reset();  //metoda resetująca wartości komend i parametrów
};

class path  //klasa odpowiedzialna za zmiany położenia w systemie plików
{
public:
  string line;
  string output;

  void up();
  void objectively();
};

void manual(input);
