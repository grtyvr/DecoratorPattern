#include <iostream>
class Component {
	public:
		Component(){
		}
		virtual ~Component() {}
		virtual std::string method() const = 0;
		// etc...
};

class ConcreteComponent : public Component {
	public:
		ConcreteComponent () {
		}
		virtual ~ConcreteComponent() {}
		std::string method() const override {
			return "concrete component";
		}
		// etc...
};

class Decorator : public Component {
	private:
		// a reference to the Component that we will be decorating
		Component *component_;
	public:
		// the component we are decorating will manage destruction
		// store a reference to our decorated Component type.
		Decorator(Component *component) : component_(component) {}
		// the interface conforms to the Component interface
		// we can call the components method if we like.
		std::string method() const override {
			return component_->method();
		}
};

class ConcreteDecoratorA : public Decorator {
	public:
		ConcreteDecoratorA(Component *component) : Decorator(component) {}
		std::string method() const override{
			// add capabilities for this decorator
			// note that the Decorator::method() will resolve to the method of
			// the component object that was used to initialize this concrete
			// decorator.
			return "Decorator A (" + Decorator::method() + ")";
		}
};

class ConcreteDecoratorB : public Decorator {
	public:
		ConcreteDecoratorB( Component *component) : Decorator(component) {}
		std::string method() const override{
			// add capabilities for this decorator.
			// note that the Decorator::method() will resolve to the method of
			// the component object that was used to initialize this concrete
			// decorator.
			return "Decorator B (" + Decorator::method() + ")";
		}
};

int main(int argc, char *argv[])
{
	// create a concrete component that implements the interface of Component
	ConcreteComponent *concreteComponent = new ConcreteComponent();
	// create decorated versions
	// first decorate with ConcreteDecoratorA
	ConcreteDecoratorA *decoratorA = new ConcreteDecoratorA(concreteComponent);
	// take the decorated resulting object and pass that 
	// as a paramater to the ConcreteDecoratorB
	ConcreteDecoratorB *decoratorB = new ConcreteDecoratorB(decoratorA);
	// decorate the original ConcreteComponent with ConcreteDecoratorB
	ConcreteDecoratorB *decoratorC = new ConcreteDecoratorB(concreteComponent);

	Component *component = decoratorB;

	std::cout << component->method() << std::endl;
	std::cout << decoratorA->method() << std::endl;
	std::cout << concreteComponent->method() << std::endl;
	std::cout << decoratorB->method() << std::endl;
	std::cout << decoratorC->method() << std::endl;

	delete decoratorA;
	delete decoratorB;
	delete decoratorC;
	delete concreteComponent;
}