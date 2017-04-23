#ifndef SFENGINE_THREADING_ASYNC_LOADER_H
#define SFENGINE_THREADING_ASYNC_LOADER_H

#include "BasicIncludes.h"

#include <thread>
#include <mutex>
#include <condition_variable>

namespace Engine
{
  class BasicLevel;

  struct ASyncThreadStatus
  {
    bool  bThreadComplete;
    INT32 ThreadStatus;
    bool  bNeedShutdown;
    bool  bHasWork = false;
    bool  bIsLoading = false;
    std::thread::id ThreadID;
    std::mutex StatusLock;
    std::condition_variable   ThreadCond;
    std::function<void(void)> NotifyCompleted;
    SPtrShared<BasicLevel> LoadingLevel;
  };

  struct ASyncThreadRequest
  {
    std::thread::id m_ThreadId;
    std::function<void(void)> m_LoadingFtn;
    std::function<void(void)> m_LoadingDoneFtn;
  };

  class ASyncLevelStreamThread
  {
  public:
    static SPtrShared<ASyncThreadStatus> Launch();
    static void Shutdown();

    static bool Load(std::function<SPtrShared<BasicLevel>(void)> LoadFtn, std::string LevelName);
    static std::thread::id GetThreadID();
    static SPtrShared<ASyncThreadStatus> GetThreadStatus();

  protected:
    ASyncLevelStreamThread();
    ~ASyncLevelStreamThread();
    void ThreadLoop();
    static ASyncLevelStreamThread* Get();
    
    //Level to stream data into
    SPtrShared<BasicLevel> m_StreamingLevel;

    //Lock to secure the queue
    SPtrSharedMutex m_QueueLock;

    //Request to query
    SPtrShared<ASyncThreadStatus> m_StreamerStatus;

    //The thread
    std::thread m_Thread;

    //ID of the thread
    std::thread::id m_ThreadID;

    //Queue to push requests into
    SPtrShared<
      std::queue<
        std::pair<std::string, std::function<SPtrShared<BasicLevel>(void)>>
      >> m_LoadingQueue;
  };

  class ASyncLoadManager
  {
  public:
    static void Init();
    static void Shutdown();

    static ASyncLoadManager& Get();

    static void Launch(std::function<void(void)> LoadingFtn, std::function<void(void)> CompletedFtn);
    static bool QueryFinished();
    static void Halt();
    

  protected:
    ASyncLoadManager();
    ~ASyncLoadManager();



    std::thread m_LoaderThread;
    SPtrShared<std::mutex> m_ThreadMutex;
    SPtrShared<std::mutex> m_ThreadStatusLock;
    SPtrShared<ASyncThreadStatus> m_ThreadCompleted;
  };

}

#endif
