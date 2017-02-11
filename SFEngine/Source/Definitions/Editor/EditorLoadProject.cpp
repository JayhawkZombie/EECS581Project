#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::LoadProject(const std::string &ProjectPath)
  {
    std::ifstream In(ProjectPath);

    MessageAlert("Failed to load project file");

  }

}
