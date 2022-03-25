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
#include <netinet/ip.h>	//sockaddr_in
#include <arpa/inet.h>	//inet_ntoa()

#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
// #include "../../cmds/numeric_replies.hpp"

#define USER_MAX 10


/*	This is the main class for the server : it groups the main info about it, 
*	like the address, password, channel list, member list	*/

namespace irc
{

class	Client;
class	Channel;
class	Message;

class   Server
{
	public :
		Server(int port, std::string password);
		~Server();

		int		start();
		void	setUpFds();
		void	connectionCheck();
		void	activityCheck();

	private :
		int						_port;					//port number for the server (set at the start by './ircserv *port* *password*')
		std::string				_password;				//needed password to connect to the server (set at the start by './ircserv *port* *password*') then rotixed
		bool					_on;					//status
		Client*					_clients[USER_MAX];		//list of all the users on the channel
		int						_mainSocket;
		struct sockaddr_in		_address;				//address structure with address family, port and IP address
		size_t					_addressSize;
		fd_set 					_clientFds;				//structure containing the fds used
		int						_socketFd;				//temp storage for the use of one socket
		int						_fdMax;	
		int						_fdReady;				//used to store an fd when it is ready to receive/send 
		int						_newSocket;
		std::vector<Channel*>	_channels;				//list of all the channels on the server

	public :
		int	const &							getPort() const;
		std::string							getPassword() const;
		int const &							getRotKey() const;
		void								setRotKey(int key);
		std::vector<Channel*>				getChannels();			//used by server command /list that shows all member channels
		std::vector<Client*>				getClients();

		//channel management
		void								addChannel(Channel* chan);
		void								rmChannel(Channel* chan);
		Channel*							findChannel(Channel* chan);

		//user management
		void								addClient(Client* client);
		void								rmClient(Client* client);
		Client*								findClient(Client* client);	



	private :
		Server();

		int									_rotKey;		//randomized key for password rotation algo
		std::string							_operLog;		//operator login
		std::string							_operPass;		//operator password
		struct timeval						_timeout;		//time before the server closes without activity
		time_t								_startTime;		//time of server start

		//password encryption
		std::string							ft_rotix(std::string pass);		
		// std::string							ft_unrotix();
};


}   //namespace end

#endif
