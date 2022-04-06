#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <utility>

#include "Client.hpp"


/*	This is the main class for the Channel : it groups the main info about it, 
*	like the name, user list	*/

namespace irc
{

class	Client;

class   Channel
{
	public :
		Channel(std::string name);
		~Channel();

		std::string const &				getName() const;
		std::vector<Client*>			getClients();
		std::string						getTopic();

		void							setPass(std::string pass);
		std::string						getPass();
		void							addClient(Client* client);
		void							rmClient(Client* client);
		Client*							findClient(Client* client);
		Client*							getCreator();
		bool							isClient(Client* client);
		bool							isOper(Client* client);
		bool							isBan(Client* client);
		std::string						getName();

	private :
		Channel();

		Client*								_creator;
		std::vector<Client*>				_oper;
		std::vector<Client*>				_ban;
		std::vector<Client*>				_clients;		//list of all the users on the channel
		std::string 						_name;			//name of the channel (initialized by the user 		command '/join *name*')
		std::string							_topic;

		std::string							_mode;
		std::string							_pass;
};


}   //namespace end

#endif
