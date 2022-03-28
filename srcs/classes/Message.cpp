#include "Message.hpp"
#include "numeric_replies.hpp"

/*	The constructor handles the user registration and the message splitting	*/
irc::Message::Message(std::string line, Server *server, Client *sender) : _server(server), _sender(sender), _fullCommand(line)
{
	std::vector<std::string>	command = v_split(line);

	if (command[0] == "PASS")
	{
		sender->setPass(command[1]);
		std::cout << "Pass set" << std::endl;
	}
	else if (command[0] == "NICK")
	{
		sender->setNick(command[1]);
		std::cout << "Nick set" << std::endl;
	}
	else if (command[0] == "USER")
	{
		sender->setUsername(command[1]);
		std::cout << "Username set" << std::endl;
		sender->sendMsg(message_print("fcavillo@localhost", RPL_WELCOME, sender->getNick(), RPL_WELCOME_MSG(sender->getNick(), sender->getUsername(),"fcavillo@localhost"), false));
	}
	return ;
}

std::vector<std::string>	irc::Message::v_split(std::string line)
{
	std::vector<std::string>	v;
	std::string					word;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (word.size() > 0)
				v.push_back(word);
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

irc::Client*		irc::Message::getSender() const
{
	return (this->_sender);
}



void					irc::Message::initCommands()
{
//to do : implement each command one by one in a vector of function pointers
}


