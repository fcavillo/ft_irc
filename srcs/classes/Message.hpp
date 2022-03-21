#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Client.hpp"

/*	This is the main class for the Message : it groups the main info about it, 
*	like the sender, receiver, command called and command map	*/

namespace irc
{

class   Message
{
	public :
		Message(std::string fullCommand);	//the message is created with the whole command : /say "hi guys"
		~Message();

		std::string* const &	getCommand() const;
		irc::Client*			getSender() const;
		irc::Client*			getReceiver() const;
		void					setSender();
		void					setReceiver();		
		
		void					initCommands();
		void					fillCommand(std::string fullCommand);


	private :
		Message();

		std::string						_fullCommand;	//full sent command, before splitting
		std::string*					_splitCommand;	//all the split info of the command : 'say', 'hi guys'
		// std::map<std::string, pointer>	_commandList;	//list of all the commands the server can do
		irc::Client*	 				_sender;	
		irc::Client*					_receiver;	

};


}   //namespace end

#endif