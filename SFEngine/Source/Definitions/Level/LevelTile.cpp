#include "../../Headers/Level/LevelTile.h"

namespace Engine
{


  LevelTile::LevelTile(const std::string &id, std::shared_ptr<sf::Texture> texture, bool animated, std::vector<sf::IntRect> Frames, sf::Vector2f size, sf::Vector2f pos, double duration)
    : TextureFrames(Frames), Texture(texture), ID(id), AnimationDuration(duration), AnimationFrameDelta(duration / Frames.size()), IsAnimated(animated), CurrentFrameDuration(0.f)
  {
    Position = pos;
    Size = size;
    TilesSprite.setTexture(*texture);
  }

  LevelTile::~LevelTile()
  {

  }


  void LevelTile::CreateSprite()
  {
    if (Texture)
      TilesSprite.setTexture(*Texture);
    TilesSprite.setTextureRect(TextureFrames[0]);
  }

  sf::Sprite* LevelTile::GetSpritePtr()
  {
    return &TilesSprite;
  }

  void LevelTile::SetPosition(const sf::Vector2f &pos)
  {
    Position = pos;
    TilesSprite.setPosition(pos);
  }

  void LevelTile::SetSize(const sf::Vector2f &size)
  {
    Size = size;
  }

  void LevelTile::Scale(const sf::Vector2f &scale)
  {
    TilesSprite.scale(scale);
  }

  void LevelTile::SetAnimationDuration(const double &dur)
  {
    AnimationDuration = dur;
    AnimationFrameDelta = dur / (TextureFrames.size() == 0 ? 1 : TextureFrames.size());
  }

  void LevelTile::SetTextureFrames(const std::vector<sf::IntRect> &rect)
  {
    TextureFrames = rect;
  }

  void LevelTile::SetTexture(std::shared_ptr<sf::Texture> tex)
  {
    Texture = tex;
  }

  void LevelTile::SetID(const std::string &id)
  {
    ID = id;
  }


  void LevelTile::TickUpdate(const double &delta)
  {
    if (IsAnimated) {

      CurrentFrameDuration += delta;

      if (CurrentFrameDuration >= AnimationFrameDelta)
        CurrentFrame = (CurrentFrame >= TextureFrames.size() ? 0 : CurrentFrame + 1);

      TilesSprite.setTextureRect(TextureFrames[CurrentFrame]);
    }
  }

  void LevelTile::Render(sf::RenderTexture *texture)
  {
    texture->draw(TilesSprite);
  }

}
