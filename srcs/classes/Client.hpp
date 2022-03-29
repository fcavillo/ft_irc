
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstring>

#include "Server.hpp"


/*	This is the main class for the client : it groups the main info about it, 
*	like the username, nickname, real name, status	*/


namespace irc
{

class	Server;

class   Client
{
	public :
		Client(Server* server);
		~Client();

	/*	Functions	*/	
		void					sendMsg(std::string msg);


	/* Getters/setters	*/
	//socket
		int	const & 			getSocket() const;
		void					setSocket(int sd);
	//address
		std::string	const & 	getAddress() const;
		void					setAddress(std::string address);
	//password
		void					setPass(std::string pass);
		std::string	&			getPass();
	//registered
		void					setRegistered(bool b);
		bool					getRegistered();
		bool					checkRegistered();
	//logged
		void					setLogged(bool b);
		bool					getLogged();
	//username
		void					setUsername(std::string username);
		std::string const &		getUsername() const;
	//nickname
		std::string const &		getNick() const;
		void					setNick(std::string nick);
	//real name
		std::string const &		getRealName() const;
		void					setRealName(std::string realName);
	//operator status	
		bool const &			getOper() const;
		void					setOper(bool oper);					//used in client command /oper
	//buffer for the command line
		std::string &			getBufferLine();

	private :

		bool			_oper;										//1 if client is operator, 0 by default
		bool			_registered;								//1 if client is registered (nick + pass + username), 0 by default
		bool			_logged;									//0 if client disconnects, 0 by default
		std::string 	_username;
		std::string		_nick;
		std::string		_realName;
		std::string		_password;
		std::string		_address;
		int				_socket;									//socket on which the client is
		Server*			_server;									//pointer to the global server
		std::string 	_bufferLine; 

};

}   //namespace end


#endif