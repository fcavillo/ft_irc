/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/04/27 17:26:25 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
#include "../numeric_replies.hpp"

#include "utils.hpp"
#include <iostream>

#include <cstdio>

//		this->_msg = this->getMsg(line); // JE l ai fait de facon simplifier


std::string			prefix(irc::Client *a)
{
//	return(":" + a->getNick() + "!" + a->getUsername() + "@" + "localhost");
	return(":" + a->getNick() + "!" + "localhost" + "@" + "localhost");
}

void	irc::Message::Messagejoin(/*std::string cmds,*/ /*std::string msg, */irc::Channel* chan)
{
	std::string s;
	std::vector<Client*>	o = chan->getClients();

	for(std::vector<Client*>::iterator n = o.begin() ; n != o.end(); n++)
	{
		if((*n) != NULL && (*n) != this->_sender)
			(*n)->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
	}
	for(std::vector<Client*>::iterator n = o.begin() ; n != o.end(); n++)
	{
		if((*n) != NULL && chan->isOper(this->_sender) == true)
			s += "@";
		if((*n) != NULL)
			s += (*n)->getNick();
		if((n + 1) != o.end())
			s += " ";
	}
	this->_sender->sendMsg(prefix(this->_sender) + " 353" + " " + this->_sender->getNick() + " = " + chan->getName() + " :" + s);
	this->_sender->sendMsg(prefix(this->_sender) + " " + "366" + " " + this->_sender->getNick() + " " + chan->getName() + " :End of /NAMES list");
	this->_sender->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
}

void	irc::Message::Message_p(std::string code, std::string code_msg)
{
	this->_sender->sendMsg(message_print("localhost", code , this->_sender->getNick(), code_msg , this->_sender->getOper()));
}

void	irc::Message::pass()
{
	if(this->_params.size() - 1 == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_sender->getPass() != "" && this->_sender->getRegistered())
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
		this->_sender->setPass(this->_params[0]);
}

bool	irc::valid_flags(std::string flags, std::string validflag)
{
	if(flags == "" || (flags[0] != '+' && flags[0] != '-'))
		return(false);

	for(size_t n = 1; flags[n] != '\0' ; n++)
	{
		if(ftFind(flags[n], validflag) == false)
			return(false);
	}
	return(true);
}


void	irc::Message::mode()
{
	if(this->_params[0] == "")
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	if(this->_params[0] != "" && this->_params[0][0] == '#')
	{
		Channel			*a = this->_server->findChannelFromName(_params[0]);
		if(a == NULL)
			return ;
		if(this->_params[1] == "+O" || this->_params[1] == "+o" || this->_params[1] == "+v" || this->_params[1] == "+b") // mode liee a des users (ON NE GERE PAS B et V)
		{
			if(this->_params[2] == "")
				return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
			Client		*b = a->findClientNick(this->_params[2]);
			if(b == NULL)
			{
				b = this->_server->findNick(this->_params[2]);
				if(b == NULL)
					return ;
				b->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost INVITE " + this->_params[0] + " " + this->_params[1]);
				this->_sender->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost "+ RPL_INVITING + " " + b->getNick() + "_ " + this->_params[1] + " " +this->_params[0]);
			}
			if(this->_params[1] == "+O" || this->_params[1] == "+o")
			{
				a->addOpper(b);
			}
			if(this->_params[1] == "-O" || this->_params[1] == "-o")
			{
				a->rmOpper(b);
			}
		}
		if(this->_params[1] == "+k" || this->_params[1] == "-k" || this->_params[1] == "+l" || this->_params[1] == "-l") // CHAN KEY ET USER CHAN KEY OU USER LIMIT
		{
			if(!(a->isClient(this->_sender)))
				return(this->Message_p(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG(this->_params[2], this->_params[0])));
			if(!(a->isOper(this->_sender)))
				return(this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_params[0])));
			if(this->_params[1] == "+k")
			{
				if(this->_params[2] == "")
					return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
				a->setPass(this->_params[2]);
			}
			if(this->_params[1]  == "-k")
			{
				a->setPass("");
			}
			if(this->_params[1] == "+l")
			{
				if(this->_params[2] == "")
					return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
				a->setUserlimit(ftatoi(this->_params[2]));
			}
			if(this->_params[1] == "-l")
			{
				a->setUserlimit(256);
			}
			if(a != NULL)
				this->_sender->sendMsg(prefix(this->_sender) + " 324 " + this->_sender->getNick() + " " + this->_params[0] + " +" +  a->getMode());
		}
		else if(valid_flags(this->_params[1] , "aimnqpsrt"))
		{
			if(!(a->isClient(this->_sender)))
				return(this->Message_p(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG(this->_params[2], this->_params[0])));
			if(a != NULL)
			{
				if(!(a->isOper(this->_sender)))
					return(this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_params[0])));
				if(this->_params[1] != "")
				{
					if(this->_params[1][0] == '+')
						a->setMode(_params[1]);
					if(this->_params[1][0] == '-')
						a->rmMode(_params[1]);
				}
			}
		}
		if(this->_params[1] == "")
			this->_sender->sendMsg(prefix(this->_sender) + " 324 " + this->_sender->getNick() + " " + this->_params[0] + " +" +  a->getMode());
		else
			this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_CHANNELMODEIS + " " + RPL_CHANNELMODEIS_MSG( this->_sender->getNick() , this->_params[0] , "+" + a->getMode()));
		return ;
	}
	else if(this->_params[0] != "")// USER MODE EN DEHORS DE CHANNEL (DONE)
	{
		Client			*b = this->_server->findClientUser(this->_params[0]);
		if(b == NULL)
			return(this->Message_p(ERR_USERSDONTMATCH, ERR_USERSDONTMATCH_MSG()));
		if(this->_params[1] != "" && valid_flags(this->_params[1], "aiwroOs"))
		{
			if(this->_params[1][0] == '+')
				b->setMode(this->_params[1]);
			if(this->_params[1][0] == '-')
				b->rmMode(this->_params[1]);
			this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_UMODEIS + " " + this->_sender->getNick() + " " + this->_sender->getMode());
		}
		else
			return(this->Message_p(ERR_UMODEUNKNOWNFLAG, ERR_UMODEUNKNOWNFLAG_MSG()));
	}
}

