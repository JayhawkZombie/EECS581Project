#ifndef RPG_ACTOR_H
#define RPG_ACTOR_H

#include <string>

#include "../SFEngine/Source/Headers/Actor/Actor.h"
#include "../SFEngine/Source/Headers/Physics/Collider.h"

class RPGActor : public Engine::GenericActor
{
public:
	//constructor/destructor
	RPGActor();
	~RPGActor();

	void AddAnimations();

	//getters/setters
	std::string getName() const;
    std::string getFilePath() const;
	void setName(std::string name);
    void setFilePath(std::string filePath);

	void HandleInputEvent(const Engine::UserEvent &evnt) override;
    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;

private:
	std::string m_name;
    std::string m_filePath;
    sf::Vector2i m_Cell;
	sf::Texture myActor_texture;

    virtual void HandleCollisionWithActor(std::weak_ptr<Engine::Collider2D> Collided);
};

#endif
