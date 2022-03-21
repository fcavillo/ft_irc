#include "Message.hpp"

irc::Message::Message(std::string fullCommand)
{
	(void)fullCommand;
	return ;
}

irc::Message::~Message()
{
	return ;
}

std::string* const &	irc::Message::getCommand() const
{
	return (this->_splitCommand);
}

irc::Client*		irc::Message::getSender() const
{
	return (this->_sender);
}

irc::Client*	irc::Message::getReceiver() const
{
	return (this->_receiver);
}

void					irc::Message::initCommands()
{
//to do : implement each command one by one in a map with the pair<command, function>
}

/*	This function takes the full command line and splits it into several arguents	*/
void					irc::Message::fillCommand(std::string fullCommand)
{
	(void)fullCommand;

}


