#include "Channel.hpp"

irc::Client*		irc::Channel::getCreator()
{
	return(this->_creator);
}


/*
bool							isOper(Client* client);
{
	for(size_t i = 0; i < _oper.size(); i++)
	{
		if(_oppr[i] == client)
			return(true);
	}
	return(false);
}
*/

bool		irc::Channel::isBan(irc::Client* client)
{
	for(size_t i = 0; i < _oper.size(); i++)
	{
		if(_ban[i] == client)
			return(true);
	}
	return(false);
}



irc::Channel::Channel(std::string name) : _name(name)
{
	return ;
}

// irc::Channel::Channel(std::string name, mode) 	//désolé, commenté pour que ca compile :)

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

std::string						irc::Channel::getTopic()
{
	return (this->_topic);
}

/*	CLIENT MANAGEMENT	*/

void					irc::Channel::addClient(irc::Client* client)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end() ; it++)	//checks if user already is member
		if (*(it) == client)
			return ;
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
	for (size_t i = 0; i < _oper.size(); i++)
	{
		if(_oper[i] == client)
			return (_clients[i]);
	}
	return (NULL);
}

std::string				irc::Channel::clientList()
{
	std::string	list;

	for (size_t i = 0; i < _clients.size(); i++)
		list.append(" " + _clients[i]->getNick());
	
	return (list);
}