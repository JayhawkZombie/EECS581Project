#ifndef SFENGINE_UMTIMED_SEQUENCE_H
#define SFENGINE_UMTIMED_SEQUENCE_H

#include "../BasicIncludes.h"

#include <queue>

namespace Engine
{

  class UntimedSequenceNode
  {
  public:
    UntimedSequenceNode(std::function<void(void)> m_StartCB, std::function<bool(void)> m_CheckCB, std::function<void(void)> m_EndCB);
    UntimedSequenceNode(const UntimedSequenceNode &node);
    ~UntimedSequenceNode();

    void Start();
    void Stop();
    void Update();
    bool IsDone() const;

  protected:
    bool m_IsDone = false;
    std::function<bool(void)> m_CheckCallBack   = []() -> bool { return false; };
    std::function<void(void)> m_StartedCallBack = []() {};
    std::function<void(void)> m_EndedCallBack   = []() {};
  };

  class UntimedSequence
  {
  public:
    UntimedSequence();
    ~UntimedSequence();
    void Start();
    void Stop();
    void Update();
    void AddSequence(std::function<void(void)> SeqStart, std::function<void(void)> SeqDone,
                     UntimedSequenceNode Node);
    void AddSequences(std::function<void(void)> SeqStart, std::function<void(void)> SeqDone,
                      std::initializer_list<UntimedSequenceNode> Nodes);
  protected:
    bool m_IsSequencing = false;
    std::queue<UntimedSequenceNode> m_Nodes;
    std::function<void(void)> m_StartCallBack = []() {};
    std::function<void(void)> m_EndCallBack   = []() {};
  };

}

#endif
