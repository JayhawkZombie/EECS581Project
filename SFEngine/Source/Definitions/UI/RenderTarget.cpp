#include "../../Headers/UI/RenderTarget.h"

namespace Engine
{
  RenderTarget::RenderTarget()
  {
    DrawBounds = Render::DefaultBounds();
  }

  RenderTarget::RenderTarget(std::shared_ptr<sf::Drawable> item)
  {
    drawitem.reset();
    drawitem = item;
  }

  RenderTarget::RenderTarget(const RenderTarget &tgt)
  {
    drawitem = tgt.drawitem;
    DrawBounds = tgt.DrawBounds;
  }

  RenderTarget::~RenderTarget()
  {
    /**
     * Reset each item, to cause the refernce count to go to zero and 
     * destroy the item
     */
    
  }

  void RenderTarget::SetDrawable(std::shared_ptr<sf::Drawable> item)
  {
    drawitem.reset();
    drawitem = item;
  }

  void RenderTarget::SetDrawBounds(const sf::FloatRect &rect)
  {
    DrawBounds = rect;
  }

  void RenderTarget::Render() const
  {
    if (drawitem)
      Render::RenderSFDrawable(drawitem.get());
  }
}
