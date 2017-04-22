#include "Threading/ASyncLoader.h"

namespace Engine
{



  void ASyncLoadManager::Init()
  {
  }

  void ASyncLoadManager::Shutdown()
  {
  }

  ASyncLoadManager & ASyncLoadManager::Get()
  {
    static ASyncLoadManager LoaderSingleton;

    return LoaderSingleton;
  }

  void ASyncLoadManager::Launch(std::function<void(void)> LoadingFtn, std::function<void(void)> CompletedFtn)
  {
    auto &Loader = Get();
    Loader.m_ThreadStatusLock->lock();
    Loader.m_ThreadCompleted->NotifyCompleted = CompletedFtn;
    Loader.m_LoaderThread = std::thread(LoadingFtn);
    Loader.m_ThreadStatusLock->unlock();
  }

  bool ASyncLoadManager::QueryFinished()
  {
    bool Done = false;

    auto &Loader = Get();
    Loader.m_ThreadStatusLock->lock();
    Done = Loader.m_ThreadCompleted->bThreadComplete;
    Loader.m_ThreadStatusLock->unlock();

    return Done;
  }

  void ASyncLoadManager::Halt()
  {
  }

  ASyncLoadManager::ASyncLoadManager()
    : m_ThreadCompleted(std::make_shared<ASyncThreadStatus>()),
    m_ThreadMutex(std::make_shared<std::mutex>()),
    m_ThreadStatusLock(std::make_shared<std::mutex>())
  {
  }

  ASyncLoadManager::~ASyncLoadManager()
  {
    if (m_LoaderThread.joinable())
      m_LoaderThread.join();

    m_ThreadCompleted.reset();
    m_ThreadMutex.reset();
    m_ThreadStatusLock.reset();
  }

}
