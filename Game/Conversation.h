#ifndef CONVERSATION_H
#define CONVERSATION_H
//#include "Companion.h"
//#include "MainCharacter.h"
#include <string>
#include <memory>
class Conversation
{
public:
  Conversation();
  ~Conversation();
  //getters
  const std::string getUserID();
  const std::string getConvoID();
  const std::string getConvoNodes(int choice);
  const std::string getConvoNodesContent(int choice);
  const int getNumChoices();
  const std::string getContent();
//  const int getAffinity(); //int?
  const std::string getChoiceID();

  //setters
  void setUserID(std::string &userID);
  void setConvoID(std::string &convoID); //ID of main conversation node
  void setContent(std::string &content);
  void setChoiceID(std::string &choiceID); //ID of choices in conversation
  void setConvoNodes(std::string &convoNode); //possibly to place them into an array
  void setConvoNodesContent(std::string &convoNode); 
  void setNumChoices(int &numChoices);
//  void setCharacter(MainCharacter character);
//  void setAffinity(int &affinity, int &increment);
  //affinity, value, check if affinity is greater than the value
//255 max convo nodes in a conversation
private:
//  MainCharacter m_character;
  int m_currentConvoNodes;
  std::string m_convoNodes[255];
  std::string m_convoNodesContent[255];
//  std::shared_ptr<int> m_convoNodes;
  std::string m_userID;
  std::string m_convoID;
  std::string m_content;
  std::string m_choiceID;
  int m_numNodes;
  int m_numChoices;
};

#endif
