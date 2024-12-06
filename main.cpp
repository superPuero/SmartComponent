#include "SmartComponent/src/SmartComponent.h"

struct Vec2 {
	float x, y;
};

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

	SmartComponent smart_component(TransformComponent(5,6));

	SmartComponent smart_component2(std::move(smart_component));

	std::cout << '\n' << ((TransformComponent*)smart_component2.data)->position->x;
}