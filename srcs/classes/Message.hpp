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

		std::vector<std::string>	v_split(std::string line);
		Message();

	public :

		irc::Client*			getSender() const;
		
		void					initCommands();
		void					fillCommand(std::string fullCommand);




};


}   //namespace end

#endif