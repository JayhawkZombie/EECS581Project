#ifndef SFENGINE_LEVEL_TILE_H
#define SFENGINE_LEVEL_TILE_H


#include "LevelObject.h"
#include "../Actor/Player.h"
#include "../Lights/GenericLightSource.h"
#include "../Lights/GlobalLightSource.h"

namespace Engine
{

  class LevelTile
  {
  public:
    LevelTile(const std::string &ID, std::shared_ptr<sf::Texture> texture, bool animated, std::vector<sf::IntRect> Frames, sf::Vector2f size, sf::Vector2f pos, double duation = 0);
    ~LevelTile();


    virtual void TickUpdate(const double &delta);
    virtual void Render(sf::RenderTexture *texture);

    void CreateSprite();
    void SetPosition(const sf::Vector2f &pos);
    void SetSize(const sf::Vector2f &size);
    void Scale(const sf::Vector2f &scale);
    void SetAnimationDuration(const double &dur);
    void SetTextureFrames(const std::vector<sf::IntRect> &rect);
    void SetTexture(std::shared_ptr<sf::Texture> tex);
    void SetID(const std::string &ID);
    sf::Sprite* GetSpritePtr();

  private:
    std::shared_ptr<sf::Texture> Texture;
    double AnimationDuration;
    std::vector<sf::IntRect> TextureFrames;
    std::string ID;
    sf::Sprite TilesSprite;
    
    sf::Vector2f Position;
    sf::Vector2f Size;

    bool IsAnimated;
    double CurrentFrameDuration;
    double AnimationFrameDelta;
    std::size_t CurrentFrame;
  };

}


#endif
