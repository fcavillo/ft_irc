#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#include "Channel.hpp"
#include "User.hpp"


/*	This is the main class for the server : it groups the main info about it, 
*	like the address, password, channel list, member list	*/

namespace irc
{

class   Server
{
	public :
		Server(char* port, char* password);
		~Server();


		int	const &							getPort() const;
		std::string const &					getPassword() const;
		std::map<std::string, Channel*>		getChannels();			//used by server command /list that shows all member channels
		std::map<std::string, User*>		getUsers();

		//channel management
		bool								addChannel(Channel* chan);
		int									rmChannel(std::string name);
		Channel*							findChannel(std::string name);

		//user management
		bool									addUser(User* user);
		int									rmUser(std::string nick);
		User*								findUser(std::string nick);		

	private :
		Server();

		std::map<std::string, User*>		_users;			//list of all the users on the channel, the pair is <userNick, address>
		std::map<std::string, Channel*>		_channels;		//list of all the channels on the server, the pair is <channelName, address>
		std::string 						_password;		//needed password to connect to the server (set at the start by './ircserv *port* *password*') then rotixed
		int									_rotKey;
		int									_port;			//port number for the server (set at the start by './ircserv *port* *password*')
};


}   //namespace end

#endif