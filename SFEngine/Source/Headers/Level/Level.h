#ifndef SFENGINE_LEVEL_H
#define SFENGINE_LEVEL_H

#include "../BasicIncludes.h"
#include "LevelObject.h"
#include "Layer.h"
#include "../Actor/Actor.h"

namespace Engine
{

  class Level : public BaseEngineInterface
  {
  public:
    friend class SFEngine;

    Level();
    Level(const Level &lvl);
    ~Level();

    void TickUpdate(const double &delta);
    void Render();
    void OnShutDown();

    void LoadLevel(const std::string &file);
    bool IsReady() const;

  protected:
    void HandleKeyEvent(const sf::Keyboard::Key &key);


    std::vector<std::shared_ptr<LevelLayer>> Layers;
    std::vector<GenericActor> Actors;

    std::vector<LevelObject> LevelObjects;
    sf::Text LevelWaitingText;

    void ReceiveFont(std::shared_ptr<sf::Font> font, const std::string &ID);
    std::shared_ptr<sf::Font> LevelWaitingFont;

    std::thread LOADER, DRAWER;

    std::vector<std::vector<std::string>> BGLayout;
    std::size_t BGHeight, BGWidth;

    void ReadIDAndPath(std::streampos &pos, std::ifstream &IN);
    void ReadLayout(std::streampos &pos, std::ifstream &IN);
    bool ReadCorrectly;
    bool ReadyToDraw;

    bool ReadyToPlay;

    std::map<std::string, std::shared_ptr<sf::Texture>> IDToTexture;
    std::map<std::string, std::string> MapToTextureID;
    std::vector<std::string> KnownTextures;

    void ReceiveTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID);
    void RequestTextures();
    void DrawToRenderTexture();

    std::shared_ptr<std::condition_variable> COND_VAR;
    std::shared_ptr<std::mutex> MUTEX;

    std::shared_ptr<std::mutex> CHECK_READY_MUTEX;

  };

}

#endif
