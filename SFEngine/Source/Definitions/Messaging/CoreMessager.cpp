#include "Messaging/CoreMessager.h"
#include "Globals/GlobalHooks.h"
#include "Exceptions/Exceptions.h"

#include <iomanip>

namespace
{

  std::unordered_map<Engine::SystemMessageType, std::string> MessageTypeStrings =
  {
    { Engine::SystemMessageType::ActivityLog, "ActivityLog" }, { Engine::SystemMessageType::Notification, "Notification" },
    { Engine::SystemMessageType::Request, "Request" }, { Engine::SystemMessageType::Critical, "Critical" }
  };

  std::unordered_map<Engine::MessageLogLevel, std::string> MessageLogLevelStrings =
  {
    { Engine::MessageLogLevel::Normal, "Normal" }, { Engine::MessageLogLevel::Elevated, "Elevated" },
    { Engine::MessageLogLevel::High, "High" }, { Engine::MessageLogLevel::Critical, "Critical" },
    { Engine::MessageLogLevel::Unrecoverable, "Unrecoverable" }
  };

}

namespace Engine
{
  Messager* Messager::m_MessagerInstance = nullptr;


  Messager::~Messager()
  = default;

  void Messager::Init()
  {
    m_MessagerInstance = new Messager;

    if (!m_MessagerInstance) {
      throw MessageException({ ExceptionCause::MessagerInvalid, ExceptionCause::ConstructionError }, 
                             EXCEPTION_MESSAGE("Failed to initialize the messager"));
    }
  }

  void Messager::Shutdown()
  {
    auto MessagerPtr = Get();

    if (MessagerPtr) {
      MessagerPtr->FlushMessageCache();

      delete MessagerPtr;
    }
    else if (MessagerPtr) {
      throw MessageException({ ExceptionCause::MessagerInvalid }, 
                             EXCEPTION_MESSAGE("Attempt to shutdown, but more than 1 reference exists"));
    }
    else {
      throw MessageException({ ExceptionCause::MessagerInvalid }, 
                             EXCEPTION_MESSAGE("Attempt to shutdown messager, but messager does not exist"));
    }
  }

  void Messager::FlushMessageCache()
  {
  }

  bool Messager::PostMessageForInstance(std::uint32_t Source, std::uint32_t Destination, const SystemMessage &Message)
  {
    // If this ID is used, we will post a message to it, otherwise not
    if (IsIDUsed(Destination)) {
      auto Cache = Get();
      if (Cache) {
        Cache->m_MessageCache[Destination].emplace_back(Message);
        return true;
      }

      return false;
    }
    return false;
  }

  bool Messager::PostMessageForClass(std::uint32_t Source, const std::string ReceivingClass, const SystemMessage &Message)
  {
    auto Cache = Get();

    if (!Cache)
      return false;

    std::string ALogPost = "Message posted for class " + ReceivingClass;
    SystemMessage ALogMsg(SystemMessageType::ActivityLog, Source, 0, ALogPost);

    PostToActivityLog(ALogMsg);
    Cache->m_ClassesMessageCache[ReceivingClass].emplace_back(Message);

    return true;
  }

  void Messager::PushMessageNotifcations()
  {
    //To be implemented - we currently have no tracking of all instantiated objects
    //  through an easy-to-use interface
  }

