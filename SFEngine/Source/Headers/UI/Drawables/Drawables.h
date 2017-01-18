/**
*  Drawable elements
*    These are NOT UI ELEMENTS ON THEIR OWN
*  These contain NO method of handling events triggered, nor can they invoke any
*  These are SOLELY FOR RENDERING
*  Look at Widget.h for the base element widget, which is the base for all UI widgets
*/

#ifndef SFENGINE_DRAWABLES_H
#define SFENGINE_DRAWABLES_H

#include "../../BasicIncludes.h"
#include "../../Globals/GlobalHooks.h"

#include <SFML\Graphics.hpp>

#include <memory>

namespace Engine
{

  namespace UI
  {

/**
* These macros have no functional purpose
* They are simply used to signify the purpose of the method
*   But UI classes MUST use them so that ALL readers can clearly identify the purpose of the methods
*/

    class Drawable;

    enum class RelativeSpace : std::uint32_t
    {
      ToElement = 0,
      ToScreen
    };

    enum class DrawableType : std::uint32_t
    {
      DTBox = 0,
      DTText,
      DTOutline,
      DTGradient,
      DTLayer,
      DTView,
      DTLine,
      DTCustom
    };

    enum class TextureType : std::uint32_t
    {
      Texture,
      RenderTexture
    };

    /**
    *  A drawable Quad (Rectangle)
    *    TopLeft    TopRight
    *     *          *
    *    *          *
    *   *          *
    *  _          _
    * |_|--------|_|
    *  |          |
    *  |          |
    *  |          |
    *  _          _
    * |_|--------|_|
    *  *          *
    *   *          *
    *    *          *
    *  BottomLeft   BottomRight
    *
    *  GlobalBounds Encompases the region set by the 4 corner points
    *  All UI elements must be drawn relative to a DrawableQuad
    *    The viewport region in which they will be rendered is defined as this Quad
    *       The viewport is created by GlobalBounds, so the GlobalBounds should not be relative to an element
    *       but relative to the RenderWindow
    *         If it is, the offset will be calculated before instituting the viewport change
    */
    struct DrawableQuad {
      sf::VertexArray LeftSide = (sf::VertexArray(sf::Lines, 2)), 
        TopSide = (sf::VertexArray(sf::Lines, 2)), 
        RightSide = (sf::VertexArray(sf::Lines, 2)), 
        BottomSide = (sf::VertexArray(sf::Lines, 2));
      sf::FloatRect GlobalBounds;
      sf::View DrawView;
      RelativeSpace RelativeTo;
      sf::RectangleShape DrawQuad;

      void ForceRegion(const sf::FloatRect &Region);
      
      template<typename T>
      void MoveRegion(const sf::Vector2<T> Vec) {
        EDITOR_ONLY_CODE_BEGIN
          TLCorner.setPosition(TLCorner.getPosition() + sf::Vector2f{ Vec });
          TRCorner.setPosition(TRCorner.getPosition() + sf::Vector2f{ Vec });
          BRCorner.setPosition(BRCorner.getPosition() + sf::Vector2f{ Vec });
          BLCorner.setPosition(BLCorner.getPosition() + sf::Vector2f{ Vec });
        EDITOR_ONLY_CODE_END

          GlobalBounds.left += Vec.x;
          GlobalBounds.top += Vec.y;
          DrawQuad.setPosition(DrawQuad.getPosition() + sf::Vector2f{ Vec });
      }

      EDITOR_ONLY sf::RectangleShape TLCorner;
      EDITOR_ONLY sf::RectangleShape TRCorner;
      EDITOR_ONLY sf::RectangleShape BRCorner;
      EDITOR_ONLY sf::RectangleShape BLCorner;
    };

    /**
    *  Quad to define the region in which interaction can occur
    */
    struct InteractQuad {
      sf::FloatRect GlobalBounds;
      RelativeSpace RelativeTo;

      
        void ForceRegion(const sf::FloatRect &Region);
    };

    /**
    *  Texture struct to contain textures used to texture an item
    */
    struct TextureSource {
      TextureType Type;

      
        void SetRenderView(const sf::FloatRect &Rect);

      std::shared_ptr<sf::Texture> Texture;
      std::shared_ptr<sf::RenderTexture> RenderTexture;
    };

    /**
    *  A canvas that can be drawn to
    *  UI elements cannot directly drawn to the screen outside of the class
    *    Elements must be drawn to a canvas, for which a View and RenderTexture are managed
    *    The Canvas can maintain a RenderState, which can be altered
    *  A canvas cannot be interacted with, so they contain no InteractQuad
    *  In the editor, their rendering region can be shown, so they do contain a DrawQuad (if editor is defined, so it is not compiled into release builds)
    */
    struct Canvas {
      std::shared_ptr<sf::RenderTexture> DrawTexture;
      sf::RenderStates State;

