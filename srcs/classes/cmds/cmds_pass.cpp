/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/04/06 21:13:50 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
#include "../numeric_replies.hpp"

#include "utils.hpp"
//#include "cstring"

/*
std::string message_print(
std::string nameserver, 
std::string code, 
std::string nick, 
std::string msg, 
bool op)
*/

/*
std::string		message_print1(std::string nameserver, std::string code, std::string nick, std::string msg, bool op)
{
    if(op == true)
        return("*:" + nameserver + " " + code + " " + nick + " " + msg);
    else
        return(":" + nameserver + " " + code + " " + nick + " " + msg);
}
*/
/*
bool		irc::isSpecial(char c){ return (c >= '[' && c <= '\'') || (c >= '{' && c <= '}');}
bool		irc::isLetter(char c){ return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');}
bool		irc::isChiffre(char c){ return (c >= '0' && c <= '9');}
*/

void	irc::Message::Message_cmds(std::string cmds, std::string facultatif, Client *a)
{
	if(facultatif == "")
		a->sendMsg(this->_sender->getNick() + "!" + this->_sender->getUsername() + "@" + this->_sender->getRealName() + " " + cmds + " " + facultatif);
	else
		a->sendMsg(this->_sender->getNick() + "!" + this->_sender->getUsername() + "@" + this->_sender->getRealName() + " " + cmds);
}




void	irc::Message::Message_c(std::string code, std::string code_msg, Client *a)
{
	a->sendMsg(message_print(this->_server->getServername(), code , this->_sender->getNick(), code_msg , this->_sender->getOper()));
}

void	irc::Message::Message_p(std::string code, std::string code_msg)
{
	this->_sender->sendMsg(message_print(this->_server->getServername(), code , this->_sender->getNick(), code_msg , this->_sender->getOper()));
}

void	irc::Message::pass()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_sender->getPass() != "")
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
		this->_sender->setPass(this->_params[0]);
}


/*
bool	irc::nick_check_char(std::string params)
{
	for(size_t index = 1; index < params.lenght(); ++index)
		if(!isLetter(params[index]) && !isSpecial(params[index]) && !isChiffre(params[index]))
			return(false);
	return(true);
}*/

//void	irc::irc::Client*		irc::Server::findNick(std::string nick)

void	irc::Message::nick()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG());
	else if(this->_server->findNick(this->_params[0])) // Si c est deja le meme nickname
		this->Message_p(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG(this->_params[0]));
	else if(this->_params[0].length() > 9 || (!isLetter(this->_params[0][0]) && !isSpecial(this->_params[0][0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	else if(!(nick_check_char(this->_params[0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	else
		this->_sender->setNick(this->_params[0]);
	// RETOURNER PAR UN SERVER SI LA CONNECTION EST DITE RESTRICTED user mode "+r"
//	this->Message_p(ERR_RESTRICTED, ERR_RESTRICTED_MSG());
}

void	irc::Message::user()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_server->findClient_user(this->_params[0]))
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
	{
		this->_sender->setUsername(this->_params[0]);
		// voir pour mettre les mode et real name
	}
}

void	irc::Message::oper()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_params[1] != this->_server->getPassword())
		this->Message_p(ERR_PASSWDMISMATCH, ERR_PASSWDMISMATCH_MSG());
	else
	{
		if(this->_sender->getUsername() == "labintei" || this->_sender->getUsername() == "fcavillo")
		{
			this->_sender->setOper(true);
			this->Message_p(RPL_YOUREOPER, RPL_YOUREOPER_MSG());
		}
		else
			this->Message_p(ERR_NOOPERHOST, ERR_NOOPERHOST_MSG());
	}
}
/*
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
	word.clear();
	return (v);
}*/

/*std::vector<std::string>		splitChar(std::string line, char c)
{
	std::string		word;
	std::vector<std::string>	v;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if(line[i] == c)
		{
			if(word.size())
			{
				v.pushback(word);
				word.clear();
			}
		}
		else
			word += line[i];
	}
	if(word.size())
		v.push_back(word);
	return(v);
}
*/

// Les channel se trouve au niveau du Server
 void	irc::Message::join()
 {
 	std::vector<std::string>	names;
 	std::vector<std::string>	key;

 	if(this->_params[0] == "")
 		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
 	names = splitChar(this->_params[0], ',');
 	if(this->_params[1] != "")
 		key = splitChar(this->_params[1], ',');
 	Channel*	a;
	a = this->_server->findChannelFromName(_params[0]);
 	for(size_t v = 0; names[v] != ""; v++)
 	{
 		Channel*	a = this->_server->findChannelFromName(_params[0]);
 		if( a != NULL)
 		{
 			if(a->getPass() != "" && a->getPass() != key[v])
 				this->Message_p(ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_MSG(names[v]));
 			else if(a->isBan(this->_sender))
 				this->Message_p(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MSG(names[v]));
 			else if(this->_server->numberChannelsJoin(this->_sender) > 20) // 20 est le nombre max de channels valable
 				this->Message_p(ERR_TOOMANYCHANNELS, ERR_TOOMANYCHANNELS_MSG(names[v]));
			else if(names[v][0] == '!' && (a->getName())[0] != '!')
				this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG(names[v], "abbort messages"));
			else
			{
				
				for(std::vector<Client*>::iterator it  = (a->getClients()).begin(); it !- (a->getClients()).end() ; it++)
				{
					Message_cmds("JOIN " , a->getName() , (*it));
				}
				a->addClient(this->_sender);
			}
			a = NULL;
 		}
 		else
 		{
 			if(validChannelName(names[v]))
 			{
 				Channel		h(names[v]);
				for(size_t c = 0; key[c] != "" ; c++)
				{
					if(c == v)
						h.setPass(key[c]);
				}
 				this->_server->getChannels().push_back(&h);
 			}
 			else
 				this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(names[v]));
 		}
 	}

	// Des qu un user join un channel touts les autres user sont imforme
	// nick!user@client_name


	// Quand un client cherche a rejindre un channel qui a ! et qui a plusieurs short name equivalents
	// this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG());
}

void	irc::Message::part()
{
	/*this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(this->_cmds));
	this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG());
	this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG());
	*/

	// part LEAVING A CHANNEL
}

void	irc::Message::topic()
{/*
	this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	this->Message_p(ERR_NOTOPIC, ERR_NOTOPIC_MSG());
	this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG());
	this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG());
	this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG());*/
}

void	irc::Message::names()
{
//	this->Message_p(ERR_TOOMANYMATCHES, )
}


char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

void	irc::Message::list()
{
	if (this->_params[0] != "\0" && this->_params[0] != _server->getServername())
		this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_params[0]));
	for (int i = 0; i < (int)this->_server->getChannels().size(); i++)
	{
		Channel*	tmp = this->_server->getChannels()[i];
		this->Message_p(RPL_LIST, RPL_LIST_MSG(tmp->getName(), itoa(tmp->getClients().size(), 10), tmp->getTopic()));
	}
	this->Message_p(RPL_LISTEND, RPL_LISTEND_MSG());
}

