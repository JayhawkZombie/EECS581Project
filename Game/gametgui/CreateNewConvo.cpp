#include "CreateNewConvo.h"
#include <filesystem>

//namespace Engine {

void NewConvoCreator::CreateConvoNode(std::string filename, MainCharacter mc)
  {
    ListReader reader;

    //This will cause a compiler failure, please use a cloning method
    
    my_filename = filename;

    convo_arr = reader.readConversation("Game/ContentFiles/Conversation/ConvoJohnWakeUp.txt", mc);
    totalNodes = reader.getNumConversations();
    sf::RenderWindow *Window;
    WindowSize = Window->getSize();

    //WindowSize = 
  }

  void NewConvoCreator::LoadConvoGUI(int cur, int j)
  {

    ChoiceButton = Theme->load("Button");
    ChoiceButton->setText(sizeof(convo_arr));
    ChoiceButton->setSize({ 680, 30 });
    ChoiceButton->setPosition({ 10, 350 });
    CreationWindow->add(ChoiceButton);

    int arrsize = sizeof(convo_arr) / sizeof(convo_arr[0]);

    //for (int i = 0; i < arrsize; i++)
    for (int i = 0; i < totalNodes; i++)
    {
      if (convo_arr[i]->getConvoID() == convo_arr[cur]->getConvoNodes(j))
      {
        LoadConvo(i);
        return;
      }
    }
    if (convo_arr[cur]->getNumChoices() == 0)
    {
      Close();
    }

  }
  void NewConvoCreator::setVariables(int numChoices, std::string contentText, std::string buttonText)
  {
    m_numChoices = numChoices;
    m_contentText = contentText;
    m_buttonText = buttonText;
  }
  void NewConvoCreator::NewWindow()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
    OpenTheme(Theme);
  }

  void NewConvoCreator::LoadConvo(int cur)
  {
    if (convo_arr == NULL)
      CreateConvoNode(my_filename, my_mc);
    buttonPos = 0;
    textSize = 0;
    Close();
    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });

    //create the edit fields to enter a project title
    CharSpeaking = Theme->load("ChatBox");
    CharSpeaking->addLine(convo_arr[cur]->getUserID());
    CharSpeaking->setSize({ 680, 30 });
    CharSpeaking->setPosition({ 10, 10 });

    //should be variable, dependent on how many choices there are
    textSize = 110;
    ContentText = Theme->load("TextBox");
    ContentText->addText(convo_arr[cur]->getContent());
    ContentText->setSize({ 680, textSize });
    ContentText->setPosition({ 10, 50 });

    buttonPos = textSize + 60;

    for (int j = 0; j < convo_arr[cur]->getNumChoices(); j++)
    {
      ChoiceButton = Theme->load("Button");
      ChoiceButton->setText(convo_arr[cur]->getConvoNodesContent(j));
      ChoiceButton->setSize({ 680, 30 });
      ChoiceButton->setPosition({ 10, buttonPos });

      nodeID = (convo_arr[cur]->getConvoNodes(j));
      ChoiceButton->connect("clicked", &NewConvoCreator::LoadConvoGUI, this, cur, j);
      buttonPos += 40;
      CreationWindow->add(ChoiceButton);

    }

    CreationWindow->add(CharSpeaking);
    CreationWindow->add(ContentText);

    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

  }
  void NewConvoCreator::NewConvo()
  {
    buttonPos = 200;
    textSize = 0;
    Close();
    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });


    EditCharacter = Theme->load("EditBox");
    EditCharacter->setDefaultText("Character speaking");
    EditCharacter->setTextSize(10);
    EditCharacter->setSize({ 400, 25 });
    EditCharacter->setPosition({ 10, 10 });

    EditID = Theme->load("EditBox");
    EditID->setDefaultText("# ID");
    EditID->setTextSize(10);
    EditID->setSize({ 150, 25 });
    EditID->setPosition({ 500, 10 });

    EditContent = Theme->load("EditBox");
    EditContent->setDefaultText("Add conversation content here...");
    EditContent->setTextSize(15);
    EditContent->setSize({ 680, 150 });
    EditContent->setPosition({ 10, 40 });

    EditAddChoice = Theme->load("Button");
    EditAddChoice->setText("Add Choice");
    EditAddChoice->setSize({ 100, 20 });
    EditAddChoice->setPosition({ 550, 360 });
    EditAddChoice->connect("clicked", [this]() {this->addChoice(); });

    EditSave = Theme->load("Button");
    EditSave->setText("Save");
    EditSave->setSize({ 100, 20 });
    EditSave->setPosition({ 10, 360 });
    EditSave->connect("clicked", [this]() {this->addChoice(); });

    EditLoad = Theme->load("Button");
    EditLoad->setText("Load");
    EditLoad->setSize({ 100, 20 });
    EditLoad->setPosition({ 550, 360 });
    EditLoad->connect("clicked", [this]() {this->addChoice(); });

    CreationWindow->add(EditAddChoice);
    CreationWindow->add(EditSave);
    CreationWindow->add(EditID);
    CreationWindow->add(EditContent);
    CreationWindow->add(EditCharacter);

    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }
  void NewConvoCreator::addChoice()
  {
    if (buttonPos < 360)
    {
      //needs to be pushed to a vector so that the choices can be loaded in by their IDs
      //vector needs to be cleared after every choice...??
      //otherwise IDs and stuff get too messy for an engine run game made to make things simpler
      EditChoiceID = Theme->load("EditBox");
      EditChoiceID->setDefaultText("Go to ID #");
      EditChoiceID->setTextSize(10);
      EditChoiceID->setSize({ 70, 30 });
      EditChoiceID->setPosition(10, buttonPos);

      EditChoice = Theme->load("EditBox");
      EditChoice->setDefaultText("Add dialogue for choice...");
      EditChoice->setSize({ 600, 30 });
      EditChoice->setPosition(75, buttonPos);
      buttonPos += 40;

      CreationWindow->add(EditChoice);
      CreationWindow->add(EditChoiceID);
    }

  }
  void NewConvoCreator::OpenTheme(tgui::Theme::Ptr ThemePtr)
  {
    Theme = ThemePtr;

    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    //create the window
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });

    CreateConversations = Theme->load("Button");
    CreateConversations->setText("Create a new conversation graph");
    CreateConversations->setSize({ 320, 380 });
    CreateConversations->setPosition({ 10, 10 });
    CreateConversations->connect("clicked", [this]() {this->NewConvo(); });

    LoadGameConvo = Theme->load("Button");
    LoadGameConvo->setText("Load in the game");
    LoadGameConvo->setSize({ 320, 380 });
    LoadGameConvo->setPosition({ 350, 10 });
    LoadGameConvo->connect("clicked", [this]() {this->LoadConvo(0); });


    CreationWindow->add(CreateConversations);
    CreationWindow->add(LoadGameConvo);

    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void NewConvoCreator::Close()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
  }
//}
