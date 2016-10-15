#include "../../Headers/Resources/ResourceManager.h"
#include <iterator>

namespace Engine
{
  namespace Resource
  {

    ResourceManager::ResourceManager()
    {
      PushQueueLock = new std::mutex;
      ActiveQueueLock = new std::mutex;
      LoadLock = new std::mutex;
      WakeUpThread = new std::condition_variable;
      StorageAccessLock = new std::mutex;
      ThreadQuit = new bool;
      *ThreadQuit = false;
      ThreadWorkToDo = new bool;
      *ThreadWorkToDo = false;

      started = false;

      VertexShaders = new std::map<std::string, std::shared_ptr<sf::Shader>>;
      FragmentShaders = new std::map<std::string, std::shared_ptr<sf::Shader>>;
      Textures = new std::map<std::string, std::shared_ptr<sf::Texture>>;
      Fonts = new std::map<std::string, std::shared_ptr<sf::Font>>;

      TextureQueue = new std::queue <std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>>;

      FragmentShaderQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

      VertexShaderQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

      FontQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>>;

      ActiveTextureQueue = new std::queue <std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>>;

      ActiveFragmentShaderQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

      ActiveVertexShaderQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>>;

      ActiveFontQueue = new std::queue<std::pair<DoubleStringPair
        , std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>>;
    }

    void ResourceManager::Start()
    {
      if (!started) {
        started = true;
        LoaderThread = std::thread([this]() {this->ThreadMethod(); });
      }
    }

    ResourceManager::~ResourceManager()
    {
      *ThreadQuit = true;
      WakeUpThread->notify_all();
      LoaderThread.join();

      delete ActiveQueueLock;
      delete PushQueueLock;
      delete LoadLock;
      delete WakeUpThread;
      delete StorageAccessLock;
      delete ThreadQuit;
      delete ThreadWorkToDo;

      delete VertexShaders;
      delete FragmentShaders;
      delete Textures;
      delete Fonts;

      delete TextureQueue;
      delete FragmentShaderQueue;
      delete VertexShaderQueue;
      delete FontQueue;


      delete ActiveTextureQueue;
      delete ActiveFragmentShaderQueue;
      delete ActiveVertexShaderQueue;
      delete ActiveFontQueue;
    }

    void ResourceManager::Shutdown()
    {
      std::cerr << "Notifying thread of shutdown request" << std::endl;
      *ThreadQuit = true;
      *ThreadWorkToDo = true;
      WakeUpThread->notify_all();
    }

    void ResourceManager::RequestTexture(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback)
    {
      DoubleStringPair pair(Filepath, ID);
      PushQueueLock->lock();
      TextureQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>(pair, callback));
      PushQueueLock->unlock();
      *ThreadWorkToDo = true;
      WakeUpThread->notify_all();
    }

    void ResourceManager::RequestVertexShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
    {
      DoubleStringPair pair(Filepath, ID);
      PushQueueLock->lock();
      VertexShaderQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(pair, callback));
      PushQueueLock->unlock();
      *ThreadWorkToDo = true;
      WakeUpThread->notify_all();
    }

    void ResourceManager::RequestFragmentShader(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
    {
      DoubleStringPair pair(Filepath, ID);
      PushQueueLock->lock();
      FragmentShaderQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(pair, callback));
      PushQueueLock->unlock();
      *ThreadWorkToDo = true;
      WakeUpThread->notify_all();
    }

    void ResourceManager::RequestFont(const std::string &Filepath, const std::string &ID, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback)
    {
      DoubleStringPair pair(Filepath, ID);
      PushQueueLock->lock();
      FontQueue->push(std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>(pair, callback));
      PushQueueLock->unlock();
      *ThreadWorkToDo = true;
      WakeUpThread->notify_all();
    }

    void ResourceManager::RequestTextureChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Texture>, const std::string &ID)> callback)
    {
      PushQueueLock->lock();

      for (auto it = Info.begin(); it != Info.end(); it++) {
        TextureQueue->push(
          std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Texture>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
      }

      PushQueueLock->unlock();
    }

    void ResourceManager::RequestVertexShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
    {
      PushQueueLock->lock();

      for (auto it = Info.begin(); it != Info.end(); it++) {
        VertexShaderQueue->push(
          std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
      }

      PushQueueLock->unlock();
    }

    void ResourceManager::RequestFragmentShaderChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Shader>, const std::string &ID)> callback)
    {
      PushQueueLock->lock();

      for (auto it = Info.begin(); it != Info.end(); it++) {
        FragmentShaderQueue->push(
          std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Shader>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
      }

      PushQueueLock->unlock();
    }

    void ResourceManager::RequestFontChunk(std::vector<DoubleStringPair> Info, std::function<void(std::shared_ptr<sf::Font>, const std::string &ID)> callback)
    {
      PushQueueLock->lock();

      for (auto it = Info.begin(); it != Info.end(); it++) {
        FontQueue->push(
          std::pair<DoubleStringPair, std::function<void(std::shared_ptr<sf::Font>, std::string ID)>>(DoubleStringPair(it->first, it->second), callback));
      }

      PushQueueLock->unlock();
    }

    std::size_t ResourceManager::GetSizeOfTexturePool() const
    {
      std::size_t size(0);

      for (auto item : *Textures) {
        size += sizeof(item);
      }
      return size;
    }

    std::size_t ResourceManager::GetSizeOfVertexShaderPool() const
    {
      std::size_t size(0);

      for (auto item : *VertexShaders) {
        size += sizeof(item);
      }
      return size;
    }

    std::size_t ResourceManager::GetSizeOfFragmentShaderPool() const
    {
      std::size_t size(0);

      for (auto item : *FragmentShaders) {
        size += sizeof(item);
      }
      return size;
    }

    std::size_t ResourceManager::GetSizeOfFontPool() const
    {
      std::size_t size(0);

      for (auto item : *Fonts) {
        size += sizeof(item);
      }
      return size;
    }

  }
}
