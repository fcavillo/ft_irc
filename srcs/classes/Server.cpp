#include "Server.hpp"

#include <cstdio>


/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
irc::Server::Server(int port, std::string password) :
_servername("IRC"),
_port(port),
_password(password),
_on(true)
{
	std::cout << "Creating Server - port : " << port << std::endl;

	//set start time
	_startTime = time(0);
	_startTimeString = ctime(&_startTime);

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

		activityCheck();	//iterates through sockets to catch incoming requests and answers them
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
	for (size_t i = 0; i < _clients.size(); i++)
	{
		_socketFd = _clients[i]->getSocket();
		if (_socketFd > 0)
			FD_SET(_socketFd, &_clientFds);	//if the client has a valid socket, it is added to the set
		if (_socketFd > _fdMax)
			_fdMax = _socketFd;				//if the new fd is above the max, new max set
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
		int	i = _clients.size();
		_clients.push_back(new Client(this));
		_clients[i]->setSocket(_newSocket);
		_clients[i]->setAddress(inet_ntoa(_address.sin_addr));
		std::cout << "Adding to sockets array as : " << i << std::endl;
	}		
}

#include <unistd.h>

int 		readLine(irc::Client & user)
{
	(void)user;
	char 			buff = 0;
	int 			read;

	std::string &	line = user.getBufferLine();
	read = recv(user.getSocket(), &buff, 1, 0);			//receive messages from a socket
	if (read <= 0)
		return read;

	else if (buff == '\n')
	{
		if (line.length() > 0 && line.at(line.length() - 1) == '\r')	//end of line
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
	for (size_t i = 0; i < _clients.size(); i++)
	{	//if a client exists
		if (FD_ISSET(_clients[i]->getSocket(), &_clientFds))
		{
			_socketFd = _clients[i]->getSocket();		//temp socket storage
			int status = readLine(*_clients[i]);		//get the line from the socket
			if (status == -1)
			{
				std::cout << "readline error" << std::endl;
//disconnect the client[i] + erase it
			}
			else if (status == 0)			//nothing to read, user force disconnected
			{
//disconnect the client[i] + erase
			}
			else if (status == 2)
			{
				std::string line = std::string(_clients[i]->getBufferLine());	//put message in line
				_clients[i]->getBufferLine().erase();

				if (line.length() > 0)
				{
					std::cout << "<- Socket[" << _clients[i]->getSocket() << "] : " << line << std::endl;
					Message message(line, this, _clients[i]);	//create new message from line
				}
				if (_clients[i]->getLogged() == false)			//if the client just quit
				{
					std::cout << "Client disconnected !" << std::endl;
//make sure the client is erased + set _logged as false when quitting				
				}
			}			
		}
	}
}

// 			else if (status == 2)
// 			{
// 				std::string line = std::string(_clients[i]->getBufferLine());


// 				if (_clients[i]->getKill())
// 				{
// 					std::cout << "Client disconnected!" << std::endl;
// 					close(_sd);
// 					delete _clients[i];
// 					_clients[i] = NULL;
// 				}
// 			}


/*	GETTERS & SETTERS	*/

int	const &					irc::Server::getPort() const
{
	return (this->_port);
}

std::string					irc::Server::getPassword() const
{
	return (this->_password);
}

std::string					irc::Server::getServername() const
{
	return (this->_servername);
}

time_t						irc::Server::getStartTime() 
{
	return (this->_startTime);
}

std::string					irc::Server::getStartTimeString() 
{
	return (this->_startTimeString);
}

std::vector<irc::Channel*>	irc::Server::getChannels()
{
	return (this->_channels);
}

std::vector<irc::Client*>	irc::Server::getClients()
{
	return (this->_clients);
}

/*	CHANNEL MANAGEMENT	*/

void					irc::Server::addChannel(irc::Channel* chan)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end() ; it++)	//checks if user already is member
		if (*(it) == chan)
			return ;
	this->_channels.push_back(chan);	
}

void					irc::Server::rmChannel(irc::Channel* chan)
{
	std::vector<Channel*>::iterator	it;

	for (it = _channels.begin(); it != _channels.end() || *(it) != chan ; it++);	
	if (it == this->_channels.end())		//the channel is not found
		return ;
	this->_channels.erase(it);
}

irc::Channel*				irc::Server::findChannel(irc::Channel* chan)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i] == chan)
			return (_channels[i]);
	}
	return (NULL);
}

/*	CLIENT MANAGEMENT	*/

void					irc::Server::addClient(irc::Client* client)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end() ; it++)	//checks if user already is member
		if (*(it) == client)
			return ;
	this->_clients.push_back(client);	
}

void					irc::Server::rmClient(irc::Client* client)
{
	std::vector<Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end() || *(it) != client ; it++);	
	if (it == this->_clients.end())		//the client is not found
		return ;
	this->_clients.erase(it);
}

irc::Client*				irc::Server::findClient(irc::Client* client)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i] == client)
			return (_clients[i]);
	}
	return (NULL);
}


irc::Client*		irc::Server::findNick(std::string nick)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getNick() == nick)
			return (_clients[i]);
	}
	return (NULL);
}


bool				irc::Server::findClient_user(std::string user)
{
	std::vector<Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end() || (*(it))->getUsername() != user ; it++);
	if (it == this->_clients.end())		//the client is not found
		return (false);
	return (true);
}


bool				irc::Server::findClient_nick(std::string nick)
{
	std::vector<Client*>::iterator	it;

	for (it = _clients.begin(); it != _clients.end() || (*(it))->getNick() != nick ; it++);
	if (it == this->_clients.end())		//the client is not found
		return (false);
	return (true);
}


