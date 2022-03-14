#include "server.hpp"

/*	Server class is initialized with a specific port and password (set at launch with the executable)	*/
Server::Server(int port, std::string password) : _port(port), _password(password)
{
std::cout << "Creating Server" << std::endl;
//initialize _channels map?
	return ;
}

Server::~Server()
{
	return ;
}

int	const &						Server::getPort() const
{
	return (this->_port);
}

std::string const &				Server::getPassword() const;
{
	return (this->_password);
}

std::map<std::string, *Channel>	Server::getChannels()
{
	return (this->_channels);
}

/*	addChannel is used to create a new channel in the server, identified in the Server::_channels map by the pair <name, pointer to new Channel>	*/
int					Server::addChannel(Channel* chan)
{
	return (0);
}

int					Server::rmChannel(std::string name)
{
	return (0);
}

Channel*			Server::findChannel(std::string name)
{
	return ()
}