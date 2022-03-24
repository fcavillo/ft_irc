#include "Server.hpp"

#include <cstdio>


/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
irc::Server::Server(int port, std::string password) :
_port(port),
_password(ft_rotix(password)),
_on(true)
{
	std::cout << "Creating Server - port : " << port << std::endl;
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

		setUpFds();

		//select() monitors a set of fds, waiting for one to be ready to send/receive info
		//fd number is _max + 1, monitored set is clientFds, timeout is set at NULL so select() will wait forever
		_fdReady = select(_fdMax + 1, &_clientFds, NULL, NULL, NULL);
		if ((_fdReady < 0)/* && (errno != EINTR)*/)
			throw std::runtime_error("fd error during select()\n");
		
		connectionCheck();	//checks for new clients, sets the address and socket for the client

		activityCheck();
	}


	return (0);
}

void	irc::Server::setUpFds()
{
	//Clears a fd_set (a struct with an array of sockets) at this address so it can store the client sockets
	FD_ZERO(&_clientFds);
	//Add the main socket fd to the set
	FD_SET(_mainSocket, &_clientFds);
	_fdMax = _mainSocket;
	//Add child sockets to fd_set
	for (int i = 0; i < USER_MAX; i++)
	{
		if (_clients[i])
		{
			_socketFd = _clients[i]->getSocket();
			if (_socketFd > 0)
				FD_SET(_socketFd, &_clientFds);	//if the client has a valid socket, it is added to the set
			if (_socketFd > _fdMax)
				_fdMax = _socketFd;				//if the new fd is above the max, new max set
		}
	}
}

void		irc::Server::connectionCheck()
{
	if (FD_ISSET(_mainSocket, &_clientFds))		//tests to see if _mainSocket is part of the set of client fd
	{	//mainSocket has been created with socket(), bound to a local address with bind() and is listening with listen()
		//accept() returns the first connection request on a new fd
		if ((_newSocket = accept(_mainSocket, (struct sockaddr *)&_address, (socklen_t *)&_addressSize)) < 0)	
			throw std::runtime_error("Socket accepting error\n");
		std::cout << "New connection : socket fd [" << _newSocket << "] ip [" << inet_ntoa(_address.sin_addr) << "] port [" << ntohs(_address.sin_port) << "]" << std::endl;
		// add new socket to sockets array, sets the socket and address for the new client
		for (int i = 0; i < USER_MAX; i++)
		{
			if (!_clients[i])		//first available spot in the client array
			{
				_clients[i] = new Client(this);
				_clients[i]->setSocket(_newSocket);

				_clients[i]->setAddress(inet_ntoa(_address.sin_addr));
				std::cout << "Adding to sockets array as : " << i << std::endl;
				break;
			}
		}
	}		
}

#include <unistd.h>

int 		readLine(irc::Client & user)
{
	(void)user;
	char 			buff = 0;
	int 			read;

	std::string &	line = user.getBufferLine();
	read = recv(user.getSocket(), &buff, 1, 0);
	if (read <= 0)
		return read;

	else if (buff == '\n')
	{
		if (line.length() > 0 && line.at(line.length() - 1) == '\r')
			line.erase(line.length() - 1, 1);
		return (2);
	}
	else if (buff != 0)
		line.push_back(buff);

// std::cout << line << std::endl;
// sleep(1);

	return (1);
}

void		irc::Server::activityCheck()
{
	for (int i = 0; i < USER_MAX; i++)
	{
		if (_clients[i] && FD_ISSET(_clients[i]->getSocket(), &_clientFds))
		{
			_socketFd = _clients[i]->getSocket();
			
			int status = readLine(*_clients[i]);
			if (status == -1)
			{
				std::cout << "readline error" << std::endl;
			// 	_clients[i]->disconnect();
			// 	delete _clients[i];
			// 	_clients[i] = NULL;
			}
// 			else if (status == 0)
// 			{
// 				std::cout << "Client disconnected!" << std::endl;
// 				_clients[i]->disconnect();
// 				delete _clients[i];
// 				_clients[i] = NULL;
// 			}
			else if (status == 2)
			{
				std::string line = std::string(_clients[i]->getBufferLine());
				_clients[i]->getBufferLine().erase();

				if (line.length() > 0)
				{
					std::cout << "<- [" << _clients[i]->getSocket() << "] " << line << std::endl;
					Message message(line, this, _clients[i]);
				}

// 				if (_clients[i]->getKill())
// 				{
// 					std::cout << "Client disconnected!" << std::endl;
// 					close(_sd);
// 					delete _clients[i];
// 					_clients[i] = NULL;
// 				}
			}			
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

// if (_clients[i] && FD_ISSET(_clients[i]->getSd(), &_read_fds))
// 		{
// 			_sd = _clients[i]->getSd();

// 			int status = readLine(*_clients[i]);
// 			if (status == -1)
// 			{
// 				std::cerr << "Error inr recv(). Quiting" << std::endl;
// 				_clients[i]->disconnect();
// 				delete _clients[i];
// 				_clients[i] = NULL;
// 			}
// 			else if (status == 0)
// 			{
// 				std::cout << "Client disconnected!" << std::endl;
// 				_clients[i]->disconnect();
// 				delete _clients[i];
// 				_clients[i] = NULL;
// 			}
// 			else if (status == 2)
// 			{
// 				std::string line = std::string(_clients[i]->getBufferLine());
// 				_clients[i]->getBufferLine().erase();

// 				if (line.length() > 0)
// 				{
// 					std::cout << "<- [" << _clients[i]->getSd() << "] " << line << std::endl;
// 					Parser parser(line, this, _clients[i]);
// 				}

// 				if (_clients[i]->getKill())
// 				{
// 					std::cout << "Client disconnected!" << std::endl;
// 					close(_sd);
// 					delete _clients[i];
// 					_clients[i] = NULL;
// 				}
// 			}
// 		}


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