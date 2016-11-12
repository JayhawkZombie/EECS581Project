#ifndef SFENGINE_ANIMATION_H
#define SFENGINE_ANIMATION_H

#include "../BasicIncludes.h"
#include "../Actor/Actor.h"

namespace Engine
{
  class Animation : public BaseEngineInterface
  {
  public:
    //NEW
    Animation() : m_currentFrame(0), m_currentTime(0), m_frameTime(2), m_isPaused(true), m_isRendered(true) {}
    void Update(double deltaTime);
    void Play();
    void Pause();
    void Stop();
    void Move(float x, float y);
    void Move(const sf::Vector2f &pos);
    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f &pos);
    void SetFrameTime(double fTime);
    sf::Sprite* GetSprite();
    //OLD
    friend class SFEngine;
    void AddFrame(sf::IntRect frame);
    void RequestSpriteSheet(const std::string, const std::string id);
    void SetSpriteSheet(std::shared_ptr<sf::Texture> tex, const std::string &ID);
    std::shared_ptr<sf::Texture> GetSpriteSheet() const;
    std::size_t GetSize() const;
    const sf::IntRect& GetFrame(std::size_t n) const;
    void Render();
    void TickUpdate(const double& delta);
    void OnShutDown();
  private:
    bool m_isPaused;
    bool m_isRendered;
    int m_currentFrame;
    double m_currentTime;
    double m_frameTime;
    std::vector<sf::IntRect> m_frames;
    std::shared_ptr<sf::Texture> m_texture;
    sf::Sprite sprite;
  };
}
#endif // SFENGINE_ANIMATION_H#pragma once
