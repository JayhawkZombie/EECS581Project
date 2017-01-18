#ifndef SFENGINE_UI_DRAGGABLE_TILE_H
#define SFENGINE_UI_DRAGGABLE_TILE_H

#include "DraggableBase.h"

namespace Engine
{

  //test struct
  struct TestTile {
    std::vector<sf::VertexArray> Edges;

    std::shared_ptr<sf::Texture> Texture;
  };

  namespace UI
  {

    class DraggableTile : public DraggableBase
    {
    public:
      static std::shared_ptr<DraggableTile> Create(std::shared_ptr<WidgetHelper>, std::shared_ptr<sf::Texture> Texture, const sf::IntRect &Frame, const sf::Vector2f &Position, const sf::Vector2f &Size);

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Texture) override;

      TestTile Tile;
      sf::RectangleShape Outline;
      std::shared_ptr<sf::Texture> TileTexture;

      sf::VertexArray Left = sf::VertexArray(sf::Lines, 2);
      sf::VertexArray Top = sf::VertexArray(sf::Lines, 2);
      sf::VertexArray Right = sf::VertexArray(sf::Lines, 2);
      sf::VertexArray Bottom = sf::VertexArray(sf::Lines, 2);

      sf::VertexArray Verts = sf::VertexArray(sf::Quads, 4);

      sf::RenderStates RenderState;

      virtual ~DraggableTile() = default;
    protected:
      DraggableTile();
    };

  }

}

#endif