void	irc::Message::invite()
{

}

void	irc::Message::kick()
{

}

	std::string		cutChar(std::string s, char c, int i)



void	irc::Message::privmsg()
{
	// PREND EN PARAMETRE SOIT
	//
	// UN user 
	// UN channel
	//
	//
	//
	std::string		hist;
	std::string		user;
	std::string		extension;
	
	std::string		msg;
	// WILDCARD '*' && '?' // NE CONNAIT PAS L UTILITEE DE ?

	if(this->_params[0] == "")
		return(Message_p(ERR_NORECIPIENT, ERR_NORECIPIENT_MSG(this->_cmds)));
	if(this->_params[1] == "")
		return(Message_p(ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG()));
	msg = 	convertVectortoString(this->_params, 1);
	if(ft_find('@', this->_params[0]))
	{
		host = cutChar(this->_params[0], '@' , 1);
		user = cutChar(this->_params[0], '@' , 0);
		if(ft_finds("?#", user) || ft_finds("?#", host))
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG());
	}
	if(ft_find('%', this->_params[0]))
	{
		host = cutChar(this->_params[0], '%' , 1);
		user = cutChar(this->_params[0], '%' , 0);
		if(ft_finds("?#", user) || ft_finds("?#", host))
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG());
	}
	if(ft_find('*', this->_params[0]))
	{
		extension = extensionValidPrivmsg(this->params[0]);
		if(extension == "")
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG()));
	}
	// si mode incorrect (pas gerer) ou le user est ban du channel ou ne se trouve pas dans le channel
	// sera un envoit user
	if(this->params[0] && this->params[0][0] != '#')
	{
		Client*					a;
		std::vector<Client*>	ext;

		if(extension != "")
			ext = this->_server->findClientUserExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			a = findClientUser(user);
		else if(user == "")
			a = findClientUser(this->_params[0]);
		if(a == NULL || extension)
		{
			if(extension)
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(ext));
			else if(user != "")
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(user));
			else
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0]));
		}
		else
		{
			if(extension == "")
				this->Message_c("PRIVMSG", msg, a);
			else if(extension && ext)
			{
				for(std::vector<Client*>::iterator it = ext.begin(); it != it.end(); ++it)
				{
					this->Message_c("PRIVMSG", msg , (*it));
				}
			}
		}
	}
	else
	{
		Channel*				b;
		std::vector<Channel*>	ext;

		if(extension != "")
			ext = this->_server->findChannelNameExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			b = findChannelFromName(user);
		else if(user == "")
			b = findChannelFromName(this->params[0]);
		if(b == NULL && ext == NULL)
		{
			return(this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN(this->_params[0])));
		}
		else
		{
			if(ext && extension)
			{
				for(std::vector<Channel*>::iterator it = ext.begin(); it != ext.end() ; it++)
				{
					if((*it)->isClient(this->_sender))
					{
						for(std::vector<Client*>::iterator ut = ((*it)->getClients()).begin(); ut != ((*it)->getClients()).end() ; ut++)
						{
							this->Message_c("PRIVMSG", msg, (*ut));
						}
					}
					else
						this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG());
				}
			}
			else
			{
				if(b->isClient(this->_sender))
					this->Message_c("PRIVMSG", msg, (b));
				else
					this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG());
			}
		}

	}

	//Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG());
	//Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0]));
	// quand invalid utilite de Privmsg <server> <host>
	//Message_p(ERR_NOTOPLEVEL, ERR_NOTOPLEVEL_MSG());
	// Envouers si user@host(sender) a plusieurs occurences ???
	//Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG());
	// Replies valides ?? REPLIES QUAND LE SERVER EST AILLEURS ???
	//Message_p(RPL_AWAY, RPL_AWAY_MSG());

}

