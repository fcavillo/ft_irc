#include "Client.hpp"

irc::Client::Client(Server* server) : _server(server)
{
	(void)_server;
	return ;
}

irc::Client::~Client()
{
	return ;
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

std::string	const &		irc::Client::getAddress() const
{
	return (this->_address);
}

void					irc::Client::setAddress(std::string address)
{
	_address = address;
	return ;
}

std::string &			irc::Client::getBufferLine() 
{ 
	return (this->_bufferLine); 
}


std::string const &		irc::Client::getUsername() const
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

void					irc::Client::setUsername(std::string username)
{
	this->_username = username;
	return ;
}

void					irc::Client::setNick(std::string nick)
{
	this->_nick = nick;
	return ;
}

void					irc::Client::setRealName(std::string realName)
{
	this->_realName = realName;
	return ;
}

void					irc::Client::setOper(bool oper)
{
	this->_oper = oper;
	return ;
}