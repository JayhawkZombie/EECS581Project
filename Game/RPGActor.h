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
  std::string getFilePath() const;
	void setName(std::string name);
  void setFilePath(std::string filePath);
private:
	std::string m_name;
  std::string m_filePath;
};

#endif
