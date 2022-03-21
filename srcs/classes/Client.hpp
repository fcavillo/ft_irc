#include <iostream>
#include <cstring>

#ifndef CLIENT_HPP
#define CLIENT_HPP

/*	This is the main class for the client : it groups the main info about it, 
*	like the username, nickname, real name, status	*/

namespace irc
{

class   Client
{
	public :
		Client();
		~Client();

		int	const & 	getSocketFd() const;

	private :
		int		_socketFd;

	public :
		std::string const &		getUsername() const;
		std::string const &		getNick() const;
		std::string const &		getRealName() const;
		bool const &			getOper() const;
		void					setUsername(std::string clientname);
		void					setNick(std::string nick);
		void					setRealName(std::string realName);
		void					setOper(bool oper);					//used in client command /oper

	private :

		bool			_oper;										//1 if client is operator, 0 by default
		std::string 	_username;
		std::string		_nick;
		std::string		_realName;
		std::string		_password;
};

}   //namespace end

#endif