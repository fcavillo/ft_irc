#include "Message.hpp"
//#include "numeric_replies.hpp"

/*	The constructor handles the user registration and the message splitting	*/


irc::Message::Message(std::string line, Server *server, Client *sender) : _server(server), _sender(sender), _fullCommand(line)
{
	this->parse(line);
	for (int i = 0; i < (int)_cmds.size(); i++)
		_cmds[i] = toupper(_cmds[i]);
	std::cout << "PREFIX : " << this->_prefix << std::endl;
	std::cout << "CMDS : " << this->_cmds << std::endl;
	if (_params.size() != 0)
		std::cout << "PARAMS :" << this->_params[0] << std::endl;
	if(this->_cmds == "PASS")
		this->pass();
	else if(this->_cmds == "NICK")
		this->nick();
	else if(this->_cmds == "USER")
		this->user();
	
	if(sender->getRegistered() == true)
	{
		if(this->_cmds == "PING")
		{
			pong();
		}
		else if(this->_cmds == "OPER")
		{
			this->oper();
		}
		else if(this->_cmds == "JOIN")
		{
			this->join();
		}
		else if(this->_cmds == "PART")
		{
			this->part();
		}
		else if(this->_cmds == "TOPIC")
		{
			this->topic();
		}
		else if(this->_cmds == "NAMES")
		{
			this->names();
		}
		else if(this->_cmds == "LIST")
		{
			this->list();
		}
		else if(this->_cmds == "INVITE")
		{
			this->invite();
		}
		else if(this->_cmds == "KICK")
		{
			this->kick();
		}
		else if(this->_cmds == "PRIVMSG")
		{
			this->privmsg();
		}
		else if(this->_cmds == "NOTICE")
		{
			this->notice();
		}
		else if(this->_cmds == "ADMIN")
		{
			this->admin();
		}
		else if(this->_cmds == "KILL")
		{
			this->kill();
		}
		else if(this->_cmds == "DIE")
		{
			this->die();
		}
		else if(this->_cmds == "RESTART")
		{
			this->restart();
		}
		else if(this->_cmds == "QUIT")
		{
			this->quit();
		}
		else if(this->_cmds == "USERHOST")
		{
			this->userhost();
		}

	}
	else
	{
		if (sender->checkRegistered() == true)
		{
			welcome();
		}
	}
	return ;
}
/*


irc::Message::Message(std::string line, Server *server, Client *sender) : _server(server), _sender(sender), _fullCommand(line)
{
	//std::vector<std::string>	command = v_split(line);
	this->parse(line);
	std::cout << "PREFIX : " << this->_prefix << std::endl;
	std::cout << "CMDS : " << this->_cmds << std::endl;
	std::cout << "PARAMS :" << this->_params[0] << std::endl;
	if (this->_cmds == "PASS")
	{
		sender->setPass(this->_params[0]);
		std::cout << "Pass set" << std::endl;
	}
	else if (this->_cmds == "NICK")
	{
		sender->setNick(this->_params[0]);
		std::cout << "Nick set" << std::endl;
	}
	else if (this->_cmds == "USER")
	{
		sender->setUsername(this->_params[0]);
		std::cout << "Username set" << std::endl;

	}
	else if (this->_cmds == "PING")
	{
		pong();
	}
	if (sender->getRegistered() == false)
	{
		if (sender->checkRegistered() == true)
		{
			welcome();
		}
	}


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

irc::Message::Nick(std:string line, Server *server, Client *sender)
{
	std::vector<std::string> command = v_split(line);

	if(cmd[0] == 'NICK')
	{
		if(!cmd[1])
			sender->sendMsg(message_print(server->getServername(), RPL_NONICKNAMEGIVEN, RPL_NONICKNAMEGIVEN_MSG(), false));
		if(server->findnickname(cmd[1]))
			sender->sendMsg(message_print(server->getServername(), RPL_NICKNAMEINUSE, RPL_NICKNAMEINUSE_MSG(), false));
		else
			sender->setUsername(cmd[1]);
	}

}*/


void	irc::Message::parse(std::string line)
{
	int							pref = 0;
	int							j = 0;
	std::vector<std::string>	v;
	std::string					word;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ' && line[i + 1] == ' ')
				i++;
			if (word.size() > 0)
			{
				if(pref == 0 && line[i] == ':')
				{
					this->_prefix = word;
					pref++;
				}
				else if(this->_cmds == "")
					this->_cmds = word;
				else
					this->_params.push_back(word);
				pref++;
			}
			word.clear();
		}
		else if(line[i] != ' ')
		{
			word += line[i];
//			std::cout << word << std::endl;			//commenté pour y voir plus clair, déso :)
		}
	}
	if (word.size() > 0)
	{
		if(pref == 0 && line[j] == ':')
			this->_prefix = word;
		else if(this->_cmds == "")
			this->_cmds = word;
		else
			this->_params.push_back(word);
	}
	this->_params.push_back("");
//	word.clear();
//	return (v);
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
/*
irc::Client*		irc::Message::getnonconstSender()
{
	return (this->_sender);
}


irc::Server*		irc::Server::getServer()	const
{
	return (this->_server);
}
irc::Server*			getnonconstServer()
{
	return (this->_server);
}*/

