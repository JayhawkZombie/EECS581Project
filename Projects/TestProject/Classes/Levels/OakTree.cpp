#include "OakTree.h"

OakTreeLevel::OakTreeLevel()
  : BasicLevel({ 50 * 16, 50 * 16 }, { 28 * 16, 18 * 16, 9 * 16, 9 * 16 })
{

}

OakTreeLevel::OakTreeLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  : BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{
}

void OakTreeLevel::TickUpdate(const double & delta)
{
}

void OakTreeLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
}
