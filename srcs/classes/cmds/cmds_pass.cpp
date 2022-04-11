/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/04/11 20:59:57 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
#include "../numeric_replies.hpp"

#include "utils.hpp"
#include <iostream>

#include <cstdio>


//void	


void	irc::Message::MessagetoChannel(std::string cmds, std::string msg, Channel* b)
{
	std::vector<Client*>	n = b->getClients();
	for(std::vector<Client*>::iterator ut = n.begin(); ut != n.end() ; ut++)
	{
//		if((*ut) != this->_sender)
			this->Message_cmds(cmds, msg, (*ut));
	}
}

void	irc::Message::Message_cmds(std::string cmds, std::string facultatif, Client *a)
{
	printf("\nMessage envoye : %s!%s@%s %s \n", (this->_sender->getNick()).c_str() , (this->_sender->getUsername()).c_str() , (this->_sender->getRealName()).c_str() , (cmds).c_str() );
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
	if(this->_params.size() == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_sender->getPass() != "")
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
		this->_sender->setPass(this->_params[0]);
}


void	irc::Message::nick()
{
	if(this->_params.size() == 0)
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


void	irc::Message::userhost()
{
	if(this->_params.size() == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
//	else if(this->_server->findClient_user(this->_params[0]))
//		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
//	else
//	{
	this->_sender->setUsername(this->_params[0]);
		// voir pour mettre les mode et real name
//	}
}

void	irc::Message::user()
{
	if(this->_params.size() == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
//	else if(this->_server->findClient_user(this->_params[0]))
//		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
//	else
//	{
	this->_sender->setUsername(this->_params[0]);
		// voir pour mettre les mode et real name
//	}
}

void	irc::Message::oper()
{
	if(this->_params.size() == 0)
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

//		void								addChannel(Channel* chan);


 void	irc::Message::join()
 {
 	std::vector<std::string>	names;
 	std::vector<std::string>	key;

	printf("\nCommence join\n");
 	if(this->_params[0] == "")
 		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
 	printf("\n1\n");
	names = splitChar(this->_params[0], ',');
 	printf("\n2\n");/*
	if(this->_params[0] != "" && this->_params[1] != "")
 		key = splitChar(this->_params[1], ',');
	*/printf("\n3\n");
 //	Channel*	a;
//	a = this->_server->findChannelFromName(_params[0]);
 
//	printf("\n %s \n", names[v]);
//	size_t	v = 0;
//	printf("\n %s \n", names[v].c_str());
	size_t		v = 0;
 	for(std::vector<std::string>::iterator it = names.begin() ; it != names.end() ; it++)
 	{
 		if( this->_server->findChannelFromName(_params[0]) != NULL)
 		{
			printf("\nBIEN EN TRAIN DE JOINDRE LE CHANNEL DEJA CREEER\n");
			Channel*	a = this->_server->findChannelFromName(_params[0]);
 			//if(a->getPass() != "" && a->getPass() != key[v])
 			//	this->Message_p(ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_MSG(names[v]));
 			/*else*/ 
			printf("\n1\n");
			if(a->isBan(this->_sender))
 				this->Message_p(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MSG(names[v]));
 			else if(this->_server->numberChannelsJoin(this->_sender) > 20) // 20 est le nombre max de channels valable
 				this->Message_p(ERR_TOOMANYCHANNELS, ERR_TOOMANYCHANNELS_MSG(names[v]));
			else if(names[v][0] == '!' && (a->getName())[0] != '!')
				this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG(names[v], "abbort messages"));
			else
			{
				printf("\n2\n");
				std::vector<Client*>		g = a->getClients();
				for(std::vector<Client*>::iterator it  = g.begin(); it != g.end() ; it++)
				{
					Message_cmds("JOIN " , a->getName() , (*it));
				}
				a->addClient(this->_sender);
				// _sender->addMembership(a); a rajouter ?
			}
 		}
 		else
 		{
 			if(validChannelName(names[v]))
 			{
 			Channel		*h = new Channel(names[v]);

			printf("\n Prenom set\n");
			/*if(this->_params[0] != "" && this->_params[1] != "")
			{
				for(size_t c = 0; key[c] != "" ; c++)
				{
					if(c == v)
						h->setPass(key[c]);
				}
			}*/
			 //CETTE FONCTION NE MARCHE PEUT ETRE PAS
 			//this->_server->getChannels().push_back(h);
			h->addClient(this->_sender);
			this->_server->addChannel(h);
			if(this->_server->findChannel(h))
				printf("\n CHannel bien integre \n");
			}
			else
 				this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(names[v]));
		}
		v++;
 	}

	// Des qu un user join un channel touts les autres user sont imforme
	// nick!user@client_name


	// Quand un client cherche a rejindre un channel qui a ! et qui a plusieurs short name equivalents
	// this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG());
}

void	irc::Message::part()
{
	std::string		msg = convertVectortoString(this->_params, 1);

	if(this->_params.size() == 0)
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	Channel*	a = this->_server->findChannelFromName(this->_params[0]);
	if(a != reinterpret_cast<Channel*>(NULL))
	{
		if(!(a->isClient(this->_sender)))
			return(this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG(this->_params[0])));
		std::vector<Client*>	c = a->getClients();
		for(std::vector<Client*>::iterator it = c.begin() ; it != c.end(); it++)
		{
			if((*it) != this->_sender)
				this->Message_c("PART",msg,(*it));
		}
	}
	else
		return(this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

void	irc::Message::topic()
{
	std::string		msg = convertVectortoString(this->_params, 1);

	if(this->_params.size() == 0)
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
		{
			b->setTopic(msg);
			this->Message_p(RPL_TOPIC, RPL_TOPIC_MSG(this->_params[0], b->getTopic()));
		}
		else
		{
			if(b->getTopic() == "")
				this->Message_p(RPL_NOTOPIC, RPL_NOTOPIC_MSG(this->_params[0]));
			else
				this->Message_p(RPL_TOPIC, RPL_TOPIC_MSG(this->_params[0], b->getTopic()));
		}

	}


/*
	this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	this->Message_p(ERR_NOTOPIC, ERR_NOTOPIC_MSG());
	this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG());
	this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG());
	this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG());*/
}

void	irc::Message::names()
{
// std::cout << "FloNames()1" << std::endl;	
	if (_params.size() > 0)
	{
	// std::cout << "FloNames()2" << std::endl;	
		for (size_t i = 0; i < _params.size(); i++)
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
	// std::cout << "FloNames()5" << std::endl;	
		for (size_t i = 0; i < _server->getChannels().size(); i++)
		{
			Channel*	tmp = _server->getChannels()[i];
				
			this->Message_p(RPL_NAMEREPLY, RPL_NAMEREPLY_MSG("no_channel_mod", tmp->getName(), tmp->clientList()));
			this->Message_p(RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG(tmp->getName()));
		}
	}	
// std::cout << "FloNames()9" << std::endl;	
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
// std::cout << "FloList()1" << std::endl;
	if (this->_params.size() > 0 && this->_params[0] != _server->getServername())
	{
// std::cout << "FloList()2" << std::endl;
		this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_params[0]));
		return ;
	}
	for (int i = 0; i < (int)this->_server->getChannels().size(); i++)
	{
// std::cout << "FloList()6" << std::endl;
		Channel*	tmp = this->_server->getChannels()[i];
		this->Message_p(RPL_LIST, RPL_LIST_MSG(tmp->getName(), itoa(tmp->getClients().size(), 10), tmp->getTopic()));
	}
	this->Message_p(RPL_LISTEND, RPL_LISTEND_MSG());
// std::cout << "FloList()9" << std::endl;
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
		Client	*c;
		c = this->_server->findClientUser(this->_params[1]); // PEUT ETRE LE FAIRE A PARTIR DE NICK
		if(c == reinterpret_cast<Client*>(NULL))
			return(Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[1])));
		if(g->isClient(c))
			return(Message_p(ERR_USERONCHANNEL, ERR_USERONCHANNEL_MSG(this->_params[0], this->_params[1])));
		Message_c(RPL_INVITING , RPL_INVITING_MSG(g->getName(), this->_params[1]) ,c);
		Message_p(RPL_INVITING, RPL_INVITING_MSG(g->getName(), this->_params[1]));
	}
	else
	{
		return(Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[1])));
	}
}

