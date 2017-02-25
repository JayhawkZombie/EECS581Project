#ifndef SFENGINE_RENDER_H
#define SFENGINE_RENDER_H

#include <SFML\Graphics.hpp>
#include <cassert>

#include "../Lights/GenericLightSource.h"
#include "../Lights/GlobalLightSource.h"
#include <vector>

namespace Engine
{
  namespace Render
  {
    struct RenderSettings {
      float Brightness;
      float Contrast;
      float Gamma;
      sf::Color BGClearColor = sf::Color::Black;
      int PostProcess;
      sf::Color HueShift;
      sf::RenderTexture *texture;
    };

    sf::FloatRect DefaultBounds();

    void RenderText(const sf::Text *text);
    void RenderText(const sf::Text *text, const sf::FloatRect &bounds);
    
    void RenderVertices(const sf::VertexArray *arr);
    void RenderVertices(const sf::VertexArray *arr, const sf::FloatRect &bounds);

    void RenderShape(const sf::Shape *shape);
    void RenderShape(const sf::Shape *shape, const sf::FloatRect &bounds);

    void RenderSprite(const sf::Sprite *spr);
    void RenderSprite(const sf::Sprite *spr, const sf::FloatRect &bounds);

    void RenderSFDrawable(const sf::Drawable *drawable);
    void RenderSFDrawable(const sf::Drawable *drawable, const sf::FloatRect &bounds);

    void RenderVertexArrayVector(const std::vector<sf::VertexArray> &arr);

    void RenderVertexArray(const sf::VertexArray &arr);

    void SecondPassRender();
    void ClearRender();

    void __Set__Window(sf::RenderWindow *window);
    void __Create__ViewPanel(const sf::FloatRect &bounds);
    void __Set__Core__Shaders(sf::Shader *frag, sf::Shader *vert);
    void __Set__Render__States(const sf::RenderStates &states);
    void __Set__Render__Settings(const RenderSettings &settings);
    void AddPostProcessShader(sf::Shader *shader);
    void AddLightSource(const GenericLightSource &light);
    void AddGlobalLight(const GlobalLightSource &light);
  }
}


#endif
