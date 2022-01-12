#include <iostream>
class Component {
	public:
		virtual ~Component() {}
		virtual void method() = 0;
		// etc...
};

class ConcreteComponent : public Component {
	public:
		virtual ~ConcreteComponent() {}
		void method() {
			std::cout << "method" << std::endl;
		}
		// etc...
};

class Decorator : public Component {
	private:
		// a reference to the Component that we will be decorating
		Component *component_;
	public:
		// the interface conforms to the Component interface
		~Decorator() {}
		Decorator(Component *component) : component_(component) {}
		virtual void method() {
			component_->method();
		}
};

class ConcreteDecoratorA : public Decorator {
	public:
		ConcreteDecoratorA(Component *component) : Decorator(component) {}
		void method() {
			Decorator::method();
			// add capabilities for this decorator
			std::cout << "Decorator A" << std::endl;
		}
};

class ConcreteDecoratorB : public Decorator {
	public:
		ConcreteDecoratorB( Component *component) : Decorator(component) {}
		void method() {
			Decorator::method();
			// add capabilities for this decorator.
			std::cout << "Decorator B" << std::endl;
		}
};

int main(int argc, char *argv[])
{
	ConcreteComponent *concreteComponent = new ConcreteComponent();
	ConcreteDecoratorA *decoratorA = new ConcreteDecoratorA(concreteComponent);
	ConcreteDecoratorB *decoratorB = new ConcreteDecoratorB(decoratorA);

	Component *component = decoratorB;
	component->method();
	decoratorA->method();
	concreteComponent->method();

	delete decoratorA;
	delete decoratorB;
	delete concreteComponent;
}