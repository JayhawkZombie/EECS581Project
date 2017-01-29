#include "../../../Headers/UI/Drawables/Drawables.h"

namespace Engine
{

  namespace UI
  {

    ColoredQuad::ColoredQuad(const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      Type = DrawableType::DTBox;
      DrawBounds.ForceRegion({ Position, Size });
      InteractBounds.ForceRegion({ Position, Size });
      RelativeTo = RelativeSpace::ToScreen;

      //Default color
      DrawBounds.DrawQuad.setFillColor(sf::Color(91, 91, 91));
      DrawBounds.DrawQuad.setOutlineColor(sf::Color::White);
      DrawBounds.DrawQuad.setOutlineThickness(-2);
    }

    ColoredQuad::~ColoredQuad()
    {

    }

    void ColoredQuad::TickUpdate(const double &delta)
    {

    }

    void ColoredQuad::Render(std::shared_ptr<sf::RenderTexture> Target)
    {
      auto View = MakeView(DrawBounds.GlobalBounds);
      auto OldView = Target->getView();

      Target->setView(MakeView({ 0, 0, 1200, 900 }));
      Target->setView(View);
      Target->draw(DrawBounds.DrawQuad);

      Target->setView(OldView);
    }

    void ColoredQuad::Resize(const sf::Vector2f &Size)
    {

    }

  }

}
