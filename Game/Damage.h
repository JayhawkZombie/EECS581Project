//Basically passing arrays is frustrating in C++ so Damage is a wrapper for an int array
//length 30
#ifndef DAMAGE_H
#define DAMAGE_H
class Damage
{
public:
  Damage();
  ~Damage();
  int content[30];//feeling risky, making public to save time
  static int size;
};

#endif