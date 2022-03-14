#include <iostream>
#include <cstring>
#include <map>
#include <pair>

#include "Channel.hpp"


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
		std::map<std::string, Channel*>		getChannels();					//used by server command /list thatshozs all member channels
		int									addChannel(Channel* chan);
		int									rmChannel(std::string name);
		Channel*							findChannel(std::string name);

	private :
		Server();

//does it need a member list ?
		std::map<std::string, Channel*>		_channels;		//list of all the channels on the server, the pair is <name, address>
		std::string 						_password;		//needed password to connect to the server (set at the start by './ircserv *port* *password*')
		int									_port;			//port number for the server (set at the start by './ircserv *port* *password*')
}



}   //namespace end