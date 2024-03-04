# include "Dog.hpp"

Dog::Dog(void) : AAnimal()
{
	std::cout << GREEN << "Its a Dog!" << RESET << std::endl;
	this->type = "Dog";
	_brain = new Brain();
}

Dog::Dog(const Dog &src) : AAnimal(src), _brain(NULL)
{
	std::cout << GREEN << "Its another Dog!" << RESET << std::endl;
	*this = src;
}

Dog &Dog::operator=(const Dog &src)
{
	if (this == &src)
		return (*this);
	this->AAnimal::operator=(src);
	if (this->_brain)
		delete _brain;
	this->_brain = new Brain(*src._brain);
	return (*this);
}

Dog::~Dog(void)
{
	delete _brain;
	std::cout << GREEN << "Dog died" << RESET << std::endl;
}

void Dog::makeSound() const
{
	std::cout << CYAN << type << ": Woof Woof" << RESET << std::endl;
}

Brain	*Dog::getBrain() const
{
	return (_brain);
}