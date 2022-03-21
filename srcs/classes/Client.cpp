#include "Client.hpp"

irc::Client::Client() : _oper(0)
{
	return ;
}

irc::Client::~Client()
{
	return ;
}

/*	GETTERS & SETTERS	*/

int	const &				irc::Client::getSocketFd() const
{
	return (this->_socketFd);
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