#include "Channel.hpp"

void				irc::Channel::setTopic(std::string newtopic)
{
	if(this->_topic !=  "")
		this->_topic.clear();
	this->_topic = newtopic;

}

void				irc::Channel::setName(std::string name)
{
	this->_name = name;
}

void				irc::Channel::setUserlimit(int limit)
{
	this->_userlimit = limit;
}


irc::Client*				irc::Channel::findClientNick(std::string nick)
{
	for(std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if((*it)->getNick() == nick)
			return((*it));
	}
	return(NULL);


}


/*
irc::Client*		irc::Channel::findClientNick(std::string nick);
{
	for(std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if((*it)->getNick() == nick)
			return((*it));
	}
	return(NULL);
}

*/
irc::Client*		irc::Channel::getCreator()
{
	return(this->_creator);
}
/*
bool				irc::Channel::isOper(irc::Client* client);
{
	for(size_t i = 0; i < _oper.size(); i++)
	{
		if(_oppr[i] == client)
			return(true);
	}
	return(false);
}

bool				irc::Channel::isClient(irc::Client* client);
{
	if(this->isOper(client))
		return(true);
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if(_clients[i] == client)
			return(true);
	}
	return(false);
}

bool		irc::Channel::isBan(irc::Client* client)
{
	for(size_t i = 0; i < _oper.size(); i++)
	{
		if(_ban[i] == client)
			return(true);
	}
	return(false);
}*/


// set le mode a "n" par default
irc::Channel::Channel(std::string name) : _name(name), _mode("n")
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

std::vector<irc::Client*>					irc::Channel::getBan()
{
	return(this->_ban);
}
/*	CLIENT MANAGEMENT	*/

void					irc::Channel::addClient(irc::Client* client)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end() ; it++)	//checks if user already is member
		if (*(it) == client)
			return ;
	this->_clients.push_back(client);	
}

void					irc::Channel::addOpper(Client* client)
{
	addClient(client); // deja une secu dessus
	for (std::vector<Client*>::iterator it = _oper.begin(); it != _oper.end() ; it++)	//checks if user already is member
		if ((*it) == client)
			return  ;
	this->_oper.push_back(client);
}

void					irc::Channel::rmOpper(Client* client)
{
	std::vector<Client*>::iterator it;

	for (it = _oper.begin(); it != _oper.end() || *(it) != client ; it++)
	{
		if((*it) == client)
		{
			this->_oper.erase(it);
			return ;
		}
	}
}


void					irc::Channel::rmClient(irc::Client* client)
{
	std::vector<Client*>::iterator it;

	// PETITE MODIFICATION EFFACER OPPER EN PREMIER
	if(isOper(client) == true)
	{
		rmOpper(client);
	}
	for (it = _clients.begin(); it != _clients.end() || *(it) != client ; it++)
	{
		if((*it) == client)
		{
			client->rmMembership(this);
			this->_clients.erase(it);

			return ;
		}
	}
	//this->_clients.erase(it);			//erase only takes an iterator
}



/*
void					irc::Channel::rmClient(irc::Client* client)
{
	std::vector<Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end() || *(it) != client ; it++);
	if (it == this->_clients.end())		//the client is not found
		return ;
	this->_clients.erase(it);			//erase only takes an iterator
}*/

void					irc::Channel::setPass(std::string pass)
{
	this->_pass = pass;
}

std::string					irc::Channel::getPass()
{
	return this->_pass;
}

std::string					irc::Channel::getName()
{
	return this->_name;
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

bool		irc::Channel::isBan(irc::Client* client)
{
	for(size_t i = 0; i < _ban.size(); i++)
	{
		if(_ban[i] == client)
			return(true);
	}
	return(false);
}


bool		irc::Channel::isOper(irc::Client* client)
{

	for(size_t i = 0; i < _oper.size(); i++)
	{
		if(_oper[i] == client)
			return(true);
	}
	return(false);
}

bool		irc::Channel::isClient(irc::Client* client)
{
	if(this->isOper(client))
		return(true);
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if(_clients[i] == client)
			return(true);
	}
	return(false);
}

void	irc::Channel::addBan(irc::Client* client)
{
	this->getBan().push_back(client);
}

std::string				irc::Channel::clientList()
{
	std::string	list;

	for (size_t i = 0; i < _clients.size(); i++)
		list.append(" " + _clients[i]->getNick());
	
	return (list);
}


bool	ftFind1(char c, std::string s)
{
	for(size_t e = 0; s[e] != '\0'; e++)
	{
		if(s[e] == c)
			return(true);
	}
	return(false);
}

void						irc::Channel::setMode(std::string s)
{
	if(s != "" && s[0] == '+')
	{
		for(int i = 1; s[i] != '\0' ; i++)
		{
			if(!(ftFind1(s[i], this->_mode)))
				this->_mode += s[i];
		}
	}
}

void						irc::Channel::rmMode(std::string s)
{
	std::string		replace;
	std::string		base(this->_mode);

	if(s != "" && s[0] == '-')
	{
		for(int i = 0; base[i] != '\0' ; i++)
		{
			if(!(ftFind1(base[i], s)))
				replace += base[i];
		}
	}
	this->_mode.clear();
	this->_mode = replace;

}

std::string				irc::Channel::getMode(void)
{
	return this->_mode;
}

std::vector<irc::Client*>	irc::Channel::getOpper(void)
{
	return this->_oper;
}

