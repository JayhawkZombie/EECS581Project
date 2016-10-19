#ifndef SFENGINE_LIST_TEMPLATES_H
#define SFENGINE_LIST_TEMPLATES_H

#include <string>
#include <iostream>

namespace Engine
{
  namespace Util
  {

    template<typename T>
    struct Node {
      T value;
      Node<T> *Next;
      Node<T> *Previous;

      Node(const T &v) : value(v), Next(nullptr) {}
      Node(const T &v, Node<T> *p) : Previous(p), Next(nullptr), value(v) {}

      inline bool operator==(const Node<T> &other) {
        return (value == other.value);
      }

      const T& GetValue() const {
        return value;
      }

    };

    template<typename Sequence>
    class NodeSequence {
    public:
      NodeSequence() : Beginning(nullptr), End(nullptr), Current(nullptr), Length(0) {
        
      }

      NodeSequence(const NodeSequence<Sequence> &copy) : NodeSequence() {
        Node<Sequence> *Temp = copy.Beginning;
        Node<Sequence> _Curr = Beginning;

        while (Temp != nullptr) {
          AddSequence(Temp->value);
          Temp = Temp->Next;
        }
      }

      NodeSequence<Sequence>& operator=(const NodeSequence &copy) {
        //Destroy old list
        Node<Sequence> *Temp = Beginning;
        while (Temp != nullptr) {
          Beginning = Temp;
          Temp = Temp->Next;
          delete Beginning;
        }

        Beginning = nullptr;
        End = nullptr;
        Length = 0;
        //Copy list on the right
        Temp = copy.Beginning;
        while (Temp != nullptr) {
          AddSequence(Temp->value);
          Temp = Temp->Next;
        }

      }

      void AddSequence(const Sequence &seq) {
        ++Length;
        if (Beginning == nullptr) {
          Beginning = new Node<Sequence>(seq);
          End = Beginning;
          Current = Beginning;
        }
        else {
          End->Next = new Node<Sequence>(seq, End);
          End = End->Next;
        }
          
      }

      bool AdvanceSequence() {
        return (Current->Next && (Current = Current->Next));
      }

      const std::size_t& SequenceLength() const {
        return Length;
      }

      Node<Sequence>* GetBeginning() const {
        return Beginning;
      }
      Node<Sequence>* GetEnd() const {
        return End;
      }
      Node<Sequence>* GetCurrent() const {
        return Current;
      }

    private:
      Node<Sequence> *Beginning;
      Node<Sequence> *End;
      Node<Sequence> *Current;
      std::size_t Length;

    };



  }
}

#endif
