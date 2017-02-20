#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::LoadProject(const std::string &ProjectPath)
  {
    std::cerr << "Loading Project" << std::endl;

    std::cerr << "***********************************************" << std::endl;
    std::ifstream In(ProjectPath);

    if (!In) {
     std::cerr << "Failed to load project file";
      In.clear();
      return;
    }

    In >> ProjectJson;

    try
    {
      PROJECT_PATH = ProjectJson["Project"]["Info"]["PROJECT_PATH"].asString();
      std::cerr << "PROJECT_PATH = " << PROJECT_PATH << std::endl;

      LoadAssets();
    }
    catch (Json::Exception &err)
    {
      std::cerr << "Json error: " << err.what() << std::endl;
    }
  }

  void Editor::LoadAssets()
  {
    //load textures
    std::cerr << "***********************************************" << std::endl;
    try
    {
      auto textures = ProjectJson["Project"]["Data"]["Textures"];

      std::string texname{ "" };
      std::string path{ "" };
      for (auto & val : textures) {
        texname = val["Name"].asString();

        Textures[texname] = std::make_shared<sf::Texture>();
        path = PROJECT_PATH + val["Path"].asString();

        if (!Textures[texname]->loadFromFile(path)) {
          throw EngineRuntimeError({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("Failed to load texture"));
        }
      }

      std::cerr << "Textures loaded: ";
      for (auto & tex : Textures) {
        std::cerr << "\t" << tex.first << std::endl;
      }
      std::cerr << "***********************************************" << std::endl;
      LoadSheets();
      LoadAnimations();
    }
    catch (Json::Exception &err)
    {

    }
    catch (EngineRuntimeError &eng_err)
    {

    }
  }

  void Editor::LoadSheets()
  {
    auto sheets = ProjectJson["Project"]["Data"]["Sheets"];

    if (sheets.isArray()) {

      for (auto & _ : sheets)
        LoadSheet(_);
    }

    std::cerr << "***********************************************" << std::endl;
    std::cerr << "Tile sheets loaded: " << std::endl;

    for (auto & sheet : TIleSheets) {
      std::cerr << sheet.first << std::endl;
      std::cerr << "\t->" << std::endl;

      for (auto & tile : sheet.second->GetLevelTiles()) {
        std::cerr << "\t\t" << tile.second->Name << std::endl;
      }

    }
    std::cerr << "***********************************************" << std::endl;
  }

  void Editor::LoadAnimations()
  {
    auto animations = ProjectJson["Project"]["Data"]["Animations"];

    if (animations.isArray()) {

      for (auto & _ : animations)
        LoadAnimation(_);

    }

    std::cerr << "Animations loaded: " << std::endl;

    for (auto & anim : Animations)
      std::cerr << "\t" << anim.first << std::endl;

    std::cerr << "***********************************************" << std::endl;

  }

  void Editor::LoadAnimation(const Json::Value & anim)
  {
    std::string name = anim["Name"].asString();
    std::string texture = anim["Texture"].asString();
    float time = anim["FrameTime"].asFloat();
    bool pingpong = anim["PingPong"].asBool();

    //Make sure we have a valid texture
    auto it = Textures.find(texture);
    if (it == Textures.end()) {
      std::cerr << "Unable to find texture : " << texture << std::endl;
      return;
    }

    auto tex = it->second;
    std::shared_ptr<Animation> Animation(new Engine::Animation());
    Animation->SetSpriteSheet(tex, "AnimSheet");
    Animation->SetFrameTime(time);
    Animation->MakePingPong(pingpong);
    //get the frames
    std::vector<sf::IntRect> Frames = {};
    auto frames = anim["Frames"];
    sf::IntRect Rect = {};
    for (auto & frame : frames) {
      Rect.left = frame[0].asInt();
      Rect.top = frame[1].asInt();
      Rect.width = frame[2].asInt();
      Rect.height = frame[3].asInt();

      Animation->AddFrame(Rect);
    }
    
    Animations[name] = Animation;
  }

  void Editor::LoadSheet(const Json::Value &sheet)
  {
    std::cerr << "***********************************************" << std::endl;
    try
    {
      auto texturename = sheet["Name"].asString();
      std::cerr << "Loading Sheet : " << texturename << std::endl;
      auto sheet_data = sheet["Sheet"];
      auto sheet_frames = sheet_data["Frames"];

      std::cerr << "\tTexture : " << sheet_data["Texture"] << std::endl;

      TIleSheets[texturename] = std::make_shared<TileSheet>();

      Json::Value rect;
      std::string tileName{ "" };
      sf::IntRect iRect{ 0, 0, 0, 0 };
      Json::Value size;

      for (auto & frame : sheet_frames) {
        tileName = frame["Name"].asString();
        rect = frame["Rect"];
        size = frame["Size"];

        //there should be 4 items in this array
        if (!rect.isArray())
          throw EngineRuntimeError({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("Frames data is not an array"));

        iRect.left = std::stoi(rect[0].asString());
        iRect.top = std::stoi(rect[1].asString());
        iRect.width = std::stoi(rect[2].asString());
        iRect.height = std::stoi(rect[3].asString());

        std::cerr << tileName << "\t\t ---> \t[" << iRect.left << ", " << iRect.top << ", " << iRect.width << ", " << iRect.height << "]" << std::endl;
        TIleSheets[texturename]->AddTile(tileName, iRect);
        TIleSheets[texturename]->SetTexture(Textures[sheet_data["Texture"].asString()]);
      }

    }
    catch (Json::Exception &err)
    {
      std::cerr << "Json error while loading sheets : " << err.what() << std::endl;
    }

  }

  void Editor::LoadObjects()
  {
  }

  void Editor::LoadScripts(chaiscript::ModulePtr ptr)
  {
  }

  void Editor::PopulateGUI()
  {

    for (auto & sheet : TIleSheets) {
      TilesPanelListBox->addItem(sheet.first);
    }

    GUIPopulated = true;
  }

}
