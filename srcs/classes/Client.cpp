#include "Client.hpp"

irc::Client::Client(Server* server) : _oper(0), _registered(0), _logged(1), _server(server)
{
	(void)_server;
	return ;
}

irc::Client::~Client()
{
	return ;
}

/*	FUNCTIONS	*/


void					irc::Client::sendMsg(std::string msg)
{
	std::cout << "-> Socket[" << _socket << "] : " << msg << std::endl;
	send(_socket, (msg + "\r\n").c_str(), (msg + "\r\n").length(), 0);	//send, on the client socket, the char* str wth no flag
}

// void					irc::Client::welcome()
// {
// 	sendMsg(Message_p(RPL_WELCOME, RPL_WELCOME_MSG(sender->getNick(), sender->getUsername(),server->getServername())));
// }

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

bool					irc::Client::getOpper()
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
		std::cout << "User " << getNick() << " successfully registered !" << std::endl;
	this->_registered = b;
}

bool					irc::Client::getRegistered()
{
	return (this->_registered);
}

bool					irc::Client::checkRegistered()
{
	if (getUsername() != "" && getPass() != "" && getNick() != "" && this->_registered == false)
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