void	irc::Message::who()
{
	if(this->_params[0] != "" && this->_params[0][0] == '#')
	{
		Channel*		b  = this->_server->findChannelFromName(this->_params[0]);
		std::vector<Client*>	a = b->getClients();
		// PAS SUR POUR LE MESSAGE DE WHO
		for(std::vector<Client*>::iterator it = a.begin(); it != a.end() ; it++)
		{
//			this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_WHOREPLY + " " + RPL_WHOREPLY_MSG(this->_params[0], this->_sender->getUsername() , " hostname ", " server " /*server*/ , this->_sender->getNick() , " connect ",  this->_sender->getRealName()));
		}
		this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_ENDOFWHO + " " + this->_sender->getNick() + " " + "localhost" + " " + ":End of /WHO list");
	}
}

// DONE
void	irc::Message::nick()
{
	if(this->_params.size() - 1 == 0)
		this->Message_p(ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG());
	else if(this->_server->findNick(this->_params[0])) // Si c est deja le meme nickname
		this->Message_p(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG(this->_params[0]));
	else if(this->_params[0].length() > 9 || (!isLetter(this->_params[0][0]) && !isSpecial(this->_params[0][0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	else if(!(nick_check_char(this->_params[0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	this->_sender->setNick(this->_params[0]);
}

// DONE (userhost n a pas de allready regisrtered)
void	irc::Message::userhost()
{
	if(this->_params.size() - 1 == 0)
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	this->_sender->setUsername(this->_params[0]);
	//
//	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + RPL_USERHOST_MSG("list ??"));
	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + this->_sender->getNick() + "_ :" + this->_sender->getNick() + "@localhost");
}

// DONE
void	irc::Message::user()
{
	if(this->_params.size() - 1 == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_server->findClient_user(this->_params[0]))
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	this->_sender->setUsername(this->_params[0]);
}

// DONE
void	irc::Message::oper()
{

	if(this->_params[0] == "" || this->_params[1] == ""/* || this->_params[2] == ""*/)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_params[0] != this->_sender->getUsername())
		this->Message_p(ERR_NOOPERHOST, ERR_NOOPERHOST_MSG());
	else if(this->_params[1] != this->_server->getPassword())
		this->Message_p(ERR_PASSWDMISMATCH, ERR_PASSWDMISMATCH_MSG());
	else
	{
		this->_sender->setOper(true);
		this->Message_p(RPL_YOUREOPER, RPL_YOUREOPER_MSG());
	}
}

 void	irc::Message::join()
 {
 	std::vector<std::string>	names;
 	std::vector<std::string>	key;

 	if(this->_params[0] == "")
 		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	names = splitChar(this->_params[0], ',');
	if(this->_params[0] != "" && this->_params[1] != "")
 		key = splitChar(this->_params[1], ',');
 	Channel*	a;
	size_t		v = 0;
	if(this->_params[0] == "0" && this->_params[1] == "")
	{
		return(this->_server->leaveAllChannels(this->_sender));
	}
 	for(std::vector<std::string>::iterator it = names.begin() ; it != names.end() ; it++)
 	{
		int		i = 0;
		a = this->_server->findChannelFromName(_params[0]);
 		if( a != NULL)
 		{
			Channel*	a = this->_server->findChannelFromName(_params[0]);
			size_t	c = 0;
			for(std::vector<std::string>::iterator y = key.begin(); y != key.end(); y++)
			{
				if(c == v)
					if(a->getPass() != "" && a->getPass() != (*y))
					{
						this->_sender->sendMsg(prefix(this->_sender) + " " + ERR_BADCHANNELKEY + " " + ERR_BADCHANNELKEY_MSG(a->getName()));
						return ;
						i = 1;
					}
			}
			if(i == 0)
			{
				if(a->isBan(this->_sender))
					this->Message_p(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MSG(names[v]));
				else if(this->_server->numberChannelsJoin(this->_sender) > 20) // 20 est le nombre max de channels valable
					this->Message_p(ERR_TOOMANYCHANNELS, ERR_TOOMANYCHANNELS_MSG(names[v]));
				else if(names[v][0] == '!' && (a->getName())[0] != '!')
					this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG(names[v], "abbort messages"));
				else
				{
					_sender->addMembership(a);
					a->addClient(this->_sender);
					this->Messagejoin(a);
				}
			}
 		}
		else if(names[v] != "" && ftFind(names[v][0], "#!?") != true)
			this->Message_p(ERR_BADCHANMASK, ERR_BADCHANMASK_MSG(names[v]));
 		else if(names[v] != "")
 		{
 			if(validChannelName(names[v]))
 			{
 			Channel		*h = new Channel(names[v]);

//			printf("\n Prenom set\n");
			if(this->_params[0] != "" && this->_params[1] != "")
			{
				size_t o = 0;
				for(std::vector<std::string>::iterator ut = key.begin(); ut != key.end(); ut++)
				{
					if(v == o)
						h->setPass((*ut));
					o++;
				}
			}
			h->addOpper(this->_sender);
			_sender->addMembership(h); 
			this->Messagejoin(h);
			this->_server->addChannel(h);
			}
			else
 				this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(names[v]));
		}
		v++;
 	}
}

void	irc::Message::part()
{
	if(this->_params[0] == "")
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	Channel*	a = this->_server->findChannelFromName(this->_params[0]);
	if(a != NULL)
	{
		if(!(a->isClient(this->_sender)))
			return(this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG(this->_params[0])));
		std::vector<Client*>	c = a->getClients();
		this->_sender->sendMsg(prefix(this->_sender) + " PART " + a->getName() + this->_msg);
		for(std::vector<Client*>::iterator it = c.begin() ; it != c.end(); it++)
		{
			if((*it) != this->_sender)
				(*it)->sendMsg(prefix(this->_sender) + " PART " + a->getName() + this->_msg);
		}
		// il faut le mettre en away au lieu de l effacer
		a->rmClient(this->_sender);
		_sender->rmMembership(a); 
	}
	else
		return(this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

// 
void	irc::Message::topic()
{
	if(this->_params.size() - 1 == 0)
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG("TOPIC")));
	Channel*	b;
	b = this->_server->findChannelFromName(this->_params[0]);
	if(b != reinterpret_cast<Channel*>(NULL))
	{
		if(!(b->isClient(this->_sender)))
			return(this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG(this->_sender->getNick())));
		if(!(b->isOper(this->_sender)))
			return(this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_sender->getNick())));
		if(this->_params[1] != "")
			b->setTopic(this->_msg);
		if(b->getTopic() == "")
			this->Message_p(RPL_NOTOPIC, RPL_NOTOPIC_MSG(this->_params[0]));
		else
			this->Message_p(RPL_TOPIC, RPL_TOPIC_MSG(this->_params[0], b->getTopic()));
	}
	this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG(this->_params[0]));
}

