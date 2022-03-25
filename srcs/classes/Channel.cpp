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

std::map<std::string, irc::Client*>	irc::Channel::getClients()
{
	return (this->_clients);
}

// /*	Client MANAGEMENT	*/

// /*	addClient is used to create a new Client in the channel, identified in the Channel::_clients map by the pair <nick, pointer to new Client>,
// *	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
// int								irc::Channel::addClient(irc::Client* Client)
// {
// 	std::pair<std::string, irc::Client*>	newPair;

// 	newPair = make_pair(Client->getNick(), Client);

// 	return ((this->_clients.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
// }

// /*	rmClient removes a Client from the list of channel members	*/
// int								irc::Channel::rmClient(std::string nick)
// {
// 	this->_clients.erase(nick);
// 	return (0);
// }

// /*	findClient returns a pointer to the Client whose nick is sent in parameter, 
// *	NULL if the Client does not exist	*/
// irc::Client*							irc::Channel::findClient(std::string nick)
// {
// 	std::map<std::string, irc::Client*>::iterator	it;

// 	it = this->_clients.find(nick);
// 	if (it == this->_clients.end())		//the Client is not found
// 		return (NULL);

// 	return (it->second);
// }