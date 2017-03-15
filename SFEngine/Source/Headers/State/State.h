#ifndef STATE_H
#define STATE_H

#include "../../../ThirdParty/cereal/cereal.hpp"
#include "../../../ThirdParty/cereal/archives/json.hpp"

namespace Engine {
	class State {
	public:
    template <class Archive>
		virtual void Save(Archive & archive) = 0;
    template <class Archive>
		virtual void Restore(Archive & archive) = 0;

	};
}
#endif //STATE_H
