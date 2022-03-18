#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <map>
#include <utility>		//pair
#include <cstdlib>		//rand()
#include <ctime>		//timeval struct
#include <sys/time.h>	//select()
#include <cstdlib>		//atoi()
#include <csignal>		//signal()


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

		int		start();

	private :
		int						_port;			//port number for the server (set at the start by './ircserv *port* *password*')
		std::string				_password;		//needed password to connect to the server (set at the start by './ircserv *port* *password*') then rotixed
		bool					_on;			//





	public :
		int	const &							getPort() const;
		std::string							getPassword() const;
		int const &							getRotKey() const;
		void								setRotKey(int key);
		std::map<std::string, Channel*>		getChannels();			//used by server command /list that shows all member channels
		std::map<std::string, User*>		getUsers();

		//channel management
		bool								addChannel(Channel* chan);
		int									rmChannel(std::string name);
		Channel*							findChannel(std::string name);

		//user management
		bool								addUser(User* user);
		int									rmUser(std::string nick);
		User*								findUser(std::string nick);	



	private :
		Server();

		std::map<std::string, User*>		_users;			//list of all the users on the channel, the pair is <userNick, address>
		std::map<std::string, Channel*>		_channels;		//list of all the channels on the server, the pair is <channelName, address>
		int									_rotKey;		//randomized key for password rotation algo
		std::string							_operLog;		//operator login
		std::string							_operPass;		//operator password
		struct timeval						_timeout;		//time before the server closes without activity
		time_t								_startTime;		//time of server start

		/*	Sockets are similar to bidirectionnal pipes : a file that represents a network connection,
		*	stuff written in the socket are turned into network packets that are sent to the other host and port.
		*	Client sockets are used to send a request to the server socket,
		*	server sockets are used to accept requests, do an operation and send the result to the client	*/
		fd_set								_clientSockets;

		//password encryption
		std::string							ft_rotix(std::string pass);		
		// std::string							ft_unrotix();
};


}   //namespace end

#endif