  bool Messager::PostLogMessage(std::uint32_t Source, const SystemMessage & Message, MessageLogLevel MLevel)
  {
    auto Cache = Get();

    if (!Cache)
      return false;

    std::string LogLevel{ "" };

    switch (MLevel)
    {
    case MessageLogLevel::Normal:
      LogLevel = "Normal";
      Cache->m_NormalLogMessages.emplace_back(Message);
      break;
    case MessageLogLevel::Elevated:
      LogLevel = "Elevated";
      Cache->m_ElevatedLogMessages.emplace_back(Message);
      break;
    case MessageLogLevel::High:
      LogLevel = "High";
      Cache->m_HighLogMessages.emplace_back(Message);
      break;
    case MessageLogLevel::Critical:
      LogLevel = "Critical";
      Cache->m_CriticalLogMessages.emplace_back(Message);
      break;
    case MessageLogLevel::Unrecoverable:
      LogLevel = "Unrecoverable";
      Cache->m_UnrecoverableMessages.emplace_back(Message);
      break;
    default:
      LogLevel = "Unknown";
      std::string ALogMsg = "Unknown log level for specified log message post";
      PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, Source, 0, ALogMsg));
      break;
    }

    return true;
  }

  void Messager::PurgeLogs()
  {
    auto Cache = Get();

    if (!Cache) {
      throw MessageException({ ExceptionCause::MessagerInvalid }, 
                             EXCEPTION_MESSAGE("Could not lock the messager to purge messages"));
    }

    Cache->m_NormalLogMessages.clear();
    Cache->m_ElevatedLogMessages.clear();
    Cache->m_HighLogMessages.clear();
    Cache->m_CriticalLogMessages.clear();
    Cache->m_UnrecoverableMessages.clear();
  }

  void Messager::PurgeLogsToFile(const std::string & CachePath, const std::string &ActivityPath, const std::string &LogPath)
  {

    // This will be fun...

    auto MPtr = Get();

    if (!MPtr) {
      throw MessageException({ ExceptionCause::MessagerInvalid, ExceptionCause::InvalidObjectUsed }, 
                             EXCEPTION_MESSAGE("Attempted to purge logs to file, but Messager does not exist"));
    }

    std::ofstream File(CachePath);
    if (!File) {
      throw StreamException({ ExceptionCause::StreamFailure }, 
                            EXCEPTION_MESSAGE("Failed to open path for log cache purge"));
    }

    //First we will purge the messages
    File << "MessageCache Purge\n";

    for (auto & message : MPtr->m_MessageCache) {
      std::uint32_t Key = message.first;

      File << "Messages for destination " << Key << std::endl;

      for (auto & submsg : message.second) {
        WriteToFile(Key, submsg, File);
      }
    } // for auto & message : Mptr->m_MessageCache

    File.close();


    //Then we will purge the activity log
    File.open(ActivityPath);
    if (!File) {
      throw StreamException({ ExceptionCause::StreamFailure }, 
                            EXCEPTION_MESSAGE("Failed to open path for activity log purge"));
    }

    File << "Activity Log Purge\n";
    for (auto & message : MPtr->m_ActivityLog) {
      WriteToFile(0, message, File);
    }
    File.close();

    File.open(LogPath);
    if (!File) {
      throw StreamException({ ExceptionCause::StreamFailure }, 
                            EXCEPTION_MESSAGE("Failed to open path for ranked log purge"));
    }

    File << "Ranked Log Purge\n" << std::endl;

    File << "\tNormal Logs:\n" << std::endl;
    for (auto & message : MPtr->m_NormalLogMessages) {
      WriteToFile(0, message, File);
    }

    File << "\n\tElevated Logs:\n" << std::endl;
    for (auto & message : MPtr->m_ElevatedLogMessages) {
      WriteToFile(0, message, File);
    }

    File << "\nHigh Logs:\n" << std::endl;
    for (auto & message : MPtr->m_HighLogMessages) {
      WriteToFile(0, message, File);
    }

    File << "\nCritical Logs:\n" << std::endl;
    for (auto & message : MPtr->m_CriticalLogMessages) {
      WriteToFile(0, message, File);
    }

    File << "\nUnrecoverable Logs:\n" << std::endl;
    for (auto & message : MPtr->m_UnrecoverableMessages) {
      WriteToFile(0, message, File);
    }

    sf::IntRect rect = { {0, 0}, {100, 500} };
    sf::IntRect _rect(0, 0, 100, 500);

    File << "\n\nLog Purge Complete" << std::endl;
    File.close();
  }

  void Messager::WriteToFile(std::uint32_t KeyVal, const SystemMessage & Message, std::ofstream & File)
  {
    File << "**********************************************************************************\n" 
         << "Source: " << ( Message.m_Source == 0 ? "Engine" : std::to_string(Message.m_Source) ) 
         << "\nPostText:\n" << Message.m_PostText << "\n" << std::endl;
  }

  void Messager::PurgeLogsAtLevel(MessageLogLevel MLevel)
  {
    auto Cache = Get();

    if (!Cache) {
      throw MessageException({ ExceptionCause::MessagerInvalid }, 
                             EXCEPTION_MESSAGE("Could not lock the messager to purge messages"));
    }
    std::string MLevelStr{ "" };

    switch (MLevel)
    {
    case MessageLogLevel::Normal:
      MLevelStr = "Normal";
      Cache->m_NormalLogMessages.clear();
      break;
    case MessageLogLevel::Elevated:
      MLevelStr = "Elevated";
      Cache->m_ElevatedLogMessages.clear();
      break;
    case MessageLogLevel::High:
      MLevelStr = "High";
      Cache->m_HighLogMessages.clear();
      break;
    case MessageLogLevel::Critical:
      MLevelStr = "Critical";
      Cache->m_CriticalLogMessages.clear();
      break;
    case MessageLogLevel::Unrecoverable:
      MLevelStr = "Unrecoverable";
      Cache->m_UnrecoverableMessages.clear();
      break;
    default:
      MLevelStr = "Unknown";
      break;
    }
    MLevelStr = "MessageCache cleared for level " + MLevelStr;
    PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, MLevelStr));
  }

  bool Messager::PostToActivityLog(const SystemMessage & Message)
  {
    auto Cache = Get();

    if (!Cache) {
      return false;
    }

    Cache->m_ActivityLog.emplace_back(Message);
    return true;
  }

  Messager* Messager::Get()
  {
    return m_MessagerInstance;
  }

  void Messager::InitPriv()
  {
  }

  SystemMessage::SystemMessage(const SystemMessage &Copy)
    : 
    m_MessageType(Copy.m_MessageType),
    m_Destination(Copy.m_Destination),
    m_PostText(Copy.m_PostText),
    m_Source(Copy.m_Source)
  {
  }

  SystemMessage::SystemMessage(const SystemMessage &&MoveCopy)
    :
    m_MessageType(MoveCopy.m_MessageType),
    m_Destination(MoveCopy.m_Destination),
    m_Source(MoveCopy.m_Source),
    m_PostText(MoveCopy.m_PostText)
  {
  }

  SystemMessage::SystemMessage(SystemMessageType MessageType, std::uint32_t Source, std::uint32_t Destination, const std::string &Post)
    :
    m_MessageType(MessageType),
    m_Destination(Destination),
    m_Source(Source),
    m_PostText(Post)
  {
  }

}
