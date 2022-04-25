#include "Server.hpp"

#include "cstdio"

bool	forceStop = false;
void	sig(int) {forceStop = true;}

/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
irc::Server::Server(int port, std::string password) :
_servername("localhost"),
_port(port),
_password(password),
_on(true),
_IRCname("IRC_42")
{
	std::cout << "Creating Server - port : " << port << std::endl;

	//set start time
	_startTime = time(0);
	_startTimeString = ctime(&_startTime);
	std::string::iterator it = _startTimeString.end();	//removing \n
	--it;
	_startTimeString.erase(it);

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
	//setting ^C amd ^\ as a clean stop
	std::signal(SIGINT, sig);
	std::signal(SIGQUIT, sig);

	/*	CREATING MAIN SOCKET	*/
	//AF_INET for Address Family = PF_INET (ipv4), SOCK_STREAM = two-way, connection-based byte streams
	_mainSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_mainSocket == 0)
		throw std::runtime_error("Socket creation error\n");
	//Allows the address to be reused as soon as it gets quit	
	int enable = 1;	
	if (setsockopt(_mainSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
	//makes the fd non blocking
	if (fcntl(_mainSocket, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("fcntl failed");
	
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

	std::cout << "Main socket created" << std::endl;

	while (_on && forceStop == false && _restart == false)
	{
		setUpFds();
std::cout << "1" << std::endl;
		//select() monitors a set of fds, waiting for one to be ready to send/receive info
		//fd number is _max + 1, monitored set is clientFds, timeout is set at NULL so select() will wait forever
		_fdReady = select(_fdMax + 1, &_clientFds, NULL, NULL, NULL);
std::cout << "2" << std::endl;
	
		if ((_fdReady < 0))
			throw std::runtime_error("fd error during select()\n");

		connectionCheck();	//checks for new clients, sets the address and socket for the client
std::cout << "3" << std::endl;

		activityCheck();	//iterates through sockets to catch incoming requests and answers them	
std::cout << "4" << std::endl;
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
		// // add new socket to sockets array, sets the socket and address for the new client
		int enable = 1;	
		if (setsockopt(_newSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
			throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
		//makes the fd non blocking
		if (fcntl(_newSocket, F_SETFL, O_NONBLOCK) < 0)
			throw std::runtime_error("fcntl failed");		
		int	i = _clients.size();
		_clients.push_back(new Client(this));
		_clients[i]->setSocket(_newSocket);
		_clients[i]->setAddress(inet_ntoa(_address.sin_addr));
		std::cout << "Adding to sockets array as : " << i << std::endl;
	}		
}

int 		readLine(irc::Client & user)
{
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

	return (1);
}

void		irc::Server::activityCheck()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{	
		if (FD_ISSET(_clients[i]->getSocket(), &_clientFds))
		{	//if the socket is part of the set
			_socketFd = _clients[i]->getSocket();		//temp socket storage
			int status = readLine(*_clients[i]);		//get the line from the socket
			if (status == -1)
			{
				std::cout << "readline error" << std::endl;
				_clients[i]->leaveAllChannels();
				_clients[i]->leaveServer();
				close(_clients[i]->getSocket());
			}
			else if (status == 0)			//nothing to read, user force disconnected
			{
				std::cout << "A client on socket[" << _clients[i]->getSocket() << "] force disconnected !" << std::endl;
				_clients[i]->leaveAllChannels();
				_clients[i]->leaveServer();
				close(_clients[i]->getSocket());				
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
					std::cout << "A client on socket [" << _clients[i]->getSocket() << "] disconnected !" << std::endl;
					_clients[i]->leaveAllChannels();
					_clients[i]->leaveServer();
					close(_clients[i]->getSocket());
				}
			}			
		}
	}
}


void	irc::Server::clear()
{
	close(_mainSocket);

	std::vector<Client*>::iterator	it = _clients.begin();
	for (; it != _clients.end() ; it++)
		delete *it;
	std::vector<Channel*>::iterator	it2 = _channels.begin();
	for (; it2 != _channels.end() ; it2++)
		delete *it2;
std::cout << "memory wiped" << std::endl;	
}

void		irc::Server::switchOff()
{
	this->_on = false;
}


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

bool	irc::Server::getRestart()
{
	return (this->_restart);
}

void	irc::Server::setRestart(bool b)
{
	this->_restart = b;;
}

std::string					irc::Server::getIRCname() 
{
	return (this->_IRCname);
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

	for (it = _channels.begin(); it != _channels.end() && *(it) != chan ; it++);	
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

irc::Channel*		irc::Server::findChannelFromName(std::string name)
{
	std::vector<Channel*>::iterator	it;

	for (it = _channels.begin(); it != _channels.end() ; it++)
	{
		if(name == (*it)->getName())
			return((*it));
	}
	return(NULL);

}

/*
irc::Channel*		irc::Server::findChannelFromName(std::string chan)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		std::string s = _channels[i]->getName();
		if (s == chan)
		{
			s.clear();
			return (this->_channels[i]);
		}
		if(chan != "\0" && (chan[0] == '#' || chan[0] == '&' || chan[0] == '!' || chan[0] == '+'))
		{
			size_t	j;
			size_t	e = 1;
			if(s[0] == '#' || s[0] == '&' || s[0] == '!' || s[0] == '+')
				e = 0;
			for(j = 1; chan[j] && s[j - e]; j++)
			{
				if(chan[j] != s[j - e])
				{
					s.clear();
					return(NULL);
				}
			}
			if(chan[j] == '\0' && s[j - e] == '\0')
			{
				s.clear();
				return(_channels[i]);
			}
		}
		s.clear();
	}
	return (NULL);
}*/

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

	for (it = _clients.begin(); it != _clients.end() && *(it) != client ; it++);
	if (it == this->_clients.end())		//the client is not found
	{
		return ;
	}
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
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getUsername() == user)
			return (true);
	}
	return (false);	
	
}


bool				irc::Server::findClient_nick(std::string nick)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getNick() == nick)
			return (true);
	}
	return (false);
}

