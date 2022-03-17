#include "Server.hpp"

#include <cstdio>


/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
irc::Server::Server(int port, std::string password) :
_port(port),
_password(ft_rotix(password)),
_on(true)
{
	std::cout << "Creating Server - port : " << port << std::endl;

// 	//timeout duration is set to 60.00s
// 	_timeout.tv_sec = 60;
// 	_timeout.tv_usec = 0;

// 	//clears a fd_set (a struct with an array of sockets) at this address so it can store the client sockets
// 	FD_ZERO(&_clientSockets);

// //memset(_main_buffer, 0, MAX_REQUEST_LEN + 1);
// 	time(&_startTime);

// 	//address info structure : flags, protocol family, socket type, address lenght, etc
// 	struct addrinfo		hints;	
// 	//settings for the hints addrinfo structure
// 	{
// 		memset(&hints, 0, sizeof(hints));
// 		//AI_PASSIVE makes the returned socket addresses usable to bind a socket accepting a connection
// 		hints.ai_flags = AI_PASSIVE;
// 		//AF_UNSPEC makes the getaddrinfo return ipv4 or ipv6 compatible addresses
// 		hints.ai_family = AF_UNSPEC;
// 		//SOCK_STREAM sets the protocol to connection-based : it is like a conversation where both parties discuss until terminated
// 		hints.ai_socktype = SOCK_STREAM;
// 		//ai_protocol set at 0 allows any protocol type to be returned by getaddrinfo
// 		hints.ai_protocol = 0;
// 		hints.ai_addr = NULL;
// 		hints.ai_canonname = NULL;
// 		hints.ai_next = NULL;	
// 	}

	return ;
}

irc::Server::~Server()
{
	return ;
}

/*	Sockets are similar to bidirectionnal pipes : a file that represents a network connection,
*	stuff written in the socket are turned into network packets that are sent to the other host and port.
*	Client sockets are used to send a request to the server socket,
*	server sockets are used to accept requests, do an operation and send the result to the client	*/
int		irc::Server::start()
{
	/*	CREATING MAIN SOCKET	*/
	//ignoring the SIGPIPE signal that shuts the program down in case of write error : error will be handled another way here
	std::signal(SIGPIPE, SIG_IGN);

	return (0);
}





///////////////////////////////////////////////////////////////////
/*	GETTERS & SETTERS	*/

int	const &					irc::Server::getPort() const
{
	return (this->_port);
}

std::string					irc::Server::getPassword() const
{
	return (this->_password);
}

std::map<std::string, irc::Channel*>	irc::Server::getChannels()
{
	return (this->_channels);
}

std::map<std::string, irc::User*>		irc::Server::getUsers()
{
	return (this->_users);
}

int const &								irc::Server::getRotKey() const
{
	return (this->_rotKey);
}

void									irc::Server::setRotKey(int key) 
{
	this->_rotKey = key;
	return ;
}

/*	CHANNEL MANAGEMENT	*/

/*	addChannel is used to create a new channel in the server, identified in the Server::_channels map by the pair <name, pointer to new Channel>,
*	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
bool					irc::Server::addChannel(irc::Channel* chan)
{
	std::pair<std::string, Channel*>	newPair;

	newPair = std::make_pair(chan->getName(), chan);

	return ((this->_channels.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
}

/*	rmChannel is used to remove a Channel from the server (A_revoir : is it necessary ?)	*/
int						irc::Server::rmChannel(std::string name)
{
	this->_channels.erase(name);
	return (0);
}

/*	findChannel returns a pointer to the Channel whose name is sent in parameter, 
*	NULL if the Channel does not exist	*/
irc::Channel*				irc::Server::findChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it == this->_channels.end())		//the channel is not found
		return (NULL);

	return (it->second);
}

/*	USER MANAGEMENT	*/

/*	addUser is used to create a new user in the server, identified in the Server::_users map by the pair <nick, pointer to new User>,
*	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
bool						irc::Server::addUser(irc::User* user)
{
	std::pair<std::string, User*>	newPair;

	newPair = std::make_pair(user->getNick(), user);

	return ((this->_users.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
}

/*	rmUser removes a user from the list of server members	*/
int						irc::Server::rmUser(std::string nick)
{
	this->_users.erase(nick);
	return (0);
}

/*	findUser returns a pointer to the User whose nick is sent in parameter, 
*	NULL if the User does not exist	*/
irc::User*					irc::Server::findUser(std::string nick)
{
	std::map<std::string, irc::User*>::iterator	it;

	it = this->_users.find(nick);
	if (it == this->_users.end())		//the user is not found
		return (NULL);

	return (it->second);
}


/*	PASSWORD CRYPTING/UNCRYPTING	*/

std::string		irc::Server::ft_rotix(std::string pass)
{
// 	srand(time(NULL));

// 	setRotKey((rand() % 93));

	std::string	s;
	for (int i = 0; pass[i]; i++)
		s.push_back(pass[i]);

	return (s);
}