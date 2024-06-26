
# ifndef AFORM_HPP
# define AFORM_HPP

# include "Bureaucrat.hpp"

# define CYAN "\e[0;36m"
# define GREEN "\e[0;32m"
# define RED "\e[0;31m"
# define YELLOW "\e[0;33m"
# define PURPLE "\e[4;35m"
# define RESET "\e[0m"

class Bureaucrat;

class AForm
{
    public:

        AForm(void);
        AForm(const AForm &src);
        AForm(const std::string name, const int gts, const int gte);
        AForm &operator=(const AForm &src);
        virtual ~AForm();

        // Getters
        const std::string       &getName() const;
        bool                    getSignature() const;
        int                     getGradeToSign() const;
        int                     getGradeToExec() const;

        class GradeTooHighException : public std::exception{
            virtual const char *what() const throw();
        };

        class GradeTooLowException : public std::exception{
            virtual const char *what() const throw();
        };

        class FormPrevSignedException : public std::exception{
            virtual const char *what() const throw();
        };

        class FormUnsignedException : public std::exception{
            virtual const char *what() const throw();
        };

        void            beSigned(const Bureaucrat &bureaucrat);
        void            checkRequirements(const Bureaucrat &executor) const;
        virtual void    execute(Bureaucrat const & executor) const = 0;

    private:
        

        const std::string   _name;
        bool                _signature;
        const int           _gradeToSign;
        const int           _gradeToExec;
};

std::ostream &operator<<(std::ostream &o, AForm &src);

# endif