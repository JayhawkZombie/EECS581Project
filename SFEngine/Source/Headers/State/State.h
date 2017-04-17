#ifndef SFENGINE_STATE_H
#define SFENGINE_STATE_H

#include "cereal\cereal.hpp"
#include "cereal\archives\json.hpp"

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
