#include "Message.hpp"

Message::Message(std::string fullCommand)
{
	return ;
}

Message::~Message()
{
	return ;
}

std::string* const &	Message::getCommand() const
{
	return (this->_splitCommand);
}

std::string const &		Message::getSender() const
{
	return (this->_sender);
}

std::string const &		Message::getReceiver() const
{
	return (this->_receiver);
}

void					Message::initCommands()
{

}

void					Message::fillCommand(std::string fullCommand)
{

}


