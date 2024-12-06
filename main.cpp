#include "SmartComponent/src/SmartComponent.h"

struct Vec2 {
	float x, y;
};

// To make smart component define component with memory deallocation logic in destructor, and define appropriate move construtor.
// SmartComponent will take care of memory managing
struct TransformComponent {
	Vec2* position;

	TransformComponent(float px, float py) {
		position = new Vec2({ px, py });
		std::cout << '\n' << "Transform construct";
	};

	TransformComponent(TransformComponent&& other) noexcept {
		position = other.position;
		other.position = nullptr;
		std::cout << '\n' << "Transform move";

	};

	~TransformComponent() {
		delete position;
		std::cout << '\n' << "Transform destructed";
	}

};

int main() {

	//Creating SmartComponent with TransformComponent as a component to wrap aroud
	SmartComponent smart_component(TransformComponent(5,6));

	//SmartComponent is movable, but non-copyable.
	SmartComponent smart_component2(std::move(smart_component));

	std::cout << '\n' << ((TransformComponent*)smart_component2.data)->position->x;

	//	Memory managing properties are achived through storing each individual component destructor as a lambda in a FunctiontWrapper member class (src/FunctionWrapper.h)
	//	Using of std::function as another way to store lambda is possible, but it has too much overhead for my use case
	//	Also it uses atleast 8x times more space.
}
