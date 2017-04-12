#ifndef SFENGINE_TIMED_SEQUENCE_H
#define SFENGINE_TIMED_SEQUENCE_H

#include "../BasicIncludes.h"

#include <queue>

namespace Engine
{

  class TimedSequence;

  class SequenceNode
  {
  public:
    SequenceNode() = default;
    SequenceNode(const SequenceNode &Copy);
    SequenceNode(std::initializer_list<SequenceNode> Seq);
    SequenceNode(double delta, 
                 std::function<void(void)> start,
                 std::function<void(void)> update,
                 std::function<void(void)> end);

    ~SequenceNode() = default;

    void TickUpdate(const double &delta);
    bool IsDone() const;

    void Start();
    void End();

  protected:

    double m_Duration;
    double m_CurrentDuration = 0.0;
    bool   m_IsDone = false;
    
    std::function<void(void)> m_StartCallBack  = []() {};
    std::function<void(void)> m_EndCallBack    = []() {};
    std::function<void(void)> m_UpdateCallBack = []() {};
  };


  class TimedSequence
  {
  public:
    TimedSequence() = default;
    ~TimedSequence() = default;

    void AddSequence(
      double Duration,
      std::function<void(void)> StartCB,
      std::function<void(void)> Update,
      std::function<void(void)> EndCB
    );

    void AddSequences(
      std::function<void(void)> Start,
      std::function<void(void)> Update,
      std::function<void(void)> End,
      std::initializer_list<SequenceNode> Nodes
    );

    void Start();
    void TickUpdate(const double &delta);
    void SetUpdateCallback(std::function<void(const double &)> CB);
  protected:

    bool m_IsTiming = false;
    std::queue<SequenceNode> m_Nodes;
    std::function<void(void)> m_StartCallBack = []() {};
    std::function<void(void)> m_EndCallBack   = []() {};
    std::function<void(const double &)> m_UpdateCallBack = [](const double &) {};
  };

}

#endif
