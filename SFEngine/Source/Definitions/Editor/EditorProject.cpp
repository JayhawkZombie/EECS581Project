#include "../../Headers/Editor/EditorProject.h"

namespace Engine
{

  void EditorProject::Read(const std::string & in)
  {
  }

  void EditorProject::Write(const std::string & outfile)
  {
    std::ofstream out(outfile);

    if (!out) {
      out.clear();
      out.close();

      MessageAlert("Failed to open file: " + outfile + "\nfor saving project file");
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

    //write out the number of tile sheets
    Tag = ProjectFileTag::TileSheetCount;


    //start writing out the tile sheets

    for (auto & sheet : TileSheets) {
      Tag = ProjectFileTag::TileSheetBeginning;
      SerializeUint64(Tag, out);

      WriteTileSheet(sheet);

      Tag = ProjectFileTag::TileSheetEnd;
      SerializeUint64(Tag, out);
    }
    //done
    out.close();
  }

  void EditorProject::WriteTileSheet(std::shared_ptr<TileSheet> sheet)
  {
    //write out
  }

}
