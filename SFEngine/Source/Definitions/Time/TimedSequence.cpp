#include "../../Headers/Time/TimedSequence.h"

namespace Engine
{



  SequenceNode::SequenceNode(const SequenceNode & Copy)
    : m_Duration(Copy.m_Duration), m_StartCallBack(Copy.m_StartCallBack),
    m_IsDone(Copy.m_IsDone), m_EndCallBack(Copy.m_EndCallBack)
  {
  }

  SequenceNode::SequenceNode(std::initializer_list<SequenceNode> Seq)
  {
    
  }

  SequenceNode::SequenceNode(double delta, std::function<void(void)> start, std::function<void(void)> update, std::function<void(void)> end)
    : m_Duration(delta), m_StartCallBack(start), m_UpdateCallBack(update), m_EndCallBack(end)
  {
  }

  void SequenceNode::TickUpdate(const double & delta)
  {
    m_CurrentDuration += delta;

    if (m_CurrentDuration >= m_Duration) {
      m_IsDone = true;;
    }
  }

  bool SequenceNode::IsDone() const
  {
    return m_IsDone;
  }

  void SequenceNode::Start()
  {
    if (m_StartCallBack)
      m_StartCallBack();
  }

  void SequenceNode::End()
  {
    if (m_EndCallBack)
      m_EndCallBack();
  }

  void TimedSequence::AddSequence(double Duration, std::function<void(void)> StartCB, std::function<void(void)> Update, std::function<void(void)> EndCB)
  {
    m_Nodes.push({ Duration, StartCB, Update, EndCB });
  }

  void TimedSequence::AddSequences(std::function<void(void)> Start,
                                   std::function<void(void)> Update,
                                   std::function<void(void)> End,
                                   std::initializer_list<SequenceNode> Nodes)
  {
    m_StartCallBack = Start;
    m_EndCallBack = End;

    for (auto & node : Nodes)
      m_Nodes.push(node);
  }

  void TimedSequence::Start()
  {
    m_IsTiming = true;

    if (!m_Nodes.empty())
      m_Nodes.front().Start();

    if (m_StartCallBack)
      m_StartCallBack;
  }

  void TimedSequence::TickUpdate(const double & delta)
  {
    if (!m_Nodes.empty()) {
      if (!m_Nodes.front().IsDone())
        m_Nodes.front().TickUpdate(delta);
      else {
        m_Nodes.front().End();
        m_Nodes.pop();

        if (!m_Nodes.empty())
          m_Nodes.front().Start();
        else
          if (m_EndCallBack)
            m_EndCallBack();
      }
    }
  }

  void TimedSequence::SetUpdateCallback(std::function<void(const double&)> CB)
  {
    m_UpdateCallBack = CB;
  }

}
