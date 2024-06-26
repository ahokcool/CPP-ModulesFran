# include "BitcoinExchange.hpp"

/* =============== Constructors ================== */

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {(void) src;}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {(void) src; return (*this);}
BitcoinExchange::~BitcoinExchange(){}

/* =============== Methods ================== */

float BitcoinExchange::checkValue(const std::string &str, bool isDB)
{
    int i = 0;
    while (str[i] && str[i] != ',' && str[i] != '|')
        i++;
    if (str[i] == ',' || str[i] == '|')
        i++;
    while (str[i] && std::isspace(str[i]))
        i++;
    std::string sub = str.substr(i);
    float value = std::strtof(sub.c_str(), NULL);

    if (errno == ERANGE || value == HUGE_VALF || value == -HUGE_VALF)
        throw BitcoinExchange::FloatOverFlow();
    if (isDB)
        return (value);
    if (value < 0)
        throw BitcoinExchange::NegativeException();
    if (value > 1000)
        throw BitcoinExchange::MultiplierTooHighException();
    return (value);
}

void BitcoinExchange::checkDate(const std::string &date)
{
    float year = std::strtof(date.c_str(), NULL);
    if (year < 2009)
        throw BitcoinExchange::BadInputException(date);
    int month = static_cast<int>(std::strtof((date.substr(5, 2)).c_str(), NULL));
    int day = static_cast<int>(std::strtof((date.substr(8, 2).c_str()), NULL));

    if (month < 1 || month > 12)
        throw BitcoinExchange::BadInputException(date);
    
    if (day == 0)
        throw BitcoinExchange::BadInputException(date);

    switch (month)
    {
        case 2:
            if ((static_cast<int>(year) % 4 != 0) && day > 28)
                throw BitcoinExchange::BadInputException(date);
            else if ((static_cast<int>(year) % 4 == 0) && day > 29)
        break;

        case 4: case 6: case 9: case 11:
            if (day > 30)
                throw BitcoinExchange::BadInputException(date);
    default:
            if (day > 31)
                throw BitcoinExchange::BadInputException(date);
        break;
    }
}

void BitcoinExchange::parserDB(const std::string &line)
{
    int i = 0;

    for (; i < 4; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    if (line[i++] != '-')
        throw BitcoinExchange::BadInputException(line);
    for (; i < 7; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    if (line[i++] != '-')
        throw BitcoinExchange::BadInputException(line);
    for (; i < 10; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    if (line[i++] != ',')
        throw BitcoinExchange::BadInputException(line);
    if (line[i] == '+')
        i++;
    while(line[i] && std::isdigit(line[i]))
        i++;
    if (!line[i])
        return ;
    if (line[i] == '.')
        while(line[++i] && std::isdigit(line[i]))
            ;
    if (line[i])
        throw BitcoinExchange::BadInputException(line);
}

void BitcoinExchange::parserInput(std::string &line)
{
    int i = 0;

    while (std::isspace(line[i]))
        i++;
    line = (line.substr(i)).c_str();
    i = 0;

    for (; i < 4; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    if (line[i++] != '-')
        throw BitcoinExchange::BadInputException(line);
    for (; i < 7; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    if (line[i++] != '-')
        throw BitcoinExchange::BadInputException(line);
    for (; i < 10; i++)
        if (!std::isdigit(line[i]))
            throw BitcoinExchange::BadInputException(line);
    while (std::isspace(line[i]))
        i++;
    if (line[i++] != '|')
        throw BitcoinExchange::BadInputException(line);
    while (std::isspace(line[i]))
        i++;
    if (line[i] == '-' || line[i] == '+')
        i++;
    while(line[i] && std::isdigit(line[i]))
        i++;
    if (!line[i])
        return ;
    if (line[i] == '.')
        while(line[++i] && std::isdigit(line[i]))
            ;
    
    while (std::isspace(line[i]))
        i++;

    if (line[i])
        throw BitcoinExchange::BadInputException(line);
}

void BitcoinExchange::extractDB()
{
    std::ifstream ifs("data.csv");
    std::string buffer;

    if (ifs.fail())
        throw BitcoinExchange::FileOpeningError();
    std::getline(ifs, buffer);
    while (1)
    {
        std::getline(ifs, buffer);
        if (ifs.eof())
            break ;
        parserDB(buffer);
        checkDate(buffer);
        _bitcoinMap[buffer.substr(0, 10)] = checkValue(buffer, true);
    }
}

void BitcoinExchange::displayMap()
{
        std::cout << "++\n++++++++++++++ DATA BASE +++++++++++++++++++\n\n";
        std::map<std::string, float>::iterator it = _bitcoinMap.begin();
        for (; it != _bitcoinMap.end(); it++)
            std::cout << it->first << ": " << it->second << std::endl;   
}

void BitcoinExchange::Exchange(char *path)
{
    std::string     buffer;
    std::ifstream   ifs (path);
    float           result;
    float           multiplier;
    std::string     date;
    std::map<std::string, float>::iterator lowIt;

    if (ifs.fail())
        throw BitcoinExchange::FileOpeningError();
    
    if (ifs.fail())
        throw BitcoinExchange::FileOpeningError();
    std::getline(ifs, buffer);
    while (1)
    {
        std::getline(ifs, buffer);
        if (ifs.eof())
            break ;
        try
        {
            parserInput(buffer);
            checkDate(buffer);
            date = buffer.substr(0, 10);
            multiplier = checkValue(buffer, false);
            lowIt = _bitcoinMap.lower_bound(date);
			// TODO: check how it works"
			// https://en.cppreference.com/w/cpp/container/map/lower_bound
			// maybe this is easier ;)  ???
			// https://en.cppreference.com/w/cpp/container/map/upper_bound
            result = lowIt->second * multiplier;

            std::cout << date << " => " << multiplier << " = " << std::fixed << std::setprecision(2) << result << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << e.what();
        }
    }
}


/* =============== Exceptions ================== */

const char *BitcoinExchange::MultiplierTooHighException::what(void) const throw()
{
    return("Error: too large a number.\n");
}

const char *BitcoinExchange::FileOpeningError::what(void) const throw()
{
    return("File opening error\n");
}

const char *BitcoinExchange::FloatOverFlow::what(void) const throw()
{
    return("Value is out of range\n");
}

const char *BitcoinExchange::BadInputException::what() const throw()
{
    return(_err.c_str());
}

const char *BitcoinExchange::NegativeException::what(void) const throw()
{
    return("Error: not a positive number.\n");
}

BitcoinExchange::BadInputException::BadInputException(const std::string &date)
{
    std::string msg = "Error: bad input: ";
    _err = msg + date;
    _err.append("\n");
}

BitcoinExchange::BadInputException::~BadInputException() throw() {}
