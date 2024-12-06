#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>
#include <type_traits>

#include "FunctionWrapper.h"

class SmartComponent {
public:
	SmartComponent() {
		data = nullptr;
		destructor_function = nullptr;
		std::cout << '\n' << "SmartComponent construct";
	};

	SmartComponent(SmartComponent&& other) noexcept {
		data = other.data;
		destructor_function = other.destructor_function;
		other.destructor_function = nullptr;
		std::cout << '\n' << "SmartComponent move";
	};

	template<typename Component>
	inline SmartComponent(Component&& component) noexcept {
		data = new Component(std::move(component));
		destructor_function = new FunctionWrapper([this]() {delete static_cast<Component*>(data); });
		std::cout << '\n' << "SmartComponent templated move";

	};

	~SmartComponent() {
		if (destructor_function) {
			destructor_function->invoke();
			delete destructor_function;
		}
	};

public:
	void* data;

private:
	FunctionWrapperBase* destructor_function;

};
