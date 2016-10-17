#include "Damage.h"


int Damage::size = 30;
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
