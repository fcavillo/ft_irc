#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#include "Client.hpp"


/*	This is the main class for the Channel : it groups the main info about it, 
*	like the name, user list	*/

namespace irc
{

class   Channel
{
	public :
		Channel(std::string name);
		~Channel();

		std::string const &				getName() const;
		std::map<std::string, Client*>	getClients();

		//user management
		int								addClient(Client* user);
		int								rmClient(std::string nick);
		Client*							findClient(std::string nick);

	private :
		Channel();

		std::map<std::string, Client*>		_clients;		//list of all the users on the channel, the pair is <nick, address>
		std::string 						_name;		//name of the channel (initialized by the user command '/join *name*')
};


}   //namespace end

#endif