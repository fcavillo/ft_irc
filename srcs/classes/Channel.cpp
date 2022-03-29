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

std::vector<irc::Client*>			irc::Channel::getClients()
{
	return (this->_clients);
}

/*	CLIENT MANAGEMENT	*/

void					irc::Channel::addClient(irc::Client* client)
{
	this->_clients.push_back(client);	
}

void					irc::Channel::rmClient(irc::Client* client)
{
	std::vector<Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end() || *(it) != client ; it++);	
	if (it == this->_clients.end())		//the client is not found
		return ;
	this->_clients.erase(it);			//erase only takes an iterator
}

irc::Client*				irc::Channel::findClient(irc::Client* client)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i] == client)
			return (_clients[i]);
	}
	return (NULL);
}