void	irc::Message::names()
{
	if (_params.size() - 1 > 1)
	{
		for (size_t i = 0; i < _params.size() - 1; i++)
		{
			if (_server->findChannelFromName(_params[i]) != NULL)
			{
				Channel*	tmp = _server->findChannelFromName(_params[i]);
				
				this->Message_p(RPL_NAMEREPLY, RPL_NAMEREPLY_MSG("no_channel_mod", tmp->getName(), tmp->clientList()));
				this->Message_p(RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG(tmp->getName()));
			}
		}
	}
	else
	{
		for (size_t i = 0; i < _server->getChannels().size(); i++)
		{
			Channel*	tmp = _server->getChannels()[i];
				
			this->Message_p(RPL_NAMEREPLY, RPL_NAMEREPLY_MSG("no_channel_mod", tmp->getName(), tmp->clientList()));
			this->Message_p(RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG(tmp->getName()));
		}
	}	
}


char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}


// FLO
void	irc::Message::list()
{
	if (this->_params.size() - 1 > 0 && this->_params[0] != _server->getServername())
	{
		this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_params[0]));
		return ;
	}
	for (int i = 0; i < (int)this->_server->getChannels().size(); i++)
	{
		Channel*	tmp = this->_server->getChannels()[i];
		this->Message_p(RPL_LIST, RPL_LIST_MSG(tmp->getName(), itoa(tmp->getClients().size(), 10), tmp->getTopic()));
	}
	this->Message_p(RPL_LISTEND, RPL_LISTEND_MSG());
}

