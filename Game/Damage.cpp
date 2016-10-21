#include "Damage.h"


int Damage::size = 31;
Damage::Damage()
{
  for (int i = 0; i < Damage::size; i++)
  {
    content[i] = 0;
  }
}


Damage::~Damage()
{
}

void Damage::setValue(int index, int value)
{
  if (index > Damage::size)
  {
    std::cout << "Went outside the bounds of the array!";
    return;
  }
  content[index] = value;
  return;
}