int					irc::Server::numberChannelsJoin(Client* a)
{
	int		i = 0;
	std::vector<Client*>::iterator	it;

	i = 0;
	for(it = _clients.begin() ; it != _clients.end() ; it++)
	{
		if(a == *(it))
			i++;
	}
	return(i);
}

irc::Client*				irc::Server::findClientUser(std::string user)
{
	int		i = 0;
	std::vector<Client*>::iterator	it;

	i = 0;
	for(it = _clients.begin() ; it != _clients.end() ; it++)
	{
		if(user == (*(it))->getUsername())
			return(*it);
	}
	return(NULL);
}

std::vector<irc::Client*>		irc::Server::findClientUserExtension(std::string extension)
{
	std::vector<Client*>	c;

	std::vector<Client*>	v = getClients();

	for(std::vector<irc::Client*>::iterator it = v.begin() ; it != v.end() ; it++)
	{
		std::string		user = (*(it))->getUsername();
		size_t			u;
		for(u = 0; (user.size() - u) >= 0 && (extension.size() - u) >= 0; u++)
		{
			if((extension.size() - u) == 0 && extension[(extension.size() - u)] == user[(user.size() - u)] && ((user.size() - u - 1) >= 0 && user[(user.size() - u - 1)] == '.'))
				c.push_back((*it));
			else if(user[user.size() - u ] != extension[extension.size() - u])
				break ;
		}
		user.clear();
	}
	return(c);
}


std::vector<irc::Channel*>		irc::Server::findChannelNameExtension(std::string extension)
{
	std::vector<Channel*>	c;

	printf("\n Channel NAMEEE \n");
	for(std::vector<Channel*>::iterator it = _channels.begin() ; it != _channels.end() ; it++)
	{
		std::string		user = (*(it))->getName();
		size_t			i = 0;
		for(size_t u = extension.size() ; (user.size() - u) >= 0 && u >= 0; u--)
		{
			if(extension[u] != user[user.size() - i])
				break;
			if(u == 0)
			{
				printf("\n PUSHclient %s \n", ((*it)->getName()).c_str());
				c.push_back((*it));
			}
			i++;
		}
		user.clear();
	}
	printf("\n return Client \n");
	return(c);
}

void							irc::Server::leaveAllChannels(irc::Client* client)
{
	for(std::vector<Channel*>::iterator	it = this->_channels.begin(); it != this->_channels.end() ; it++)
	{
		if((*it)->isClient(client))
			(*it)->rmClient(client);
	}
}

