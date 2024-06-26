# include "ICharacter.hpp"
# include "AMateria.hpp"

# ifndef CHARACTER_HPP
# define CHARACTER_HPP

# define NBR_SLOTS 4

class Character : public ICharacter
{
	public:

		Character(void);
		Character(const Character &src);
		Character &operator=(const Character &src);
		virtual ~Character();
		Character(const std::string &name);


		virtual std::string const	&getName() const;
		virtual void				equip(AMateria* m);
		virtual void				unequip(int idx);
		virtual void				use(int idx, ICharacter& target);
	
		void	DisplaySlots() const;
		void	DisplayFloor() const;

	protected:

			std::string _name;
			AMateria	*_slots[NBR_SLOTS];
			AMateria	*_floor[NBR_SLOTS];
};

# endif