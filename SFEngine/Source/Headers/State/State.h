#ifndef STATE_H
#define STATE_H
namespace Engine {
	class State {
	public:
		virtual void Save() = 0;
		virtual void Restore() = 0;

	};
}
#endif //STATE_H
