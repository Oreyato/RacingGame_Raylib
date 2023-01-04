#include <iostream>
using namespace std;

class Animal
{
public:
	Animal();
	virtual ~Animal();

	void makeNoise() { cout << "Noise" << endl; }

private:

};

Animal::Animal()
{
}

Animal::~Animal()
{
}

class Cat : public Animal
{
public:
	Cat();
	~Cat();

	void meow() { cout << "Meow" << endl; }

protected:

};

Cat::Cat()
{
}

Cat::~Cat()
{
}

void poke(Animal* animal) {
	animal->makeNoise();
}

const void pokeRef(Animal& animal) {
	animal.makeNoise();
}

int main(int argc, char* argv[])
{
	Animal* genericAnimal = new Animal;
	Cat* kitty = new Cat;

	poke(kitty);

	Cat felix;

	pokeRef(felix);

    return 0;
}