      sf::FloatRect DrawRegion;
      void Render(const sf::Drawable *Item);

      EDITOR_ONLY DrawableQuad DrawQuad;
    };

    /**
    *  Base drawable element 
    */
    class Drawable
    {
    public:
      EDITOR_FRIEND
      Drawable();
      virtual ~Drawable();
      virtual void TickUpdate(const double &Delta) = 0;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target);
      virtual void Resize(const sf::Vector2f &Size) = 0;

      DrawableQuad DrawBounds;
      InteractQuad InteractBounds;
      DrawableType Type;
      RelativeSpace RelativeTo;
    };

    class ColoredQuad : public Drawable
    {
    public:
      EDITOR_FRIEND

      ColoredQuad(const sf::Vector2f &Position, const sf::Vector2f &Size);
      virtual ~ColoredQuad();

      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target) override;
      virtual void Resize(const sf::Vector2f &Size) override;
    };

    /**
    *  Drawable text
    *  Can be "attached" to a given element and maintain position as it moved
    */
    class DrawableText : public Drawable
    {
    public:
      EDITOR_FRIEND

      
        DrawableText(Drawable *Container = nullptr);
      
        virtual ~DrawableText();    
        virtual void TickUpdate(const double &Delta) override;    
        virtual void Render(std::shared_ptr<sf::RenderTexture> &Target) override;
        virtual void Resize(const sf::Vector2f &Size) override;

      
      std::string RawText;
      sf::Text RenderText;
      std::shared_ptr<sf::Font> DrawFont;
    };

    /**
    * A textured Quad
    */
    class TexturedQuad : public Drawable
    {
    public:
      EDITOR_FRIEND  
      TexturedQuad(Drawable *Container = nullptr);
      
      virtual ~TexturedQuad();
      virtual void TickUpdate(const double &Delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target) override;
      virtual void Resize(const sf::Vector2f &Size) override;

      std::shared_ptr<sf::Texture> DrawTexture;
      
      //Another DrawableQuad for just the textureRect
      sf::IntRect TextureRegion;
    };

    /**
    *  Position the item within the GlobalBounds of the Drawable passed
    */
    
      void PlaceRelativeTo(const sf::Vector2f &Position, const sf::FloatRect &GlobalBounds, Drawable *Item);

    /**
    *  Force the sf::View variable in Drawables class to fit within the specified area
    */
    
      void ForceViewportWithinRegion(const sf::FloatRect &Restriction, DrawableQuad &ToRestrict);

    /**
    *  Force the rendered region of a drawable to be contained within a given region so it
    *  it is not drawn outside of the region
    */
    
      void ForceWithinRegion(const sf::FloatRect &Restriction, DrawableQuad &ToRestrict);

    /**
    *  Force the region of a drawable to be contained within a given region so it
    *  it is not drawn outside of the region
    */
    
      void ForceWithinRegion(const sf::FloatRect &Restriction, std::shared_ptr<Drawable> &Item);

    /**
    * Create alignment
    *   Forces a change of a rendering bounds to enforce borders
    */
    
      void AlignQuad(const sf::FloatRect &RenderRegion, DrawableQuad *RelativeTo, float BorderLeft = 0.f, float BorderRight = 0.f, float BorderTop = 0.f, float BorderBottom = 0.f);

    /**
    *  Creates a view to use for changing the viewport
    */
    
      sf::View MakeView(const sf::FloatRect &Bounds);

    /**
    *  Creates a canvas to draw to
    *  Is rendered to a region provided
    */
    
      std::shared_ptr<Canvas> MakeCanvas(const sf::FloatRect &RenderRegion, const sf::Vector2u CanvasSize);

    /**
    *  Creates drawable text inside a given region
    *  Text can be rendered relative to a DrawableQuad and with a required border relative to the GlobalBounds of the passed DrawableQuad
    */
    
      std::shared_ptr<DrawableText> CreateText(sf::FloatRect RenderRegion, DrawableQuad *RelativeTo);

    /**
    *  Resize a drawable
    */
    
      void ResizeDrawable(std::shared_ptr<Canvas> &Target);

    /**
    *  Set the viewport of a certain view to be the provided RenderRegion (for clipping)
    */
    
      void SetViewport(sf::View &RenderView, const sf::FloatRect &RenderRegion);

    /**
    *  Draw to the specified canvas
    */
    
      void DrawToCanvas(const sf::Text &RenderTextText, std::shared_ptr<sf::RenderTarget> &Target);
    
      void DrawToCanvas(const sf::Shape *Shape, std::shared_ptr<sf::RenderTarget> &Target);
    
      void DrawToCanvas(const Drawable *Item, std::shared_ptr<sf::RenderTarget> &Target);
    
      void DrawToCanvas(TexturedQuad &Quad, std::shared_ptr<sf::RenderTarget> &Target);
  }

}

#endif
