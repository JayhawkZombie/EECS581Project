#include "../../Headers/Utils/SpriteSheet.h"

namespace Engine
{

  SpriteSheet::SpriteSheet()
    : TextureHeight(0), TextureWidth(0)
  {

  }

  SpriteSheet::SpriteSheet(const SpriteSheet &copy)
  {

  }

  SpriteSheet::~SpriteSheet()
  {
    for (auto & spr : Sprites)
      spr.reset();
  }

  void SpriteSheet::SerializeIn(std::ifstream &in)
  {

  }

  void SpriteSheet::SerializeOut(std::ofstream &out)
  {
    //write out the texture itself
    sf::Image image = Texture->copyToImage();
    Encode::Image(image, out);

    //write out the number of frames in the image
    std::size_t framecnt{ 0 };
    framecnt = Frames.size();
    out.write((char *)(&framecnt), sizeof(framecnt));

    //write out each of the frames
    for (auto & frame : Frames)
      Encode::Rect<>(frame, out);
  }

  void SpriteSheet::SetTexture(SharedTexture tex)
  {
    Texture = tex;

    TextureHeight = tex->getSize().y;
    TextureWidth = tex->getSize().x;
  }

  std::shared_ptr<sf::Sprite> SpriteSheet::GetSprite(std::size_t index)
  {
    if (index < Sprites.size())
      return Sprites[index];
  }

  SharedTexture SpriteSheet::GetTexture() const
  {
    return Texture;
  }

  void SpriteSheet::AddFrame(const sf::IntRect &frame)
  {
    Frames.push_back(frame);
  }

  void SpriteSheet::EvenlyDivideFrames(std::uint32_t frameWidth, std::uint32_t frameHeight)
  {
    //Get the # of frames wide
    std::uint32_t NumFramesWide = TextureWidth / frameWidth;
    std::uint32_t NumFramesHigh = TextureHeight / frameHeight;

    for (std::uint32_t i = 0; i < NumFramesWide; ++i) {
      for (std::uint32_t j = 0; j < NumFramesHigh; ++j) {
        sf::IntRect rect;

        rect.left = i * frameWidth;
        rect.top = j * frameHeight;
        rect.height = frameHeight;
        rect.width = frameWidth;

        Frames.push_back(rect);
      } //for j = 0 -> NumFramesHigh
    } //for i = 0 -> NumFramesWide

    //For each of those frames, create a sprite
    for (auto & frame : Frames) {

      Sprites.push_back(std::shared_ptr<sf::Sprite>(new sf::Sprite));
      Sprites.back()->setTexture(*Texture);
      Sprites.back()->setTextureRect(frame);
    }
  }

}
