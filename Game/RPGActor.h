#ifndef RPG_ACTOR_H
#define RPG_ACTOR_H

#include <string>
class RPGActor
{
public:
	//constructor/destructor
	RPGActor();
	~RPGActor();

	//getters/setters
	std::string getName() const;
	void setName(std::string name);
private:
	std::string m_name;
};

#endif
