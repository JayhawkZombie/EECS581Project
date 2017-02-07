#ifndef SFENGINE_UI_OBJECT_VIEW_H
#define SFENGINE_UI_OBJECT_VIEW_H

#include "../Engine/BaseEngineInterface.h"
#include "Widget.h"

namespace Engine
{

  namespace UI
  {

    class ObjectView : public WidgetBase
    {
    public:
      static std::shared_ptr<ObjectView> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<BaseEngineInterface> Object);

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnTextEntered(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void MoveTo(const sf::FloatRect &Region) {}

      virtual void AddTextLabel(std::shared_ptr<TextLabel> Label);

      virtual void SetSpriteScale(float originalsize, float desiredsize);

      virtual void TickUpdate(const double &delta);
      virtual void Render(std::shared_ptr<sf::RenderTexture> Target);
      virtual void Move(const sf::Vector2f &Delta);
      virtual void SetAnimationSize(const sf::Vector2f &Size);

      ~ObjectView() = default;
    protected:
      ObjectView();
      std::shared_ptr<BaseEngineInterface> RawObject;
      std::shared_ptr<sf::RenderTexture> ObjectTarget;
      sf::Sprite ObjectSprite;
      sf::RectangleShape Shape;
    };

  }

}

#endif
