#include "../../../Headers/UI/Draggables/DraggableTile.h"
#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {
    std::shared_ptr<DraggableTile> DraggableTile::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, std::shared_ptr<sf::Texture> Texture, const sf::IntRect &Frame, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget()) {
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given UILayer is NULL or cannot accept a widget"));
      }
      else if (!Texture) {
        throw InvalidParameter({ ExceptionCause::InvalidObjectUsed },
                               EXCEPTION_MESSAGE("Texture is NULL"));
      }

      try
      {
        std::shared_ptr<DraggableTile> Drag(new DraggableTile);
        Drag->Helper = ThisHelper.lock();
        Drag->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(Drag);

        assert(Drag->Helper.lock() && Drag->MyLayer.lock());
        //Set up the tile
        Drag->Outline.setPosition(Position);
        Drag->Outline.setSize(Size);
        Drag->Outline.setTexture(Texture.get());
        Drag->Outline.setTextureRect(Frame);
        Drag->GlobalWidgetBounds.ForceRegion({ Position, Size });

        Drag->RenderState.texture = Texture.get();

        float FrameLeft = Position.x;
        float FrameTop = Position.y;
        float ScaleX = Size.x / Texture->getSize().x; //Scale the amount of width/height added to account for the texture being
        //larger/smaller than the target area
        float ScaleY = Size.y / Texture->getSize().y;

        float TexLeft =  static_cast<float>(Frame.left);
        float TexTop = static_cast<float>(Frame.top);
        float TexRight = static_cast<float>(Frame.left) + static_cast<float>(Frame.width);
        float TexBottom = static_cast<float>(Frame.top) + static_cast<float>(Frame.height);

        //Create the edges
        /**
        * _____________
        * |           |
        * |           |
        * |           |
        * |___________|
        */
        Drag->Verts[0].texCoords = { static_cast<float>(Frame.left), static_cast<float>(Frame.top) };
        Drag->Verts[1].texCoords = { static_cast<float>(Frame.left) + static_cast<float>(Frame.width), static_cast<float>(Frame.top) };
        Drag->Verts[2].texCoords = { static_cast<float>(Frame.left) + static_cast<float>(Frame.width), static_cast<float>(Frame.top) + static_cast<float>(Frame.height) };
        Drag->Verts[3].texCoords = { static_cast<float>(Frame.left), static_cast<float>(Frame.top) + static_cast<float>(Frame.height) };

        Drag->Verts[0].position = Position;
        Drag->Verts[1].position = { Position.x + Size.x, Position.y };
        Drag->Verts[2].position = { Position.x + Size.x, Position.y + Size.y };
        Drag->Verts[3].position = { Position.x, Position.y + Size.y };

        Drag->Outline.setFillColor(sf::Color::Transparent);
        Drag->Outline.setOutlineColor(sf::Color::Yellow);
        Drag->Outline.setOutlineThickness(-1);

        return Drag;
      }
      catch (std::exception &err)
      {
        std::cerr << "Unable to properly construct a widget\n:" << err.what() << std::endl;


        throw ConstructionException({ ExceptionCause::ConstructionError, ExceptionCause::IDGenerationError },
                                    EXCEPTION_MESSAGE("Unable to generate ID for DraggableTile"));
      }


    }

    DraggableTile::DraggableTile()
      : DraggableBase()
    {
      CanBeDragged = true; //Enable dragging
    }

    void DraggableTile::Move(const sf::Vector2f &Delta)
    {
      DraggableBase::Move(Delta);

      Verts[0].position += Delta;
      Verts[1].position += Delta;
      Verts[2].position += Delta;
      Verts[3].position += Delta;

      Outline.move(Delta);
    }

    void DraggableTile::ConsumeEvent(const InputEvent &IEvent) 
    {
      DraggableBase::ConsumeEvent(IEvent);


    }
    void DraggableTile::OnFocusGained(const FocusChangeEvent &FEvent) 
    {
      DraggableBase::OnFocusGained(FEvent);

      Outline.setFillColor(sf::Color::Red);
    }

    void DraggableTile::OnFocusLost(const FocusChangeEvent &FEvent) 
    {
      DraggableBase::OnFocusLost(FEvent);

      Outline.setOutlineColor(sf::Color::Yellow);
    }

    void DraggableTile::OnKeyPress(const InputEvent &IEvent) 
    {
      DraggableBase::OnKeyPress(IEvent);

    }

    void DraggableTile::OnKeyRelease(const InputEvent &IEvent) 
    {
      DraggableBase::OnKeyRelease(IEvent);

    }

    void DraggableTile::OnMousePress(const InputEvent &IEvent) 
    {
      DraggableBase::OnMousePress(IEvent);

    }

    void DraggableTile::OnMouseRelease(const InputEvent &IEvent) 
    {
      DraggableBase::OnMouseRelease(IEvent);
    }

    void DraggableTile::OnMouseScroll(const InputEvent &IEvent) 
    {
      DraggableBase::OnMouseScroll(IEvent);

    }

    void DraggableTile::OnMouseOver(const InputEvent &IEvent) 
    {
      DraggableBase::OnMouseOver(IEvent);

      Outline.setOutlineColor(sf::Color::Magenta);
      DEBUG_ONLY std::cerr << "Widget ID : " << WidgetID << " MouseOver" << std::endl;
    }

    void DraggableTile::OnMouseLeave(const InputEvent &IEvent) 
    {
      DraggableBase::OnMouseLeave(IEvent);

      Outline.setOutlineColor(sf::Color::Yellow);
      DEBUG_ONLY std::cerr << "Widget ID : " << WidgetID << " MouseLeave" << std::endl;
    }

    void DraggableTile::OnMouseMove(const InputEvent &IEvent) 
    {
      DraggableBase::OnMouseMove(IEvent);


    }

    void DraggableTile::OnDragBegin(const InputEvent &IEvent) 
    {
      DraggableBase::OnDragBegin(IEvent);

      Outline.setOutlineColor(sf::Color::Red);
    }

    void DraggableTile::OnDragEnd(const InputEvent &IEvent) 
    {
      DraggableBase::OnDragEnd(IEvent);

      Outline.setOutlineColor(sf::Color::Yellow);
    }

    void DraggableTile::OnDragContinue(const InputEvent &IEvent) 
    {
      DraggableBase::OnDragContinue(IEvent);

      sf::Vector2f dMovement = sf::Vector2f{ IEvent.CurrentMousePosition - IEvent.PreviousMousePosition };
      Outline.move(dMovement);

      Verts[0].position += dMovement;
      Verts[1].position += dMovement;
      Verts[2].position += dMovement;
      Verts[3].position += dMovement;
    }

    void DraggableTile::TickUpdate(const double &delta) 
    {
      DraggableBase::TickUpdate(delta);

    }

    void DraggableTile::Render(std::shared_ptr<sf::RenderTexture> &Texture) 
    {
      DraggableBase::Render(Texture);
      Texture->draw(Outline);
      Texture->draw(Verts, RenderState);
    }

  }

}
