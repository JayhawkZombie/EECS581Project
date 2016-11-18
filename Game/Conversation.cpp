Conversation::Conversation() :
  int[255] m_convoNodes,
  m_userID(""), m_convoID(""), m_content(""), m_choiceID(""),
  m_numNodes(0), m_numChoices(0)
{}
Conversation::~Conversation()
{}
//getters
const std::string Conversation::getUserID()
{
	return m_userID;
}
const std::string Conversation::getConvoID()
{
	return m_convoID;
}
const int Conversation::getConvoNodes()
{
	return m_convoNodes;
}
const int Conversation::getNumChoices()
{
	return m_numChoices;
}
const std::string Conversation::getContent()
{
	return m_content;
}
const int Conversation::getAffinity()
{

} //int?
const std::string Conversation::getChoiceID()
{
	return m_choiceID;
}

//setters
void Conversation::setUserID(std::string &userID)
{
	m_userID = userID;
}
void Conversation::setConvoID(std::string &convoID)
{
	m_convoID = convoID;
} //ID of main conversation node
void Conversation::setContent(std::string &content)
{
	m_content = content;
}
void Conversation::setChoiceID(std::string &choiceID)
{
	m_choiceID = choiceID;
} //ID of choices in conversation
void Conversation::setConvoNodes(int &numNodes)
{
	m_numNodes = numNodes;
} //possibly to place them into an array
void Conversation::setNumChoices (int &numChoices)
{
	m_numChoices = numChoices;
}
void Conversation::setAffinity(int affinity, int increment)
{
	
}