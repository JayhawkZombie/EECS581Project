#ifndef SFENGINE_LOGGER_H
#define SFENGINE_LOGGER_H

#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <condition_variable>

namespace Engine
{

  class Logger
  {
  public:
    Logger();
    ~Logger();

    void LogToFile(const std::string &message);
    void SetFile(const std::string &filepath);
    void Stop();
    void Start();

  private:
    std::shared_ptr<std::mutex> Lock;
    std::shared_ptr<std::mutex> QueueLock;
    std::shared_ptr<std::queue<std::string>> MessageQueue;
    std::shared_ptr<std::condition_variable> WaitVar;
    std::thread LOGGER_THREAD;

    std::shared_ptr<bool> QuitAlert;
    std::shared_ptr<bool> MessageAlert;
    std::shared_ptr<bool> Stopped;
    std::shared_ptr<bool> FileFailure;
    std::shared_ptr<std::ofstream> OutStream;
  };

}


#endif
