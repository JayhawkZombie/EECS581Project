#include "../../../Headers/UI/Drawables/Drawables.h"

namespace Engine
{

  namespace UI
  {
    
    void DrawableQuad::ForceRegion(const sf::FloatRect &Region)
    {
      EDITOR_ONLY_CODE_BEGIN
        BLCorner.setPosition({ Region.left,                Region.top + Region.height }); BLCorner.setSize({ Region.width, Region.height });
        BRCorner.setPosition({ Region.left + Region.width, Region.top + Region.height }); BRCorner.setSize({ Region.width, Region.height });
        TLCorner.setPosition({ Region.left,                Region.top });                 TLCorner.setSize({ Region.width, Region.height });
        TRCorner.setPosition({ Region.left + Region.width, Region.top });                 TRCorner.setSize({ Region.width, Region.height });
      EDITOR_ONLY_CODE_END

      LeftSide[0].position   = { Region.left,                Region.top + Region.height }; LeftSide[1].position   = { Region.left,                Region.top };
      TopSide[0].position    = { Region.left,                Region.top };                 TopSide[1].position    = { Region.left + Region.width, Region.top };
      RightSide[0].position  = { Region.left + Region.width, Region.top };                 RightSide[1].position  = { Region.left + Region.width, Region.top + Region.height };
      BottomSide[0].position = { Region.left + Region.width, Region.top + Region.height }; BottomSide[1].position = { Region.left,                Region.top + Region.height };

      GlobalBounds = Region;
      RelativeTo = RelativeSpace::ToScreen;
      DrawView = MakeView(Region);
      DrawQuad.setPosition({ Region.left, Region.top }); 
      DrawQuad.setSize({ Region.width, Region.height });
    }

    
    void InteractQuad::ForceRegion(const sf::FloatRect &Region)
    {
      GlobalBounds = Region;
    }

    
    void TextureSource::SetRenderView(const sf::FloatRect &Rect)
    {
      if (Type == TextureType::RenderTexture)
        RenderTexture->setView(MakeView(Rect));
      else
        throw Engine::Exception(EXCEPTION_MESSAGE("Texture type is Texture, does not have a View"));
    }

    
    Drawable::Drawable()
    {
      DrawBounds.GlobalBounds = { 0,0,0,0 };
      DrawBounds.RelativeTo = RelativeSpace::ToScreen;
    }

    
    Drawable::~Drawable()
    {}

    
    void Drawable::Render(std::shared_ptr<sf::RenderTexture> Target)
    {
      EDITOR_ONLY_CODE_BEGIN
        Target->draw(DrawBounds.TLCorner);
        Target->draw(DrawBounds.TRCorner);
        Target->draw(DrawBounds.BRCorner);
        Target->draw(DrawBounds.BLCorner);
      EDITOR_ONLY_CODE_END
    }

    
    void Canvas::Render(const sf::Drawable *Item)
    {
      if (!Item)
        throw Engine::Exception(EXCEPTION_MESSAGE("Item is NULL"));

      DrawTexture->setView(MakeView(DrawRegion));
      DrawTexture->draw(*Item, State);
    }



    /**************************************************************************************
    *
    *                   NON-CLASS FUNCTIONS
    *
    ***************************************************************************************/

    /**
    *  Position the item within the GlobalBounds of the Drawable passed
    */
    
    void PlaceRelativeTo(const sf::Vector2f &Position, const sf::FloatRect &GlobalBounds, Drawable *Item)
    {
      sf::FloatRect Bounds = GlobalBounds;
      Bounds.left = Position.x;
      Bounds.top = Position.y;

      Item->DrawBounds.ForceRegion(Bounds);
      Item->InteractBounds.ForceRegion(Bounds);
    }


    /**
    *  Force the sf::View variable in Drawables class to fit within the specified area
    *    THIS WILL NOT ALTER THE REST OF THE CLASS
    */
    
    void ForceViewportWithinRegion(const sf::FloatRect &Restriction, DrawableQuad &ToRestrict)
    {
      ToRestrict.DrawView = MakeView(Restriction);
    }

    /**
    *  Force the rendered region of a drawable to be contained within a given region so it
    *  it is not drawn outside of the region
    *  THIS WILL ALTER EVERY DATA VALUE IN THE DRAWABLEQUAD TO FIT WITHIN THE REGION
    */
    
    void ForceWithinRegion(const sf::FloatRect &Restriction, DrawableQuad &ToRestrict)
    {
      ToRestrict.ForceRegion(Restriction);
    }

    /**
    *  Force the region of a drawable to be contained within a given region so it
    *  it is not drawn outside of the region
    */
    
    void ForceWithinRegion(const sf::FloatRect &Restriction, std::shared_ptr<Drawable> &Item)
    {
      Item->DrawBounds.ForceRegion(Restriction);
      Item->InteractBounds.ForceRegion(Restriction);
    }

    /**
    * Create alignment
    *   Forces a change of a rendering bounds to enforce borders
    */
    
    void AlignQuad(const sf::FloatRect &RenderRegion, DrawableQuad *RelativeTo, float BorderLeft, float BorderRight, float BorderTop, float BorderBottom)
    {

    }

    /**
    *  Creates a view to use for changing the viewport
    */
    
    sf::View MakeView(const sf::FloatRect &Bounds)
    {
      sf::View ViewPort;
      sf::FloatRect Region =
      {
        Bounds.left / WindowSize.x,
        Bounds.top / WindowSize.y,
        Bounds.width / WindowSize.x,
        Bounds.height / WindowSize.y
      };

      ViewPort.reset(Bounds);
      ViewPort.setViewport(Region);

      return ViewPort;
    }

    /**
    *  Creates a canvas to draw to
    *  Is rendered to a region provided
    */
    
    std::shared_ptr<Canvas> MakeCanvas(const sf::FloatRect &RenderRegion, const sf::Vector2u CanvasSize)
    {
      std::shared_ptr<Canvas> NewCanvas = std::make_shared<Canvas>();
      NewCanvas->DrawQuad.ForceRegion(RenderRegion);
      NewCanvas->DrawTexture->create(CanvasSize.x, CanvasSize.y);

      return NewCanvas;
    }

    /**
    *  Creates drawable text inside a given region
    *  Text can be rendered relative to a DrawableQuad and with a required border relative to the GlobalBounds of the passed DrawableQuad
    */
    
    std::shared_ptr<DrawableText> CreateText(sf::FloatRect RenderRegion, DrawableQuad *RelativeTo)
    {
      std::shared_ptr<DrawableText> Text = std::make_shared<DrawableText>();
      
      return Text;
    }

    /**
    *  Resize a drawable
    */
    
    void ResizeDrawable(std::shared_ptr<Canvas> &Target)
    {

    }

    /**
    *  Set the viewport of a certain view to be the provided RenderRegion (for clipping)
    */
    
    void SetViewport(sf::View &RenderView, const sf::FloatRect &RenderRegion)
    {

    }

    /**
    *  Draw to the specified canvas
    */
    
    void DrawToCanvas(const sf::Text &RenderText, std::shared_ptr<sf::RenderTarget> &Target)
    {
      
    }
    
    void DrawToCanvas(const sf::Shape *Shape, std::shared_ptr<sf::RenderTarget> &Target)
    {

    }
    
    void DrawToCanvas(const Drawable *Item, std::shared_ptr<sf::RenderTarget> &Target)
    {
      //Initially store the view of the Target, then call for the drawable to render itself to the target
    }

    
    void DrawToCanvas(TexturedQuad &Quad, std::shared_ptr<sf::RenderTarget> &Target)
    {
      
    }








  }

}
