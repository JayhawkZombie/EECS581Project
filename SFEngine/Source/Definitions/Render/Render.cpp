#include "../../Headers/Render/Render.h"
#include <iostream>

namespace
{
  sf::RenderWindow *DrawWindow = nullptr;
  sf::Sprite renderSprite;
  std::vector<sf::Shader *> PostProcessShaders;
  sf::Vector2u WinSize;
  sf::FloatRect ViewPanel;
  sf::RenderStates RenderStates;
  sf::View view;
  sf::Shader *FragmentShader;
  sf::Shader *VertexShader;
  Engine::Render::RenderSettings CoreRenderSettings;
  std::vector<Engine::GenericLightSource> Lights;
  Engine::GlobalLightSource GlobalLight;
}

namespace Engine
{
  namespace Render
  {
    sf::FloatRect DefaultBounds()
    {
      
      return sf::FloatRect(0, 0, WinSize.x, WinSize.y);
    }

    void RenderText(const sf::Text *text)
    {
      RenderText(text, DefaultBounds());
    }

    void RenderText(const sf::Text *text, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(text, bounds);
    }

    void RenderVertices(const sf::VertexArray *arr)
    {
      RenderVertices(arr, DefaultBounds());
    }

    void RenderVertices(const sf::VertexArray *arr, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(arr, bounds);
    }

    void RenderShape(const sf::Shape *shape)
    {
      RenderShape(shape, DefaultBounds());
    }

    void RenderShape(const sf::Shape *shape, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(shape, bounds);
    }

    void RenderSprite(const sf::Sprite *spr)
    {
      RenderSprite(spr, DefaultBounds());
    }

    void RenderSprite(const sf::Sprite *spr, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(spr, bounds);
    }

    void RenderSFDrawable(const sf::Drawable *drawable)
    {
      RenderSFDrawable(drawable, DefaultBounds());
    }

    void RenderSFDrawable(const sf::Drawable *drawable, const sf::FloatRect &bounds)
    {
      if (DrawWindow) {
        __Create__ViewPanel(bounds);

        ViewPanel = sf::FloatRect(
          bounds.left / WinSize.x,
          bounds.top / WinSize.y,
          bounds.width / WinSize.x,
          bounds.height / WinSize.y
        );

        view.reset(bounds);
        view.setViewport(ViewPanel);

        CoreRenderSettings.texture->setActive(true);
        CoreRenderSettings.texture->setView(view);
        CoreRenderSettings.texture->draw(*drawable);
        CoreRenderSettings.texture->setView(CoreRenderSettings.texture->getDefaultView()); 
      }
    }

    void ClearRender()
    {
      CoreRenderSettings.texture->setActive(true);
      CoreRenderSettings.texture->clear();
    }

    void SecondPassRender()
    {
      //Now that every has been drawn to a render texture, draw that one huge texture
      CoreRenderSettings.texture->setActive(true);
      CoreRenderSettings.texture->display();

      FragmentShader->setUniform("BRIGHTNESS", CoreRenderSettings.Brightness);
      FragmentShader->setUniform("CONTRAST", CoreRenderSettings.Contrast);
      FragmentShader->setUniform("SCENE", sf::Shader::CurrentTexture);
      FragmentShader->setUniform("GAMMA", CoreRenderSettings.Gamma);
      FragmentShader->setUniform("POST_PROCESS_EFFECT", CoreRenderSettings.PostProcess);

      FragmentShader->setUniform("GLOBAL_LIGHT", sf::Glsl::Vec4(GlobalLight.GetColor()));
      FragmentShader->setUniform("GLOBAL_LIGHT_INTENSITY", GlobalLight.GetIntensity());

      sf::Sprite spr(CoreRenderSettings.texture->getTexture());

      DrawWindow->draw(spr, FragmentShader);
    }

    void __Set__Window(sf::RenderWindow *window)
    {
      DrawWindow = window;
      if (DrawWindow) {
        WinSize = DrawWindow->getSize();
      }
      
      assert(DrawWindow);
    }


    void __Create__ViewPanel(const sf::FloatRect &bounds)
    {
      ViewPanel = sf::FloatRect(
        bounds.left / WinSize.x,
        bounds.top / WinSize.y,
        bounds.width / WinSize.x,
        bounds.height / WinSize.y
      );

      view.reset(bounds);
      view.setViewport(ViewPanel);
    }

	  void __Set__Core__Shaders(sf::Shader *frag, sf::Shader *vert)
	  {
      VertexShader = vert;
      FragmentShader = frag;
		  
	  }

	  void __Set__Render__States(const sf::RenderStates &states)
	  {
		  RenderStates = states;
	  }

    void __Set__Render__Settings(const RenderSettings &settings)
    {
      CoreRenderSettings.Brightness = settings.Brightness;
      CoreRenderSettings.Contrast = settings.Contrast;
      CoreRenderSettings.HueShift = settings.HueShift;
      CoreRenderSettings.texture = settings.texture;
      CoreRenderSettings.Gamma = settings.Gamma;
      CoreRenderSettings.PostProcess = settings.PostProcess;
    }

    void AddPostProcessShader(sf::Shader *shader)
    {
      PostProcessShaders.push_back(shader);
    }

    void AddLightSource(const GenericLightSource &light)
    {
      Lights.push_back(light);
    }

    void AddGlobalLight(const GlobalLightSource &light)
    {
      GlobalLight = light;
    }
  }
}
