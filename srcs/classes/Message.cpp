#include "Message.hpp"

irc::Message::Message(std::string line, Server *server, Client *sender) : _server(server), _sender(sender), _fullCommand(line)
{
std::cout << "New message received : " << line << std::endl;

	std::vector<std::string>	command = v_split(line);

	if (strncmp(line, "PASS", 4))
	{

	}
	else if (strncmp(line, "NICK", 4))
	{

	}
	else if (strncmp(line, "USER", 4))
	{

	}
	return ;
}

std::vector<std::string>	v_split(str::string line)
{
	std::vector<std::string>	v;
	std::string					word;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] == ' ')
		{
			while (line[i] = ' ')
				i++;
			if (word.size() > 0)
				v.push_back(word_buf);
			word.clear();
		}
		else
			word += line[i];
	}
	if (word.size() > 0)
 		v.push_back(word);

	return (v);
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

// std::vector<std::string> Parser::split(std::string &line)
// {
// 	std::vector<std::string> tab;
// 	std::string word_buf;
// 	bool space = false;

// 	for (int i = 0; i < (int)line.size(); i++)
// 	{
// 		if (line[i] == ' ' && space == false)
// 		{
// 			space = true;
// 			if (word_buf.size() > 0)
// 				tab.push_back(word_buf);
// 			word_buf.clear();
// 		}
// 		else
// 		{
// 			word_buf += line[i];
// 			if (line[i] != ' ')
// 				space = false;
// 		}
// 	}
// 	if (word_buf.size() > 0)
// 		tab.push_back(word_buf);
// 	return tab;
// }

