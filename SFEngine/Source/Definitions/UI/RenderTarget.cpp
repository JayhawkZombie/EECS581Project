#include "../../Headers/UI/RenderTarget.h"

namespace Engine
{
  RenderTarget::RenderTarget()
  {
    drawitem.reset();
    DrawBounds = Render::DefaultBounds();
  }

  RenderTarget::RenderTarget(sf::Drawable *item)
  {
    drawitem.reset(item);
  }

  RenderTarget::~RenderTarget()
  {
    /**
     * Reset each item, to cause the refernce count to go to zero and 
     * destroy the item
     */
    drawitem.release();
  }

  void RenderTarget::SetDrawable(sf::Drawable *item)
  {
    drawitem.reset(item);
  }

  void RenderTarget::SetDrawBounds(const sf::FloatRect &rect)
  {
    DrawBounds = rect;
  }

  void RenderTarget::Render() const
  {
    if (drawitem)
      Render::RenderSFDrawable(*drawitem.get());
  }
}