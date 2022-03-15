#include "User.hpp"

irc::User::User() : _oper(0)
{
	return ;
}

irc::User::~User()
{
	return ;
}

/*	GETTERS & SETTERS	*/

std::string const &		irc::User::getUsername() const
{
	return (this->_username);
}

std::string const &		irc::User::getNick() const
{
	return (this->_nick);
}

std::string const &		irc::User::getRealName() const
{
	return (this->_realName);
}

bool const &			irc::User::getOper() const
{
	return (this->_oper);
}

void					irc::User::setUsername(std::string username)
{
	this->_username = username;
	return ;
}

void					irc::User::setNick(std::string nick)
{
	this->_nick = nick;
	return ;
}

void					irc::User::setRealName(std::string realName)
{
	this->_realName = realName;
	return ;
}

void					irc::User::setOper(bool oper)
{
	this->_oper = oper;
	return ;
}