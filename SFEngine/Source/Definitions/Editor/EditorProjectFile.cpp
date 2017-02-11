#include "../../Headers/Editor/EditorProjectFile.h"

namespace Engine
{



  void ProjectFile::Read(const std::string & path)
  {
  }

  void ProjectFile::Write(const std::string & path)
  {
    std::ofstream out(path);

    if (!out) {
      out.clear();
      out.close();

      MessageAlert("Failed to open file: " + path + "\nfor saving project file");
    }

    //write the file beg tag
    std::uint64_t Tag = ProjectFileTag::Beginning;
    SerializeUint64(Tag, out);

    //then write the name of the project
    Tag = ProjectFileTag::ID;
    SerializeUint64(Tag, out);
    SerializeString(ProjectName, out);

    //write the project version
    Tag = ProjectFileTag::ProjectVersion;
    SerializeUint64(Tag, out);
    SerializeUint64(ProjectVersion, out);

    //write the editor version
    Tag = ProjectFileTag::EditorVersion;
    SerializeUint64(Tag, out);
    SerializeString(EditorVersionString, out);

    //write out the engine version
    Tag = ProjectFileTag::EngineVersion;
    SerializeUint64(Tag, out);
    SerializeString(EngineVersionString, out);


    //done
    out.close();

  }

}
