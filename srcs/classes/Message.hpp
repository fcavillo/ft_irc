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


	public :

		std::string* const &	getCommand() const;
		irc::Client*			getSender() const;
		irc::Client*			getReceiver() const;
		void					setReceiver();		
		
		void					initCommands();
		void					fillCommand(std::string fullCommand);


	private :
		Message();

		std::string*					_splitCommand;		//all the split info of the command : 'say', 'hi guys'

		irc::Client*					_receiver;	

};


}   //namespace end

#endif