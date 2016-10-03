#ifndef SFENGINE_RESOURCE_MANAGER_H
#define SFENGINE_RESOURCE_MANAGER_H

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>
#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

typedef std::pair<std::string, std::string> DoubleStringPair;

namespace Engine
{
  namespace Resource
  {
    class ResourceManager
    {
    public:
      ResourceManager();
      ResourceManager(const ResourceManager &) = delete;
      ~ResourceManager();

      void RequestTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>)> callback);
      void RequestVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>)> callback);
      void RequestFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>)> callback);
      void RequestFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>)> callback);

      void RequestTextureChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Texture>)> callback);
      void RequestVertexShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>)> callback);
      void RequestFragmentShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>)> callback);
      void RequestFontChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Font>)> callback);

      std::size_t GetSizeOfTexturePool() const;
      std::size_t GetSizeOfVertexShaderPool() const;
      std::size_t GetSizeOfFragmentShaderPool() const;
      std::size_t GetSizeOfFontPool() const;

      void Shutdown();

      void Start();

    private:
      void ThreadMethod();
      void LoadTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>)> cb);
      void LoadFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>)> cb);
      void LoadVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>)> cb);
      void LoadFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>)> cb);

      void CopyFromPushQueue();
      void LoadShadersFromActiveQueues();
      void LoadTexturesFromActiveQueue();
      void LoadFontsFromActiveQueue();

      std::thread LoaderThread;
      bool *ThreadQuit;
      bool *ThreadWorkToDo;
      bool started;

      std::mutex *PushQueueLock;
      std::mutex *ActiveQueueLock;
      std::mutex *LoadLock;
      std::mutex *StorageAccessLock;

      std::condition_variable *WakeUpThread;

      //Oh my, how disgusting
      std::queue <std::pair<DoubleStringPair
                , std::function<void(std::shared_ptr<sf::Texture>)>>> *TextureQueue;

      std::queue<std::pair<DoubleStringPair
                , std::function<void(std::shared_ptr<sf::Shader>)>>> *VertexShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>)>>> *FragmentShaderQueue;

      std::queue<std::pair<DoubleStringPair
                , std::function<void(std::shared_ptr<sf::Font>)>>> *FontQueue;

      std::queue <std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Texture>)>>> *ActiveTextureQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>)>>> *ActiveVertexShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>)>>> *ActiveFragmentShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Font>)>>> *ActiveFontQueue;

      std::map<std::string, std::shared_ptr<sf::Texture>> *Textures;
      std::map<std::string, std::shared_ptr<sf::Shader>> *VertexShaders;
      std::map<std::string, std::shared_ptr<sf::Shader>> *FragmentShaders;
      std::map<std::string, std::shared_ptr<sf::Font>> *Fonts;
    };

  }
}


#endif
