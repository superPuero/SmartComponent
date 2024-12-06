#pragma once

class FunctionWrapperBase {
public:
	virtual void invoke() = 0;

};

template<typename Callable>
class FunctionWrapper : public FunctionWrapperBase {
public:

	FunctionWrapper(Callable&& callable) : m_callable(std::forward<Callable>(callable)) {};

public:
	void invoke() override {
		m_callable();
	}

private:
	Callable m_callable;
};
