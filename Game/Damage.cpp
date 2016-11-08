#include "Damage.h"


int Damage::size = 31;
Damage::Damage()
{
  for (int i = 0; i < Damage::size; i++)
  {
    content[i] = 0;
  }
}
Damage::Damage(Damage inflicted, Damage defense)
{
	for (int i = 0; i < Damage::size; i++)
	{
		if (i == 8)
		{
			this->content[8] = inflicted.content[8];
		}
		if (inflicted.content[i] - defense.content[i] > 0)
		{
			this->content[i] = inflicted.content[i] - defense.content[i];
		}
		else
		{
			this->content[i] = 0;
		}
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