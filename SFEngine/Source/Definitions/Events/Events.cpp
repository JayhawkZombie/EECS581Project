#include "../../Headers/Events/Events.h"

enum MyAction {
	Left,
	Right,
	Up,
	Down,
};


Events::Events() {
	thor::EventSystem();
}

Events::~Events() {

}