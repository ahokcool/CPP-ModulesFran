# include "FragTrap.hpp"

FragTrap::FragTrap(void): ClapTrap()
{
	std::cout << PURPLE << "FragTrap default constructor called" << RESET << std::endl;
}

FragTrap::FragTrap(const FragTrap &src): ClapTrap(src)
{
	std::cout << PURPLE << "FragTrap copy constructor called" << RESET << std::endl;
	*this = src;
}

FragTrap::FragTrap(const std::string name): ClapTrap(name)
{
	std::cout << PURPLE << "FragTrap constructor called" << RESET << std::endl;
	_hp = 100;
	_ep = 100;
	_attack_damage = 30;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
	if (this != &src)
		this->ClapTrap::operator=(src);
	return (*this);
}

FragTrap::~FragTrap(void)
{
	std::cout << PURPLE << "FragTrapS destructor called" << RESET << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (this->_hp <= 0)
		return ;
	std::cout << GREEN << this->_name << "requests highfive." << RESET << std::endl;
}

void FragTrap::attack(const std::string& target)
{
	if (this->_hp <= 0)
		return ;
	if (_ep == 0)
	{
		std::cout << PURPLE << _name << "doesnt have enough energy points to attack " << target << RESET << std::endl;
		return ;
	}
	std::cout << CYAN <<  "FragTrap " << _name << " attacks " << target << ", causing " << _attack_damage
		<< " points of damage!" << RESET << std::endl;
	_ep--;
}