void	irc::Message::invite()
{

	if(this->_params.size() < 2)
		return(Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG("INVITE")));
	Channel		*g;
	g = this->_server->findChannelFromName(this->_params[1]);
	if(g != reinterpret_cast<Channel*>(NULL))
	{
		if(!(g->isClient(this->_sender)))
			return(Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG(this->_sender->getUsername())));
		if(!(g->isOper(this->_sender)))
			return(Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_sender->getUsername())));
		Client	*c  = this->_server->findClientUser(this->_params[0]); // PEUT ETRE LE FAIRE A PARTIR DE NICK	
		if(c == NULL)
			return(Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0])));
		if((c->getLogged()) == false)
			return(this->Message_p(RPL_AWAY, RPL_AWAY_MSG(this->_params[1], " is away")));
		if(g->isClient(c))
			return(Message_p(ERR_USERONCHANNEL, ERR_USERONCHANNEL_MSG(this->_params[0], this->_params[1])));
		c->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost INVITE " + this->_params[0] + " " + this->_params[1]);
		this->_sender->sendMsg(":" + this->_sender->getNick() + "_!" + "localhost" + "@localhost "+ RPL_INVITING + " " + c->getNick() + "_ " + this->_params[1] + " " +this->_params[0]);
	}
	else
	{
		return(Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0])));
	}
}

