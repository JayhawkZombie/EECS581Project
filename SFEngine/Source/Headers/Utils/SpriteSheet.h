#ifndef SFENGINE_SPRITE_SHEET_H
#define SFENGINE_SPRITE_SHEET_H

#include "BasicIncludes.h"

namespace Engine
{

  class SpriteSheet
  {
  public:
    SpriteSheet();
    SpriteSheet(const SpriteSheet &sheet);

    ~SpriteSheet();

    void SetTexture(SharedTexture tex);
    SharedTexture GetTexture() const;

    virtual void SerializeIn(std::ifstream &in);
    virtual void SerializeOut(std::ofstream &out);

    void AddFrame(const sf::IntRect &frame);
    void EvenlyDivideFrames(std::uint32_t frameWidth, std::uint32_t frameHeight);

    std::shared_ptr<sf::Sprite> GetSprite(std::size_t index);

  private:
    SharedTexture Texture;
    std::vector<sf::IntRect> Frames;

    std::vector<std::shared_ptr<sf::Sprite>> Sprites;

    std::uint32_t TextureWidth;
    std::uint32_t TextureHeight;

  };

}

#endif
