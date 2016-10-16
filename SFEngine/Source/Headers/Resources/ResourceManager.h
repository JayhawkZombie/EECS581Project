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

      void RequestTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
      void RequestVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
      void RequestFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
      void RequestFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);

      void RequestTextureChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
      void RequestVertexShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
      void RequestFragmentShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
      void RequestFontChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);

      std::size_t GetSizeOfTexturePool() const;
      std::size_t GetSizeOfVertexShaderPool() const;
      std::size_t GetSizeOfFragmentShaderPool() const;
      std::size_t GetSizeOfFontPool() const;

      void Shutdown();

      void Start();

    private:
      void ThreadMethod();
      void LoadTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback);
      void LoadFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback);
      void LoadVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);
      void LoadFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback);

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
                , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>> *TextureQueue;

      std::queue<std::pair<DoubleStringPair
                , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *VertexShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *FragmentShaderQueue;

      std::queue<std::pair<DoubleStringPair
                , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>> *FontQueue;

      std::queue <std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>> *ActiveTextureQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *ActiveVertexShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>> *ActiveFragmentShaderQueue;

      std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>> *ActiveFontQueue;

      std::map<std::string, std::shared_ptr<sf::Texture>> *Textures;
      std::map<std::string, std::shared_ptr<sf::Shader>> *VertexShaders;
      std::map<std::string, std::shared_ptr<sf::Shader>> *FragmentShaders;
      std::map<std::string, std::shared_ptr<sf::Font>> *Fonts;
    };

  }
}


#endif
