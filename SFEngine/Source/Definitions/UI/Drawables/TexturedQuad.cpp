#include "../../../Headers/UI/Drawables/Drawables.h"

namespace Engine
{

  namespace UI
  {
    TexturedQuad::TexturedQuad(Drawable *Container)
      : Drawable()
    {
      if (!Container)
        throw (Engine::Exception(EXCEPTION_MESSAGE("Container is NULL")));

      DrawBounds.ForceRegion(Container->DrawBounds.GlobalBounds);
    }

    TexturedQuad::~TexturedQuad()
    {

    }

    void TexturedQuad::TickUpdate(const double &Delta)
    {

    }

    void TexturedQuad::Render(std::shared_ptr<sf::RenderTexture> Target)
    {
      //Ensure the view is within the region defined by DrawBounds::GlobalBounds
      ForceWithinRegion(DrawBounds.GlobalBounds, DrawBounds);

      //Set the texture rect based on the bounds
      DrawBounds.DrawQuad.setTextureRect(TextureRegion);
      Target->draw(DrawBounds.DrawQuad);
    }

    void TexturedQuad::Resize(const sf::Vector2f &Size)
    {
      sf::FloatRect Region = { DrawBounds.DrawQuad.getPosition(), Size };
      DrawBounds.ForceRegion(Region);
    }

  }

}
