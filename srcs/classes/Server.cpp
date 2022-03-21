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
int		irc::Server::start() //->connect + setup
{
	//ignoring the SIGPIPE signal that shuts the program down in case of write error : error will be handled another way here
	std::signal(SIGPIPE, SIG_IGN);

	for (int i = 0; i < USER_MAX; i++)
		this->_clients[i] = NULL;

	/*	CREATING MAIN SOCKET	*/
	//AF_INET for Address Family = PF_INET (ipv4), SOCK_STREAM = two-way, connection-based byte streams
	_mainSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_mainSocket == 0)
		throw std::runtime_error("Socket creation error\n");

	//Define the kind of socket created and the address
	_address.sin_family = AF_INET;			//constant
	_address.sin_port = htons(_port);		//converts unsigned int into network byte order (!= host byte order)
	_address.sin_addr.s_addr = INADDR_ANY;	//accept any type of address

	//Bind the socket to the desired port : assigning a name and address to a created socket
	if (bind(_mainSocket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
		throw std::runtime_error("Socket binding error\n");
	if (listen(_mainSocket, 3) < 0)			//marks the _mainSocket as a passive socket (able to accept incoming connections)
		throw std::runtime_error("Socket listening after binding error\n");
	_addressSize = sizeof(_address);

	std::cout << "Socket created" << std::endl;

	while (1)
	{
		if (!this->_on)		//server shutdown
			break;

		setUpFDs();
	}


	return (0);
}

void	irc::Server::setUpFDs()
{
	//Clears a fd_set (a struct with an array of sockets) at this address so it can store the client sockets
	FD_ZERO(&_readFds);
	//Add the main socket fd to the set
	FD_SET(_mainSocket, &_readFds);
//_max = _mainSocket
	//Add child sockets to set
	for (int i = 0; i < USER_MAX; i++)
	{
		if (_clients[i])
		{
			_socketFd = _clients[i]->getSocketFd();
			// if valid socket you can add it to the read list
			if (_socketFd > 0)
				FD_SET(_socketFd, &_readFds);
			if (_socketFd > _mainSocket)
				_mainSocket = _socketFd;
		}
	}
}



///////////////////////////////////////////////////////////////////
/*	GETTERS & SETTERS	*/

// int	const &					irc::Server::getPort() const
// {
// 	return (this->_port);
// }

// std::string					irc::Server::getPassword() const
// {
// 	return (this->_password);
// }

// std::map<std::string, irc::Channel*>	irc::Server::getChannels()
// {
// 	return (this->_channels);
// }

// std::map<std::string, irc::User*>		irc::Server::getUsers()
// {
// 	return (this->_clients);
// }

// int const &								irc::Server::getRotKey() const
// {
// 	return (this->_rotKey);
// }

// void									irc::Server::setRotKey(int key) 
// {
// 	this->_rotKey = key;
// 	return ;
// }

// /*	CHANNEL MANAGEMENT	*/

// /*	addChannel is used to create a new channel in the server, identified in the Server::_channels map by the pair <name, pointer to new Channel>,
// *	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
// bool					irc::Server::addChannel(irc::Channel* chan)
// {
// 	std::pair<std::string, Channel*>	newPair;

// 	newPair = std::make_pair(chan->getName(), chan);

// 	return ((this->_channels.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
// }

// /*	rmChannel is used to remove a Channel from the server (A_revoir : is it necessary ?)	*/
// int						irc::Server::rmChannel(std::string name)
// {
// 	this->_channels.erase(name);
// 	return (0);
// }

// /*	findChannel returns a pointer to the Channel whose name is sent in parameter, 
// *	NULL if the Channel does not exist	*/
// irc::Channel*				irc::Server::findChannel(std::string name)
// {
// 	std::map<std::string, Channel*>::iterator	it;

// 	it = this->_channels.find(name);
// 	if (it == this->_channels.end())		//the channel is not found
// 		return (NULL);

// 	return (it->second);
// }

// /*	USER MANAGEMENT	*/

// /*	addUser is used to create a new user in the server, identified in the Server::_clients map by the pair <nick, pointer to new User>,
// *	returns a bool (1 if succesful, 0 if key already exists or 0 if insertion failed)	*/
// bool						irc::Server::addUser(irc::User* user)
// {
// 	std::pair<std::string, User*>	newPair;

// 	newPair = std::make_pair(user->getNick(), user);

// 	return ((this->_clients.insert(newPair)).second);		//insert returns a pair with first=iterator to new elem, second=bool for success
// }

// /*	rmUser removes a user from the list of server members	*/
// int						irc::Server::rmUser(std::string nick)
// {
// 	this->_clients.erase(nick);
// 	return (0);
// }

// /*	findUser returns a pointer to the User whose nick is sent in parameter, 
// *	NULL if the User does not exist	*/
// irc::User*					irc::Server::findUser(std::string nick)
// {
// 	std::map<std::string, irc::User*>::iterator	it;

// 	it = this->_clients.find(nick);
// 	if (it == this->_clients.end())		//the user is not found
// 		return (NULL);

// 	return (it->second);
// }


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