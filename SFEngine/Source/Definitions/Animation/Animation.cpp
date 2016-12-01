#include "../../Headers/Animation/Animation.h"
namespace Engine
{
  //NEW
  void Animation::Update(double delta) {

  }
  void Animation::Play() {
    m_isPaused = false;
    if (!m_isRendered) {
      m_isRendered = true;
      m_currentFrame = 0;
    }
  }

  void Animation::SerializeOut(std::ostream &out) {

  }

  void Animation::Pause() {
    m_isPaused = true;
  }
  void Animation::Stop() {
    m_isRendered = false;
    m_isPaused = true;
  }
  void Animation::Move(float x, float y) {
    sprite.move(x, y);
  }
  void Animation::Move(const sf::Vector2f &pos) {
    sprite.move(pos);
  }
  void Animation::SetPosition(float x, float y) {
    sprite.setPosition(x, y);
  }
  void Animation::SetPosition(const sf::Vector2f &pos) {
    sprite.setPosition(pos);
  }
  void Animation::SetFrameTime(double fTime) {
    m_frameTime = fTime;
  }
  sf::Sprite* Animation::GetSprite() {
    return &sprite;
  }
  //OLD
  void Animation::Render() {
    if (m_isRendered) {
      //sprite.setTextureRect(m_frames[m_currentFrame]);
      Render::RenderSprite(&sprite);
    }
  }
  void Animation::TickUpdate(const double& delta)
  {
    if (!m_isPaused)
    {
      m_currentTime += delta;
      // if current time is bigger then the frame time advance one frame
      if (m_currentTime >= m_frameTime)
      {
        // reset time, but keep the remainder
        //m_currentTime = m_currentTime - m_frameTime;
        m_currentTime = 0;

        m_currentFrame += 1;
        m_currentFrame %= m_frames.size();

        //auto frame = m_frames[m_currentFrame];

        //std::cerr << "Frame #" << m_currentFrame << " - (" << frame.left << ", " << frame.top << ", " << frame.height << ", " << frame.width << ")" << std::endl;

        // get next Frame index
        //if (m_currentFrame + 1 < GetSize())
        //  m_currentFrame++;
        //else
        //{
        //  // animation has ended
        //  m_currentFrame = 0; // reset to start


        //}
        // set the current frame, not reseting the time
      }
    }

    sprite.setTextureRect(m_frames[m_currentFrame]);
  }
  void Animation::OnShutDown() {}

  void Animation::AddFrame(sf::IntRect rect)
  {
    m_frames.push_back(rect);
  }
  void Animation::RequestSpriteSheet(const std::string Filepath, const std::string ID) {
    m_texture;
    ResourceManager->RequestTexture(Filepath, ID,
                                    [this](std::shared_ptr<sf::Texture> t, const std::string &s) {this->SetSpriteSheet(t, s); }
    );
  }
  void Animation::SetSpriteSheet(std::shared_ptr<sf::Texture> tex, const std::string &ID) {
    sprite.setTexture(*tex.get());
    m_texture = tex;
  }

  std::shared_ptr<sf::Texture> Animation::GetSpriteSheet() const {
    return m_texture;
  }

  std::size_t Animation::GetSize() const
  {
    return m_frames.size();
  }

  const sf::IntRect& Animation::GetFrame(std::size_t n) const
  {
    return m_frames[n];
  }

}