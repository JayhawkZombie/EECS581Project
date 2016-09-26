#ifndef SFENGINE_RENDER_TARGET_H
#define SFENGINE_RENDER_TARGET_H

#include "../BasicIncludes.h"

namespace Engine
{
  
  /**
   * A class to contain rendering information
   * Store in here the elements that you wish to be
   * rendered
   * Optionally, it can completely take ownership of the drawable for you
   *   in which case the drawable item will be destroyed upon destruction of the render target
   */
  class RenderTarget 
  {
  public:
    RenderTarget();
    RenderTarget(sf::Drawable *item);
    RenderTarget(const RenderTarget &) = delete;
    ~RenderTarget();

    void Render() const;
    void SetDrawable(sf::Drawable *item);
    void SetDrawBounds(const sf::FloatRect &rect);

  private:
    std::unique_ptr<sf::Drawable> drawitem;
    sf::FloatRect DrawBounds;

  };

}


#endif
