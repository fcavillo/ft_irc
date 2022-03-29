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

		void							addClient(Client* client);
		void							rmClient(Client* client);
		Client*							findClient(Client* client);

	private :
		Channel();

		std::vector<Client*>				_clients;		//list of all the users on the channel
		std::string 						_name;			//name of the channel (initialized by the user command '/join *name*')
};


}   //namespace end

#endif