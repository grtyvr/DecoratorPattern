#include <iostream>
class Beverage {
	public:
		virtual ~Beverage() {}
		virtual float cost() = 0;
};

class HouseBlend : public Beverage {
	private:
		float cost_ = 1.50;
	public:
		virtual ~HouseBlend() {}
		float cost() {
			std::cout << "cost of house blend is " << cost_ << std::endl;
			return cost_;
		}
};

class CondimentDecorator : Beverage {
	private:
		Beverage *beverage_;
	public:
		~CondimentDecorator() {};
		CondimentDecorator(Beverage *beverage) : beverage_(beverage) {}
		virtual float cost() override {
			return beverage_->cost();
		}

};

class SteamedMilk : public Beverage {
	private:
		// a reference to the Component that we will be decorating
		Beverage *beverage_;
		float cost_ = 0.25;
	public:
		// the interface conforms to the Component interface
		~SteamedMilk() {}
		SteamedMilk(Beverage *beverage) : beverage_(beverage) {}
		float cost() {
			float total_cost = this->cost_ + beverage_->cost();
			std::cout << "Steamed milk adds " << cost_ << std::endl;
			return total_cost;
		}
};

class Mocha : public Beverage {
	private:
		Beverage *beverage_;
		float cost_ = 0.5;
	public:
		Mocha(Beverage *beverage) : beverage_(beverage) {}
		float cost() {
			float total_cost = this->cost_ + beverage_->cost();
			std::cout << "mocha adds " << cost_ << std::endl;
			return total_cost;
		}
};


int main(int argc, char *argv[])
{
	float cost;

	HouseBlend *beverageA = new HouseBlend();
	Mocha *mocha = new Mocha(beverageA);

	Beverage *beverage = mocha;
	cost = mocha->cost();
	std::cout << "Total cost " << cost << std::endl;

	SteamedMilk *withSteamed = new SteamedMilk(mocha);
	cost = withSteamed->cost();
	std::cout << "Total cost " << cost << std::endl;

	delete mocha;
	delete withSteamed;
	delete beverageA;

}