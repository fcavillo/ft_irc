#include "Client.hpp"
#include "Message.hpp"

irc::Client::Client(Server* server) : _oper(0), _registered(0), _logged(1), _realName("localhost") , _server(server) , _mode("wi")
{
	(void)_server;
	return ;
}

irc::Client::~Client()
{
	return ;
}

/*	FUNCTIONS	*/

void					irc::Client::addLog(std::string line)
{
	this->_logs.push_back(line);
}

void					irc::Client::sendMsg(std::string msg)
{
	std::cout << "-> Socket[" << _socket << "] : " << msg << std::endl;
	send(_socket, (msg + "\r\n").c_str(), (msg + "\r\n").length(), 0);	//send, on the client socket, the char* str wth no flag
}

void					irc::Client::leaveChannel(irc::Channel* chan)
{
	chan->rmClient(this);
}

void					irc::Client::leaveAllChannels()
{


	for (std::vector<Channel*>::iterator it = _membership.begin(); it != _membership.end() ; it++)
	{
		leaveChannel(*(it));
		if (_membership.size() == 0)
			return ;
	}
}

void					irc::Client::leaveServer()
{
	_server->rmClient(this);
}


/*	GETTERS & SETTERS	*/

int	const &				irc::Client::getSocket() const
{
	return (this->_socket);
}

void					irc::Client::setSocket(int sd)
{
	_socket = sd;
	return ;
}

irc::Server*			irc::Client::getServer()
{
	return (_server);
}

std::string	const &		irc::Client::getAddress() const
{
	return (this->_address);
}

void					irc::Client::setAddress(std::string address)
{
	_address = address;
	return ;
}

void					irc::Client::setPass(std::string pass)
{
	_password = pass;
	return ;
}

std::string &			irc::Client::getPass() 
{ 
	return (this->_password); 
}

std::string &			irc::Client::getBufferLine() 
{ 
	return (this->_bufferLine); 
}

std::string const &		irc::Client::getUsername() const
{
	return (this->_username);
}

std::string				irc::Client::GetUsername()
{
	return (this->_username);
}

std::string const &		irc::Client::getNick() const
{
	return (this->_nick);
}

std::string const &		irc::Client::getRealName() const
{
	return (this->_realName);
}

bool const &			irc::Client::getOper() const
{
	return (this->_oper);
}

bool					irc::Client::getOper()
{
	return (this->_oper);
}



void					irc::Client::setUsername(std::string username)
{
	this->_username = username;
}

void					irc::Client::setNick(std::string nick)
{
	this->_nick = nick;
}

void					irc::Client::setRealName(std::string realName)
{
	this->_realName = realName;
}

void					irc::Client::setOper(bool oper)
{
	this->_oper = oper;
}

void					irc::Client::setRegistered(bool b)
{
	if (b == true)
	{
		std::cout << "User " << getNick() << " successfully registered !" << std::endl;
	}
	this->_registered = b;

}

bool					irc::Client::getRegistered()
{
	return (this->_registered);
}

bool					irc::Client::checkRegistered()
{
	if (getUsername() != "")
		std::cout << "user : " << _username << std::endl;
	if (_password != "" )
		std::cout << "pass : " << _password << std::endl;
	if (_nick != "")
		std::cout << "nick : " << _nick << std::endl;				
	if (getUsername() != "" && getPass() != "" && getPass() == getServer()->getPassword() && getNick() != "" && this->_registered == false)
		setRegistered(true);
	
	return (this->_registered);
}

void					irc::Client::setLogged(bool b)
{
	this->_logged = b;
}

bool					irc::Client::getLogged()
{
	return (this->_logged);
}

void						irc::Client::addMembership(irc::Channel* chan)
{
	for (std::vector<Channel*>::iterator it = _membership.begin(); it != _membership.end() ; it++)
		if (*(it) == chan)
			return ;
	_membership.push_back(chan);
}

void						irc::Client::rmMembership(irc::Channel* chan)
{
	std::vector<Channel*>::iterator	it = _membership.begin();

	for (; it != _membership.end() && (*it) != chan ; it++);	
	if (it == this->_membership.end())		//the client is not found
	{
		return ;
	}
	this->_membership.erase(it);			//erase only takes an iterator	
}

std::vector<irc::Channel*>	irc::Client::getMembership()
{
	return (_membership);
}


// AJOUT labintei


bool	ftFind(char c, std::string s)
{
	for(size_t e = 0; s[e] != '\0'; e++)
	{
		if(s[e] == c)
			return(true);
	}
	return(false);
};


void						irc::Client::setMode(std::string s)
{
	if(s != "" && s[0] == '+')
	{
		for(int i = 1; s[i] != '\0' ; i++)
		{
			if(!(ftFind(s[i], this->_mode)))
				this->_mode += s[i];
		}
	}
}

void						irc::Client::rmMode(std::string s)
{
	std::string		replace;
	std::string		base(this->_mode);

	if(s != "" && s[0] == '-')
	{
		for(int i = 0; base[i] != '\0' ; i++)
		{
			if(!(ftFind(base[i], s)))
				replace += base[i];
		}
	}
	this->_mode.clear();
	this->_mode = replace;

}

std::string					irc::Client::getMode(void)
{
	return this->_mode;
}

