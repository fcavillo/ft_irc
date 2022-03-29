#include <iostream>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Client.hpp"
#include "Server.hpp"

/*	This is the main class for the Message : it groups the main info about it, 
*	like the sender, receiver, command called and command map	*/

namespace irc
{

class	Client;
class	Server;

class   Message
{
	public :
		Message(std::string line, Server *data, Client *user);
		~Message();

	private :
		irc::Server*			_server;
		irc::Client*	 		_sender;	
		std::string				_fullCommand;	//full sent command, before splitting

	// AFTER PARSING
		std::string					_prefix;
		std::string					_cmds;
		std::vector<std::string>	_params;
	// retour charriot mais on s en fiche

		std::vector<std::string>	v_split(std::string line);
		Message();

	public :

		irc::Client*			getSender() const;
//		irc::Client*			getnonconstSender();
		irc::Server*			getServer()	const;
//		irc::Server*			getnonconstServer();
		void					initCommands();
//		void					messageparse(std::string line, Server *server, Client *sender)
		void					parse(std::string line);


};


}   //namespace end

#endif
