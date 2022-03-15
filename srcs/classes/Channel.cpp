#include "Channel.hpp"

irc::Channel::Channel(std::string name) : _name(name)
{
	return ;
}

irc::Channel::~Channel()
{
	return ;
}

/*	GETTERS AND SETTERS	*/

std::string const &				irc::Channel::getName() const
{
	return (this->_name);
}

std::map<std::string, irc::User*>	irc::Channel::getUsers()
{
	return (this->_users);
}

/*	USER MANAGEMENT	*/

/*	addUser is used to create a new user in the channel, identified in the Channel::_users map by the pair <nick, pointer to new User>,
*	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
int								irc::Channel::addUser(irc::User* user)
{
	std::pair<std::string, irc::User*>	newPair;

	newPair = make_pair(user->getNick(), user);

	return ((this->_users.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
}

/*	rmUser removes a user from the list of channel members	*/
int								irc::Channel::rmUser(std::string nick)
{
	this->_users.erase(nick);
	return (0);
}

/*	findUser returns a pointer to the User whose nick is sent in parameter, 
*	NULL if the User does not exist	*/
irc::User*							irc::Channel::findUser(std::string nick)
{
	std::map<std::string, irc::User*>::iterator	it;

	it = this->_users.find(nick);
	if (it == this->_users.end())		//the user is not found
		return (NULL);

	return (it->second);
}