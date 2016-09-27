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
    /**
     * An element which can be rendered automatically by the UIController
     * Create a drawable element, and store it in a shared_ptr
     * Call SetDrawBounds(FloatRect) and pass the rectangular region in which
        said element is supposed to be drawn
     * Call SetDrawable(ptr) and pass the shared ptr to the sf::Drawable to be
        rendered
     */
  public:
    RenderTarget();
    RenderTarget(std::shared_ptr<sf::Drawable> item);
    RenderTarget(const RenderTarget&);
    ~RenderTarget();

    void Render() const;
    void SetDrawable(std::shared_ptr<sf::Drawable> item);
    void SetDrawBounds(const sf::FloatRect &rect);

  private:
    std::shared_ptr<sf::Drawable> drawitem;
    sf::FloatRect DrawBounds;

  };

}


#endif
