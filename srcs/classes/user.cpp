#include "User.hpp"

User::User() : _oper(0)
{
	return ;
}

User::~User()
{
	return ;
}

/*	GETTERS & SETTERS	*/

std::string const &		User::getUsername() const
{
	return (this->_username);
}

std::string const &		User::getNick() const
{
	return (this->_nick);
}

std::string const &		User::getRealName() const
{
	return (this->_realName);
}

bool					User::getOper()
{
	return (this->_oper);
}

void					User::setUsername(std::string username)
{
	this->_username = username;
	return ;
}

void					User::setNick(std::string nick)
{
	this->_nick = nick;
	return ;
}

void					User::setRealName(std::string realName)
{
	this->_realName = realName;
	return ;
}

void					User::setOper(bool oper)
{
	this->_oper = oper;
	return ;
}