//		Client*							findClientNick(std::string nick);

//void					irc::Channel::rmClient(irc::Client* client)


void	irc::Message::kick()
{
	if(this->_params.size() < 2)
		return(Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	Channel		*a = this->_server->findChannelFromName(this->_params[0]);
	if(a != reinterpret_cast<Channel*>(NULL))
	{
		if(a->getName()[0] != this->_params[0][0])
			return(Message_p(ERR_BADCHANMASK, ERR_BADCHANMASK_MSG(this->_params[1])));
		if(!(a->isClient(this->_sender)))
			return(Message_p(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG(this->_params[0], this->_params[1])));
		if(!(a->isOper(this->_sender)))
			return(Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG(this->_params[0])));
		//MessagetoChannel(std::string cdms, std::string facultatif, Channel* b)
		Client*		s = a->findClientNick(this->_params[1]);
		if(s == reinterpret_cast<Client*>(NULL))
			return(Message_p(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG(this->_params[0], this->_params[1])));
		MessagetoChannel("KICK", "" , a);
		a->rmClient(s);
		a->addBan(s);
		// MANQUE BAD CHANNEL MASK
	}
	else
		return(Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

//	std::string		cutChar(std::string s, char c, int i)



void	irc::Message::privmsg()
{
	// PREND EN PARAMETRE SOIT
	//
	// UN user 
	// UN channel
	//
	//
	//
	std::string		host;
	std::string		user;
	std::string		extension;
	
	std::string		msg;
	// WILDCARD '*' && '?' // NE CONNAIT PAS L UTILITEE DE ?


	msg = 	convertVectortoString(this->_params, 1);

/*if(this->_params.size() == 0)
		return(Message_p(ERR_NORECIPIENT, ERR_NORECIPIENT_MSG(this->_cmds)));
	if(this->_params.size() == 1)
		return(Message_p(ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG()));
	msg = 	convertVectortoString(this->_params, 1);
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
	// si mode incorrect (pas gerer) ou le user est ban du channel ou ne se trouve pas dans le channel
	// sera un envoit user
*/	if(this->_params[0] != "" && this->_params[0][0] != '#')
	{
		Client*					a;
		Client*					nullClient;
		std::vector<Client*>	ext;
		nullClient = NULL;
		a = NULL;

/*		if(extension != "")
			ext = this->_server->findClientUserExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			a = this->_server->findClientUser(user);
		else if(user == "")
*/		a = this->_server->findClientUser(this->_params[0]);
		if(a == nullClient || ext.size() == 0)
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
			if(extension == "")
				this->Message_cmds("PRIVMSG", msg, a);
			else if(extension != "" && ext.size() != 0)
			{
				for(std::vector<Client*>::iterator it = ext.begin(); it != ext.end(); it++)
				{
			//		if((*it) != this->_sender)
					this->Message_cmds("PRIVMSG", msg , (*it));
				}
			}
		}
	}
	else
	{
		Channel*				b;
		Channel*				nullChannel;
		std::vector<Channel*>	ext;
		nullChannel = NULL;
		b = NULL;
		
		printf("\n 1\n");
//		if(extension != "")
//			ext = this->_server->findChannelNameExtension(extension);
//		else if(user != "" && host != "" && host == this->_server->getServername())
//			b = this->_server->findChannelFromName(user);
//		else if(user == "")
		b = this->_server->findChannelFromName(this->_params[0]);
		printf("\n 2\n");
// ne peut pas etre egale a nul ??

//		if(b == nullChannel && ext.size() == 0)
//		{
//			return(this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG(this->_params[0])));
//		}
//		else
//		{
		/*	if(ext.size() != 0 && extension != "")
			{
				for(std::vector<Channel*>::iterator it = ext.begin(); it != ext.end() ; it++)
				{
					if((*it)->isClient(this->_sender))
					{
						std::vector<Client*>	c = (*it)->getClients();
						for(std::vector<Client*>::iterator ut = c.begin(); ut != c.end() ; ut++)
						{
							if((*ut) != this->_sender)
								this->Message_c("PRIVMSG", msg, (*ut));
						}
					}
					else
						this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG((*it)->getName()));
				}*/
//			}
//			else
//			{
			//	if(b->isClient(this->_sender))
			//	{
			if(b == nullChannel)
				printf("\nb est un null pointeur \n");
			printf("\n ENVO DANS CHANNEL\n");
			std::vector<Client*>	n = b->getClients();
			for(std::vector<Client*>::iterator ut = n.begin(); ut != n.end() ; ut++)
			{
				//if((*ut) != this->_sender)
				printf("\n A ENVOYER\n");
				this->Message_cmds("PRIVMSG", msg, (*ut));
			}
			printf("\n\n");
			//	}
			//	else
			//		this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG(this->_params[1]));
	//		}
	//	}

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
{
	if (this->_params.size() > 0 && this->_params[0] != _server->getServername())
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
	for (size_t i = 0; i < _params.size(); i++)
		std::cout << "param" << i << " = " << _params[i] << std::endl;	
	if (_sender->getOper() == false)
		this->Message_p(ERR_NOPRIVILEGES, ERR_NOPRIVILEGES_MSG());
	else if (_server->findClient_nick(_params[0]) == false)
		this->Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(_params[0]));		
	else if (this->_params.size() < 2 || _params[1].size() <= 1)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else
	{
		
// std::cout << "FloKill()3" << std::endl;	
		Client*	tmp = _server->findNick(_params[0]);
		tmp->sendMsg("You were killed by an operator for the following reason " + _params[1]);
// std::cout << "FloKill()3.1 " << tmp->getServer()->getServername() << std::endl;	
		tmp->leaveAllChannels();
// std::cout << "FloKill()3.2 " << tmp->getServer()->getServername() << std::endl;	
		tmp->leaveServer();
// std::cout << "FloKill()4 " << std::endl;	
		close(tmp->getSocket());
// std::cout << "FloKill()5" << std::endl;	
		tmp->setLogged(false);
	}
// std::cout << "FloKill()9" << std::endl;	
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
//add message
	// if (_params.size() > 0)
	//message public ?	
}

void	irc::Message::welcome()
{
	Message_p(RPL_WELCOME, RPL_WELCOME_MSG(_sender->getNick(), _sender->getUsername(), _server->getServername()));
	Message_p(RPL_YOURHOST, RPL_YOURHOST_MSG(_server->getServername(), "1.0"));
	Message_p(RPL_CREATED, RPL_CREATED_MSG(_server->getStartTimeString()));
	Message_p(RPL_MYINFO, RPL_MYINFO_MSG(_server->getServername(), "1.0", "aiwroOS", "c_modes"));
}