void	irc::Message::kick()
{
	if(this->_params.size() < 2)
		return(Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	Channel		*a = this->_server->findChannelFromName(this->_params[0]);
	if(a != reinterpret_cast<Channel*>(NULL))
	{
		if(ftFind(this->_params[0][0], "#&!") == false)
			return(Message_p(ERR_BADCHANMASK, ERR_BADCHANMASK_MSG(this->_params[1])));
		if(!(a->isClient(this->_sender)))
			return(Message_p(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG(this->_params[0], this->_params[1])));
		if(!(a->isOper(this->_sender)))
			return(Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_params[0])));
		Client*						c = a->findClientNick(this->_params[1]);
		std::vector<Client*>		b = a->getClients();
		for(std::vector<Client*>::iterator it = b.begin() ; it != b.end() ; it++)
		{
			(*it)->sendMsg(prefix(this->_sender) + " KICK " + a->getName() + " " + this->_params[1] + this->_msg);
		}
		a->rmClient(c);
		a->addBan(c);
	}
	else
		return(Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

void	irc::Message::privmsg()
{
	std::string		host;
	std::string		user;
	std::string		extension;

	if(this->_params[0] == "")
		return(Message_p(ERR_NORECIPIENT, ERR_NORECIPIENT_MSG(this->_cmds)));
	if(this->_params[1] == "")
		return(Message_p(ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG()));
	if(ftFind('@', this->_params[0]))
	{
		host = cutChar(this->_params[0], '@' , 1);
		user = cutChar(this->_params[0], '@' , 0);
		if(ftFinds("?#", user) || ftFinds("?#", host))
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG(user)));
	}
	if(ftFind('%', this->_params[0]))
	{
		host = cutChar(this->_params[0], '%' , 1);
		user = cutChar(this->_params[0], '%' , 0);
		if(ftFinds("?#", user) || ftFinds("?#", host))
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG(user)));
	}
	if(ftFind('*', this->_params[0]))
	{
		extension = extensionValidPrivmsg(this->_params[0]);
		if(extension == "")
			return(Message_p(ERR_WILDTOPLEVEL, ERR_WILDTOPLEVEL_MSG(extension)));
	}
	if(this->_params[0] != "" && this->_params[0][0] != '#') // USER MODE
	{
		std::vector<Client*>	ext;
		if(extension != "")
			ext = this->_server->findClientUserExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			ext.push_back(this->_server->findClientUser(user));
		else
			ext.push_back(this->_server->findClientUser(this->_params[0]));
		if(ext.size() == 0)
		{
			if(extension == "")
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(extension));
			else if(user != "")
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(user));
			else
				this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0]));
		}
		else
		{
			for(std::vector<Client*>::iterator it = ext.begin(); it != ext.end(); it++)
			{
				if((*it) != NULL && (*it) != this->_sender)
					(*it)->sendMsg(prefix(this->_sender) + " PRIVMSG " + this->_msg);
				//	this->Message_cmds("PRIVMSG" , this->_msg , (*it));
			}
		}
	}
	else
	{
		std::vector<Channel*>	ext;
		
		if(extension != "")
		{
			ext = this->_server->findChannelNameExtension(extension);
		}
		else if(user != "" && host != "" && host == this->_server->getServername())
		{
			ext.push_back(this->_server->findChannelFromName(user));
		}
		else if(user == "")
		{
			if (this->_server->findChannelFromName(this->_params[0]) != NULL)	//added to avoid segfault
				ext.push_back(this->_server->findChannelFromName(this->_params[0]));
		}
		if(ext.size() == 0)
		{
			return(this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG(this->_params[0])));
		}
		else
		{
			std::vector<Client*>	c;
			for(std::vector<Channel*>::iterator it = ext.begin(); it != ext.end() ; it++)
			{
				if((*it)->isClient(this->_sender))
				{
					c = (*it)->getClients();
					for(std::vector<Client*>::iterator ut = (c.begin()) ; ut != (c.end()) ; ut++)
					{
						if((*ut) != NULL && (*ut) != this->_sender)
							(*ut)->sendMsg(prefix(this->_sender) + " PRIVMSG "  + (*it)->getName() + this->_msg);
					}
				}
				else
				{
					this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG((*it)->getName()));
				}
			}
		}
	}
}

void	irc::Message::notice()
{
	std::string		host;
	std::string		user;
	std::string		extension;

	if(this->_params[0] == "")
		return;
	if(this->_params[1] == "")
		return;
	if(ftFind('@', this->_params[0]))
	{
		host = cutChar(this->_params[0], '@' , 1);
		user = cutChar(this->_params[0], '@' , 0);
		if(ftFinds("?#", user) || ftFinds("?#", host))
			return;
	}
	if(ftFind('%', this->_params[0]))
	{
		host = cutChar(this->_params[0], '%' , 1);
		user = cutChar(this->_params[0], '%' , 0);
		if(ftFinds("?#", user) || ftFinds("?#", host))
			return;
	}
	if(ftFind('*', this->_params[0]))
	{
		extension = extensionValidPrivmsg(this->_params[0]);
		if(extension == "")
			return;
	}
	if(this->_params[0] != "" && this->_params[0][0] != '#') // USER MODE
	{
		std::vector<Client*>	ext;
		if(extension != "")
			ext = this->_server->findClientUserExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			ext.push_back(this->_server->findClientUser(user));
		else
			ext.push_back(this->_server->findClientUser(this->_params[0]));
		if(ext.size() != 0)
		{
			for(std::vector<Client*>::iterator it = ext.begin(); it != ext.end(); it++)
			{
				if((*it) != NULL && (*it) != this->_sender)
					(*it)->sendMsg(prefix(this->_sender) + " NOTICE " + this->_msg);
				//	this->Message_cmds("PRIVMSG" , this->_msg , (*it));
			}
		}
	}
	else
	{
		std::vector<Channel*>	ext;
		
		if(extension != "")
		{
			ext = this->_server->findChannelNameExtension(extension);
		}
		else if(user != "" && host != "" && host == this->_server->getServername())
		{
			ext.push_back(this->_server->findChannelFromName(user));
		}
		else if(user == "")
		{
			if (this->_server->findChannelFromName(this->_params[0]) != NULL)	//added to avoid segfault
				ext.push_back(this->_server->findChannelFromName(this->_params[0]));
		}
		if(ext.size() != 0)
		{
			std::vector<Client*>	c;
			for(std::vector<Channel*>::iterator it = ext.begin(); it != ext.end() ; it++)
			{
				if((*it)->isClient(this->_sender))
				{
					c = (*it)->getClients();
					for(std::vector<Client*>::iterator ut = (c.begin()) ; ut != (c.end()) ; ut++)
					{
						if((*ut) != NULL && (*ut) != this->_sender)
							(*ut)->sendMsg(prefix(this->_sender) + " NOTICE "  + (*it)->getName() + this->_msg);
					}
				}
			}
		}
	}


}

