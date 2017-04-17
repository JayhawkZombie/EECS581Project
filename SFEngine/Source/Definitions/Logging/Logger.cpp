#include "Logging\Logger.h"

namespace Engine
{

  Logger::Logger()
    : Lock(std::shared_ptr<std::mutex>(new std::mutex)),
    QueueLock(std::shared_ptr<std::mutex>(new std::mutex)),
    MessageQueue(std::shared_ptr<std::queue<std::string>>(new std::queue<std::string>)),
    WaitVar(std::shared_ptr<std::condition_variable>(new std::condition_variable)),
    QuitAlert(std::shared_ptr<bool>(new bool{ false })),
    MessageAlert(std::shared_ptr<bool>(new bool{ false })),
    Stopped(std::shared_ptr<bool>(new bool{ false })),
    FileFailure(std::shared_ptr<bool>(new bool{ false })),
    OutStream(std::shared_ptr<std::ofstream>(new std::ofstream))
  {

  }

  Logger::~Logger()
  {

  }

  void Logger::Start()
  {
      LOGGER_THREAD = std::thread(
        [this]() 
      {
        std::unique_lock<std::mutex> _lock(*(this->Lock));
        std::stringstream message;
        std::time_t t;

        while (!*(this->QuitAlert)) {

          while (!*(this->MessageAlert)) {
            this->WaitVar->wait(_lock);
          }

          if (!*(this->FileFailure)) {

            //while (!(this->MessageQueue->empty())) {
            //  t = std::time(nullptr);
            //  message.clear();
            //  message << std::put_time(std::localtime(&t), "%c %Z");
            //  message << " : " << this->MessageQueue->front();

            //  this->MessageQueue->pop();
            //  *OutStream << message.str();
            //  *OutStream << std::endl;
            //}
          }
          
          *(this->MessageAlert) = false;

        }
      
      }
      );

      //std::thread([this]()
      //{
        //std::unique_lock<std::mutex> _lock(*(this->Lock));
        //std::stringstream message;
        //std::time_t t;

        //while (!(this->QuitAlert)) {

        //  while (!(this->MessageAlert)) {
        //    WaitVar->wait(_lock);
        //  }

        //  if (!*(this->FileFailure)) {
        //    this->QueueLock->lock();

        //    while (!this->MessageQueue->empty()) {

        //      t = std::time(nullptr);
        //      message.clear();
        //      message << std::put_time(std::localtime(&t), "%c %Z");
        //      message << " : " << this->MessageQueue->front();
        //      
        //      *OutStream << message.str() << "\n";
        //      std::cerr << "Logger message: " << message.str() << std::endl; 
        //      this->MessageQueue->pop();
        //    }

        //    this->QueueLock->unlock();
        //    *(this->MessageAlert) = false;
        //  } //if !FileFailure

        //}//while !QuitAlert

        //return;
      //});
  }

  void Logger::SetFile(const std::string &filepath)
  {
    OutStream->open(filepath);
    if (OutStream->fail())
      *FileFailure = true;
  }

  void Logger::Stop()
  {
    std::unique_lock<std::mutex> lock(*Lock);
    *QuitAlert = true;
    *MessageAlert = true;
    WaitVar->notify_all();
    LOGGER_THREAD.join();

    OutStream->close();
  }

  void Logger::LogToFile(const std::string &message)
  {
    std::unique_lock<std::mutex> _lock(*Lock);
    *MessageAlert = true;
    *QuitAlert = false;
    MessageQueue->push(message);
    WaitVar->notify_all();
  }

}
