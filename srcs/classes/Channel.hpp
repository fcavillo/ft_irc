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

		void							setName(std::string name);
		void							setPass(std::string pass);
		std::string						getPass();
		void							addClient(Client* client);
		void							rmClient(Client* client);
		Client*							findClient(Client* client);
		Client*							getCreator();
		std::string 					clientList();

		bool							isClient(Client* client);
		bool							isOper(Client* client);

		// ban valid mais pas le reste
		bool							isBan(Client* client);
		std::string						getName();

		// ADD lauranne
		
		void							addBan(Client*	client);
		std::vector<Client*>			getBan();
		void							setTopic(std::string	s);
		Client*							findClientNick(std::string nick);


		void						setMode(std::string s);
		void						rmMode(std::string s);
		std::string					getMode(void);

		// ADD labintei

		void						addOpper(Client* client);
		void						rmOpper(Client* client);
		std::vector<Client*>		getOpper();

		void						setUserlimit(int n);
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

		// ADD labintei
		int									_userlimit;
};


}   //namespace end

#endif
