#include <iostream>
#include <cstring>
#include <map>
#include <pair>

#include "Channel.hpp"
#include "User.hpp"


/*	This is the main class for the server : it groups the main info about it, 
*	like the address, password, channel list, member list	*/

namespace irc
{

class   Server
{
	public :
		Server(int port, std::string password);
		~Server();


		int	const &							getPort() const;
		std::string const &					getPassword() const;

		//channel management
		std::map<std::string, Channel*>		getChannels();					//used by server command /list that shows all member channels
		int									addChannel(Channel* chan);
		int									rmChannel(std::string name);
		Channel*							findChannel(std::string name);

		//user management
		std::map<std::string, User*>		getUsers();
		int									addUser(User* user);
		int									rmUser(std::string nick);
		User*								findUser(std::string nick);		

	private :
		Server();

		std::map<std::string, User*>		_users;			//list of all the users on the channel, the pair is <nick, address>
		std::map<std::string, Channel*>		_channels;		//list of all the channels on the server, the pair is <name, address>
		std::string 						_password;		//needed password to connect to the server (set at the start by './ircserv *port* *password*')
		int									_port;			//port number for the server (set at the start by './ircserv *port* *password*')
}



}   //namespace end