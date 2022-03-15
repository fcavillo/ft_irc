#include "Server.hpp"

/*	PASSWORD CRYPTING/UNCRYPTING	*/

std::string		irc::Server::ft_rotix(char* pass)
{
	srand(time(NULL));

	setRotKey((rand()));

	std::string	s;

	for (int i = 0; pass[i]; i++)
		s.push_back((pass[i] + getRotKey()) % 94 + 32);

	return (s);
}

std::string		irc::Server::ft_unrotix()
{
	std::string	s;
	int			i = 0;

	for (std::string::iterator it = _password.begin(); it != _password.end(); it++)
	{
		s.push_back(_password[i++] - getRotKey());
		if (*(it) < 0)
			*(it) = 94 + *(it);
		(*it) = (*it) - 32;
	}
	return (s);
}

/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
irc::Server::Server(char* port, char* password)
{
	std::cout << "Creating Server" << std::endl;


	_password = ft_rotix(password);

		std::cout << "Password = " << password << ", key = " << getRotKey() << ", crypted = " << this->_password << ", decrypted = " << ft_unrotix() << std::endl;
	(void)port;
	return ;
}

irc::Server::~Server()
{
	return ;
}


/*	GETTERS & SETTERS	*/

int	const &						irc::Server::getPort() const
{
	return (this->_port);
}

std::string								irc::Server::getPassword() const
{
	return (this->_password);
}

std::map<std::string, irc::Channel*>	irc::Server::getChannels()
{
	return (this->_channels);
}

std::map<std::string, irc::User*>		irc::Server::getUsers()
{
	return (this->_users);
}

int const &								irc::Server::getRotKey() const
{
	return (this->_rotKey);
}

void									irc::Server::setRotKey(int key) 
{
	this->_rotKey = key;
	return ;
}

/*	CHANNEL MANAGEMENT	*/

/*	addChannel is used to create a new channel in the server, identified in the Server::_channels map by the pair <name, pointer to new Channel>,
*	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
bool					irc::Server::addChannel(irc::Channel* chan)
{
	std::pair<std::string, Channel*>	newPair;

	newPair = std::make_pair(chan->getName(), chan);
//<std::string, irc::Channel*>
	return ((this->_channels.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
}

/*	rmChannel is used to remove a Channel from the server (A_revoir : is it necessary ?)	*/
int						irc::Server::rmChannel(std::string name)
{
	this->_channels.erase(name);
	return (0);
}

/*	findChannel returns a pointer to the Channel whose name is sent in parameter, 
*	NULL if the Channel does not exist	*/
irc::Channel*				irc::Server::findChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it == this->_channels.end())		//the channel is not found
		return (NULL);

	return (it->second);
}

/*	USER MANAGEMENT	*/


/*	addUser is used to create a new user in the server, identified in the Server::_users map by the pair <nick, pointer to new User>,
*	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
bool						irc::Server::addUser(irc::User* user)
{
	std::pair<std::string, User*>	newPair;

	newPair = std::make_pair(user->getNick(), user);
//pair<std::string, User*>::
	return ((this->_users.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
}

/*	rmUser removes a user from the list of server members	*/
int						irc::Server::rmUser(std::string nick)
{
	this->_users.erase(nick);
	return (0);
}

/*	findUser returns a pointer to the User whose nick is sent in parameter, 
*	NULL if the User does not exist	*/
irc::User*					irc::Server::findUser(std::string nick)
{
	std::map<std::string, irc::User*>::iterator	it;

	it = this->_users.find(nick);
	if (it == this->_users.end())		//the user is not found
		return (NULL);

	return (it->second);
}