void	irc::Message::admin()
{
	if (this->_params.size() - 1 > 0 && this->_params[0] != _server->getServername())
		this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_params[0]));
	else
	{
		this->Message_p(RPL_ADMINME, RPL_ADMINME_MSG(_server->getIRCname()));
		this->Message_p(RPL_ADMINLOC1, RPL_ADMINLOC1_MSG("This is our 42 IRC project :)"));
		this->Message_p(RPL_ADMINLOC2, RPL_ADMINLOC2_MSG("The wonderful admins are Lauranne & Florian : "));
		this->Message_p(RPL_ADMINEMAIL, RPL_ADMINEMAIL_MSG("<labintei@student.42.fr>, <fcavillo@student.42.fr>"));
	}
}

//(nick name collision)
void	irc::Message::kill()
{
	for (size_t i = 0; i < _params.size() - 1; i++)
		std::cout << "param" << i << " = " << _params[i] << std::endl;	
	if (_sender->getOper() == false)
		this->Message_p(ERR_NOPRIVILEGES, ERR_NOPRIVILEGES_MSG());
	else if (_server->findClient_nick(_params[0]) == false)
		this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(_params[0]));		
	else if (this->_params.size() - 1 < 2 || _params[1].size() - 1 <= 1) 
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else
	{
		Client*	tmp = _server->findNick(_params[0]);
		tmp->sendMsg("You were killed by an operator for the following reason " + this->_msg);
		tmp->leaveAllChannels();
		tmp->leaveServer();
		close(tmp->getSocket());
		tmp->setLogged(false);
	}
}

//(DIE oper)
void	irc::Message::die()
{
	if (_sender->getOper() == false)
		this->Message_p(ERR_NOPRIVILEGES, ERR_NOPRIVILEGES_MSG());
	else
		_server->switchOff();
}

void	irc::Message::restart()
{
	if (_sender->getOper() == false)
		this->Message_p(ERR_NOPRIVILEGES, ERR_NOPRIVILEGES_MSG());
	else
		_server->setRestart(true);
}

/////////////////////partie de Flo//////////////////////

void	irc::Message::pong()
{
	if (_params.size() - 1 == 0)
		Message_p(ERR_NOORIGIN, ERR_NOORIGIN_MSG());
	else if (_params.size() - 1 > 1)
		Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_server->getServername()));
	else
		_sender->sendMsg("PONG : " + _params[0]);
	
}

/*	A client session is terminated with a quit message.  */
void	irc::Message::quit()
{
	for (int chan = 0; chan < (int)_sender->getMembership().size() ; chan++)
	{
		std::vector<Client *>	cli_list = _sender->getMembership()[chan]->getClients();
		for (int cli = 0 ; cli < (int)cli_list.size(); cli++)
		{
				(cli_list[cli])->sendMsg(prefix(this->_sender) + " QUIT " + this->_sender->getNick() + " left" + this->_msg);
		}
	}

//QUIT: message or nickname	
	_sender->leaveAllChannels();
	_sender->leaveServer();
	close(_sender->getSocket());
	_sender->setLogged(false);
}

// peut etre a faire squit
//

void	irc::Message::welcome()
{
	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + this->_sender->getNick() + "_ :" + this->_sender->getNick() + "@localhost");
	Message_p(RPL_WELCOME, RPL_WELCOME_MSG(_sender->getNick(), _sender->getUsername(), _server->getServername()));
	Message_p(RPL_YOURHOST, RPL_YOURHOST_MSG(_server->getServername(), "1.0"));
	Message_p(RPL_CREATED, RPL_CREATED_MSG(_server->getStartTimeString()));
	Message_p(RPL_MYINFO, RPL_MYINFO_MSG(_server->getServername(), "1.0", "aiwroOS", "c_modes"));
}
