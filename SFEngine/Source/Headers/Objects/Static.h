#ifndef SFENGINE_OBJECTS_STATIC_H
#define SFENGINE_OBJECTS_STATIC_H

#include "Level\LevelObject.h"

namespace Engine
{

  class StaticLevelObject : public LevelObject
  {
  public:


  protected:

  };

  class RepeatedStaticObject : public LevelObject
  {
  public:
    RepeatedStaticObject(std::shared_ptr<LevelObject> ToRepeat, unsigned int NumRepetitions,
                         const std::vector<sf::Vector2f> &Positions);
    RepeatedStaticObject(const RepeatedStaticObject &) = delete;
    ~RepeatedStaticObject();

    void TickUpdate(const double &delta)                     override final;
    void Render(std::shared_ptr<sf::RenderTarget> Target)    override final;
    void ScriptInit()                                        override final;
    void PhysicsUpdate()                                     override final;
    void OnShutDown()                                        override final;
    void SerializeOut(std::ofstream &out)                    override final;
    void SerializeIn(std::ifstream &in)                      override final;
    void SetPosition(const sf::Vector2f &pos)                override final;
    void SetSize(const sf::Vector2f &size)                   override final;
    void SetTexture(std::shared_ptr<sf::Texture> mytexture)  override final;
    void SetTextureRect(sf::IntRect myRect)                  override final;

    static void BindScriptMethods(chaiscript::ModulePtr module);
  protected:

    std::shared_ptr<LevelObject> m_RepeatedObject;
    sf::VertexArray m_RepeatedVertices;
    std::shared_ptr<sf::Texture> m_RepeatedTexture;
  };

}

#endif
