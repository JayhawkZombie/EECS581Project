#include "MainCharacter.h"



MainCharacter::MainCharacter()
{
  for (int i = 0; i < 6; i++)
  {
    m_affinity[i] = 0;
  }
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::IncrementAffinity(int index, int value)
{
  if (index < 1 || index>6)//no work done on bad values
  {
    return;
  }
  if (value > 20)
  {
    value = 20;
  }
  else if (value < -20)
  {
    value = -20;
  }
  m_affinity[index] = m_affinity[index] + value;
}

int MainCharacter::getAffinity(int index)
{
  if (index < 1 || index>6)
  {
    return -1;
  }
  else
  {
    return m_affinity[index];
  }
}
void MainCharacter::printAffinities()
{
  std::cout << "fire:    " << m_affinity[0] << "\n";
  std::cout << "water:   " << m_affinity[1] << "\n";
  std::cout << "earth:   " << m_affinity[2] << "\n";
  std::cout << "air:     " << m_affinity[3] << "\n";
  std::cout << "light:   " << m_affinity[4] << "\n";
  std::cout << "dark:    " << m_affinity[5] << "\n";
}