void	irc::Message::notice()
{
// notice similaire a PRIVMSG sauf que un automatic replies ne doit jamais etre
// en reponce a un NOTICE MESSAGE
}

void	irc::Message::admin()
{/*
	this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG());
	this->Message_p(ERR_ADMINME, ERR_ADMINME_MSG());
	this->Message_p(ERR_ADMINLOC1, ERR_ADMINLOC1_MSG());
	this->Message_p(ERR_ADMINLOC2, ERR_ADMINLOC2_MSG());
	this->Message_p(ERR_ADMINEMAIL, ERR_ADMINEMAIL_MSG());*/
}

//(nick name collision)
void	irc::Message::kill()
{

}

//(DIE oper)
void	irc::Message::die()
{

}

void	irc::Message::restart()
{

}


/*
void	irc::Message::pass()
{
	if(this->_params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NEEDMOREPARAMS, this->sender->getNick(), ERR_NEEDMOREPARAMS_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else if(this->_sender->_pass != "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_ALREADYREGISTERED, this->sender->getNick(), ERR_ALREADYREGISTERED_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else
		sender->setPass(this->_params[0]);
}

void	irc::Message::nick()
{
	if(this->_params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NONICKNAMEGIVEN, this->sender->getNick(), ERR_NONICKNAMEGIVEN_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else if(this->_server->findClient_nick(this->_params[0]))
		sender->sendMsg(message_print(this->_server->_servername, ERR_NICKNAMEINUSE, this->sender->getNick(), ERR_NICKNAMEINUSE_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else
		this->_sender->setNick(this->_params[0]);
	// ERRONEUSNICKNAME
	// UNAVAILLABLERESOURCE
	// ERRNICKCOLLISION
	// ERRRESTRICTED
}

void	irc::Message::user()
{
	if(this->params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NEEDMOREPARAMS, this->sender->getNick(), ERR_NEEDMOREPARAMS_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else if(this->_server->findClient_user(this->_params[0]))
		sender->sendMsg(message_print(this->_server->_servername, ERR_ALREADYREGISTERED, this->sender->getNick(), ERR_ALREADYREGISTERED_MSG() , this->_sender->getUsername(), this->_sender->_oper));
	else
	{
		this->_sender->setUsername(params[0]);
		// voir pour mettre les mode et real name
	}
}


// On va partir du principe que tout le monde peut devenir oper
void	irc::Message::oper()
{

}
*/

/////////////////////partie de Flo//////////////////////

void	irc::Message::pong()
{
	if (_params.size() == 0)
		Message_p(ERR_NOORIGIN, ERR_NOORIGIN_MSG());
	else if (_params.size() > 1)
		Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_server->getServername()));
	else
		_sender->sendMsg("PONG : " + _params[0]);
	// std::cout << "user is a member of : " << std::endl;
	// for (int i = 0; i < (int)_sender->getMembership().size(); i++)
	// 	std::cout << _sender->getMembership()[i]->getName() << std::endl;
	
}

/*	A client session is terminated with a quit message.  */
void	irc::Message::quit()
{
	_sender->leaveAllChannels();
	_sender->leaveServer();
	close(_sender->getSocket());
	_sender->setLogged(false);
}

void	irc::Message::welcome()
{
	Message_p(RPL_WELCOME, RPL_WELCOME_MSG(_sender->getNick(), _sender->getUsername(), _server->getServername()));
	Message_p(RPL_YOURHOST, RPL_YOURHOST_MSG(_server->getServername(), "1.0"));
	Message_p(RPL_CREATED, RPL_CREATED_MSG(_server->getStartTimeString()));
	Message_p(RPL_MYINFO, RPL_MYINFO_MSG(_server->getServername(), "1.0", "aiwroOS", "c_modes"));
}
