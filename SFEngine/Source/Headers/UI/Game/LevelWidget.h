#ifndef SFENGINE_UI_LEVEL_WIDGET_H
#define SFENGINE_UI_LEVEL_WIDGET_H

#include "../../Globals/GlobalHooks.h"

//Obviously, we only want to compile this in if we are building the engine with the editor
#ifdef WITH_EDITOR

#include "../../Level/Level.h"
#include "../Widget.h"
#include "../Text/TextLabel.h"

namespace Engine
{

  namespace UI
  {

    class UILayer;
    class WidgetHelper;

    class LevelWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<LevelWidget> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Font> _Font);

      void GenerateEmptyLevel(std::uint32_t NumTilesWide, std::uint32_t NumTilesHigh);
      void ShowGridLines(bool show);


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
      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;
      virtual void Resize(const sf::Vector2f &Size) override;
      virtual void ResetAppearance() override;


      ~LevelWidget() = default;
    protected:
      LevelWidget();

      bool IsShowingGridlines;

      //sizes in terms of the number of tiles
      std::uint32_t LevelWidth = 0;
      std::_Uint2_t LevelHeight = 0;
      std::shared_ptr<Level> Level;

      std::shared_ptr<sf::Font> Font;
    };

  }

}

#endif

#endif
