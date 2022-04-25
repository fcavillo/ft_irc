/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/04/25 12:38:23 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
#include "../numeric_replies.hpp"

#include "utils.hpp"
#include <iostream>

#include <cstdio>


//if(this->_cmds == "PRIVMSG" || this->_cmds == "NOTICE" || this->_cmds == "PART" || this->_cmds == "QUIT" || this->_cmds == "SQUIT" || this->_cmds == "KICK" || this->_cmds == "KILL")
//		this->_msg = this->getMsg(line); // JE l ai fait de facon simplifier


std::string			prefix(irc::Client *a)
{
	return(":" + a->getNick() + "!" + a->getUsername() + "@" + "localhost");
}
// 
//void	

/*
#define		RPL_NAMEREPLY			"353"
std::string	RPL_NAMEREPLY_MSG(std::string chan_mod, std::string channel, std::string nick_list){return chan_mod + " " + channel + " " + nick_list;}
*/

// faire une commande NAMES / MODE WHO
void	irc::Message::Messagejoininit(/*std::string cmds,*/ /*std::string msg, */irc::Channel* chan)
{
	chan->getName();
//	this->_sender->sendMsg(prefix(this->_sender) + " 353" + " " + this->_sender->getNick() + " = " + chan->getName() + " :@" + this->_sender->getNick());
//	this->_sender->sendMsg(prefix(this->_sender) + " " + "366" + " " + this->_sender->getNick() + " " + chan->getName() + " :End of /NAMES list");
//	this->_sender->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
}


void	irc::Message::Messagejoin(/*std::string cmds,*/ /*std::string msg, */irc::Channel* chan)
{
	std::string s;
	std::vector<Client*>	o = chan->getClients();

/*
	if(o.size() != 0)
	{
		std::vector<Client*>::iterator		c = (o.begin());
		if((*c) != this->_sender)
			this->_sender->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
	}*/
	if(o.size() == 0)
		s += this->_sender->getNick();
	else
	{	
		for(std::vector<Client*>::iterator n = o.begin() ; n != o.end(); n++)
		{
			if((*n) != NULL)
				s += (*n)->getNick();
			if((n + 1) != o.end())
				s+= " ";
		}
	}
	printf("\n TEST %s \n", s.c_str());
	this->_sender->sendMsg(prefix(this->_sender) + " 353" + " " + this->_sender->getNick() + " = " + chan->getName() + " :@" + s);
	this->_sender->sendMsg(prefix(this->_sender) + " " + "366" + " " + this->_sender->getNick() + " " + chan->getName() + " :End of /NAMES list");
//	std::vector<Client*>	o = chan->getClients();
	for(std::vector<Client*>::iterator n = o.begin() ; n != o.end(); n++)
	{
	//	if((*n) != this->_sender)
		//	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_NAMEREPLY + RPL_NAMEREPLY_MSG("+n", chan->getName(), (*n)->getNick()));
		if((*n) != NULL && (*n) != this->_sender /*&& (n != o.begin() || (*n) == this->_sender)*/)
			(*n)->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
	}
	this->_sender->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());


//this->_sender->sendMsg(prefix(this->_sender) + " JOIN :" + chan->getName());
}


void	irc::Message::MessagetoChannel(std::string cmds, std::string msg, Channel* b)
{
	std::vector<Client*>	n = b->getClients();
	for(std::vector<Client*>::iterator ut = n.begin(); ut != n.end() ; ut++)
	{
//		if((*ut) != this->_sender)
			this->Message_cmds(cmds, msg, (*ut));
	}
}
/*
void					irc::Client::sendMsg(std::string msg)
{
	std::cout << "-> Socket[" << _socket << "] : " << msg << std::endl;
	send(_socket, (msg + "\r\n").c_str(), (msg + "\r\n").length(), 0);	//send, on the client socket, the char* str wth no flag
}
*/


void	irc::Message::Message_cmds(std::string cmds, std::string facultatif, Client *a)
{
	// nickname!user@127.0.0.1 PRIVMSG channel :msg/r/n

//	if(facultatif == "")
//		printf("\nMessage envoye : :%s!%s@%s %s \n", (this->_sender->getNick()).c_str() , (this->_sender->getUsername()).c_str() , "127.0.0.1 " , (cmds).c_str() );
//	else
//		printf("\nMessage envoye : :%s!%s@%s %s %s\n", (this->_sender->getNick()).c_str() , (this->_sender->getUsername()).c_str() , "127.0.0.1" , (cmds).c_str() , facultatif.c_str());
	if(facultatif != "")
		a->sendMsg(":" + this->_sender->getNick() + "!" + this->_sender->getUsername() + "@localhost" + " " + cmds + facultatif);
	else
		a->sendMsg(":" + this->_sender->getNick() + "!" + this->_sender->getUsername() + "@localhost" + " " + cmds);
}

void	irc::Message::Message_c(std::string code, std::string code_msg, Client *a)
{
	a->sendMsg(message_print(this->_server->getServername(), code , this->_sender->getNick(), code_msg , this->_sender->getOper()));
}

// a MODIFIER SI ERREUR DE FORMULATION

void	irc::Message::Message_p(std::string code, std::string code_msg)
{
	this->_sender->sendMsg(message_print(this->_server->getServername(), code , this->_sender->getNick(), code_msg , this->_sender->getOper()));
}



// DIFFERENTS DU PASS REGISTRATION DEMANDER A FLORIAN
// POUR NICK USER certificate
void	irc::Message::pass()
{
	if(this->_params.size() == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_sender->getPass() != "")
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
		this->_sender->setPass(this->_params[0]);
}

// POUR METTRE LES MODES AU BON ENDROIT
//
// 3 cas
//
// MODE #i
// MODE #i user
// MODE user
//
// USER mode (SERVER) "+""-" "aiwoOrs"
//
//
//
// USER mode (CHANNEL) 
// CHANNEL mode
//

// A METTRE DANS utils
//
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


// JE GERE TECHNIQUEMENT TOUT LES CAS DEMANDER PAR LE SUJET PEUT ETE DECOUPAGE
// CHECKER LES DIFFERENTES PARTIES
void	irc::Message::mode()
{
	printf("\n1");
	if(this->_params[0] == "")
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	printf("2");
	printf("\n test %s \n", this->_params[0].c_str());
	if(this->_params[0] != "" && this->_params[0][0] == '#')
	{
		printf(" RENTRE DANS LE CAS VOULU");
		// MODE AVEC CHANNEL SANS USER : MODE #i +ioinvonsi
		
		//FAUX
		//if(this->_params[1] == "")
		//	return(this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG(this->_params[1])));
		
		Channel			*a = this->_server->findChannelFromName(_params[0]);
		if(a == NULL)// IL Y A PAS DE MESSAGES D ERRUERS ASSOCIES
			return ;
		printf("\n 3 \n");
		if(this->_params[1] == "+O" || this->_params[1] == "+o" || this->_params[1] == "+v" || this->_params[1] == "+b") // mode liee a des users (ON NE GERE PAS B et V)
		{
			printf("\nPOR ACCORDER DES CHANNEL PRIVILEGES\n");
			if(this->_params[2] == "")
				return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
			Client		*b = a->findClientNick(this->_params[2]);
			if(b == NULL)
			{
				b = this->_server->findNick(this->_params[2]);
				if(b == NULL)
					return ; // ?
				b->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost INVITE " + this->_params[0] + " " + this->_params[1]);
				this->_sender->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost "+ RPL_INVITING + " " + b->getNick() + "_ " + this->_params[1] + " " +this->_params[0]);
			}
			if(this->_params[1] == "+O" || this->_params[1] == "+o")
			{
				a->addOpper(b);
				printf("\nADD OPPER \n");
				if(a->isOper(b))
					printf("\n est bien devenu OPPER\n");
				else
					printf("\nest pas devenu OPPER \n");
			}
			if(this->_params[1] == "-O" || this->_params[1] == "-o")
			{
				a->rmOpper(b);
				printf("\nRM OPPER\n");
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
				// ON va le mettre en valeur par default (je suis pas sur de la valeur fourni)
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
				printf("\n1\n");
				printf("\nPROBLEME AVEC LA PARTIE CI DESSOUS\n");
				if(this->_params[1] != "")
				{
					if(this->_params[1][0] == '+')
						a->setMode(_params[1]);
					if(this->_params[1][0] == '-')
						a->rmMode(_params[1]);
				}
				printf("\n2\n");
//				this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_CHANNELMODEIS + " " + RPL_CHANNELMODEIS_MSG( this->_sender->getNick() , this->_params[0] , "+" + a->getMode()));
//				printf("\nFINISH\n");
			}
		}
		if(this->_params[1] == "")
			this->_sender->sendMsg(prefix(this->_sender) + " 324 " + this->_sender->getNick() + " " + this->_params[0] + " +" +  a->getMode());
		else
			this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_CHANNELMODEIS + " " + RPL_CHANNELMODEIS_MSG( this->_sender->getNick() , this->_params[0] , "+" + a->getMode()));
		printf("\nFINISH\n");
		return ;
		// ???
		//else
		//	return(this->Message_p(ERR_UMODEUNKNOWNFLAG, ERR_UMODEUNKNOWNFLAG_MSG()));
	}
	else if(this->_params[0] != "")// USER MODE EN DEHORS DE CHANNEL (DONE)
	{
		// POUR TROUVER UN USER
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


// 7 params
//
// WHo A FAIRE
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
		this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_ENDOFWHO + " " + this->_sender->getNick() + " " + this->_sender->getUsername() + " " + ":End of /WHO list");
	}
}

// DONE
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
	this->_sender->setNick(this->_params[0]);
}

// DONE (userhost n a pas de allready regisrtered)
void	irc::Message::userhost()
{
	if(this->_params.size() == 0)
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	this->_sender->setUsername(this->_params[0]);
	//
//	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + RPL_USERHOST_MSG("list ??"));
	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + this->_sender->getNick() + "_ :" + this->_sender->getNick() + "@localhost");
}

// DONE
void	irc::Message::user()
{
	if(this->_params.size() == 0)
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_server->findClient_user(this->_params[0]))
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	this->_sender->setUsername(this->_params[0]);
	this->_sender->sendMsg(prefix(this->_sender) + " " + RPL_USERHOST + " " + this->_sender->getNick() + "_ :" + this->_sender->getNick() + "@localhost");
}

// DONE
void	irc::Message::oper()
{

	if(this->_params[0] == "" || this->_params[1] == "" || this->_params[2] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_params[1] != this->_sender->getUsername())
		this->Message_p(ERR_NOOPERHOST, ERR_NOOPERHOST_MSG());
	else if(this->_params[2] != this->_server->getPassword())
		this->Message_p(ERR_PASSWDMISMATCH, ERR_PASSWDMISMATCH_MSG());
	else
	{
		this->_sender->setOper(true);
		this->Message_p(RPL_YOUREOPER, RPL_YOUREOPER_MSG());
	}
}

// DONE maybe some mistake // WORK
 void	irc::Message::join()
 {
 	std::vector<std::string>	names;
 	std::vector<std::string>	key;

	printf("\nCommence join\n");
 	if(this->_params[0] == "")
 		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
 	printf("\n1\n");
	names = splitChar(this->_params[0], ',');
 	printf("\n2\n");
	if(this->_params[0] != "" && this->_params[1] != "")
 		key = splitChar(this->_params[1], ',');
 	Channel*	a;
	size_t		v = 0;
	if(this->_params[0] == "0" && this->_params[1] == "")
	{
		return(this->_server->leaveAllChannels(this->_sender));
		// LEAVE ALL CURRENT CHANNEL ne connais pas les returns et ...
	}
 	for(std::vector<std::string>::iterator it = names.begin() ; it != names.end() ; it++)
 	{
		int		i = 0;
		a = this->_server->findChannelFromName(_params[0]);
 		if( a != NULL)
 		{
			printf("\nBIEN EN TRAIN DE JOINDRE LE CHANNEL DEJA CREEER\n");
			Channel*	a = this->_server->findChannelFromName(_params[0]);
			size_t	c = 0;
			for(std::vector<std::string>::iterator y = key.begin(); y != key.end(); y++)
			{
				if(c == v)
					if(a->getPass() != "" && a->getPass() != (*y))
					{
						printf("\nPas les bon mots de pass , PAS GERER DANS LES AUTRES IRC effectue un retour a la fin\n");
						this->_sender->sendMsg(prefix(this->_sender) + " " + ERR_BADCHANNELKEY + " " + ERR_BADCHANNELKEY_MSG(a->getName()));
						return ;
						i = 1;
					}
			}// QUESTIONS EST CE QUE JE FAIS LE RESTE
			if(i == 0)
			{
				printf("\n RENTRE QUAND MEME ICI\n");
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

			printf("\n Prenom set\n");
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
			h->addClient(this->_sender);
			_sender->addMembership(h); 
			this->Messagejoin(h);
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
	//
	// IL Y A UNE RPL TOPIC DANS JOIN ?? ne voit pas trop ou poser cette chose // irssi fonctionne differement
}


// DONE
void	irc::Message::part()
{
	//std::string		msg = convertVectortoString(this->_params, 1);

	printf("\n1\n");
	if(this->_params[0] == "")
		return(this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds)));
	Channel*	a = this->_server->findChannelFromName(this->_params[0]);
	if(a != NULL)
	{
		printf("\n2\n");
		if(!(a->isClient(this->_sender)))
			return(this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG(this->_params[0])));
		std::vector<Client*>	c = a->getClients();
		printf("\n3\n");
		for(std::vector<Client*>::iterator it = c.begin() ; it != c.end(); it++)
		{
			//if((*it) != this->_sender)
			printf("\n LE message %s \n", this->_msg.c_str());
			(*it)->sendMsg(prefix(this->_sender) + " PART " + a->getName() + this->_msg);
			//this->Message_cmds("PART ", a->getName() + this->_msg,(*it)); // A remis le bon message
		}
		printf("\n4\n");
		a->rmClient(this->_sender);
		printf("\nRm clientM\n");
		if(!a->isClient(this->_sender))
			printf("\nLe client a bien ete remove du channel \n");
		printf("\n5\n");
	}
	else
		return(this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

// 
void	irc::Message::topic()
{
	//std::string		msg = convertVectortoString(this->_params, 1);

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
			b->setTopic(this->_msg);
		if(b->getTopic() == "")
			this->Message_p(RPL_NOTOPIC, RPL_NOTOPIC_MSG(this->_params[0]));
		else
			this->Message_p(RPL_TOPIC, RPL_TOPIC_MSG(this->_params[0], b->getTopic()));
	}
	this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG(this->_params[0]));
}


// FLO
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


// FLO
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

// DONE
void	irc::Message::invite()
{

	if(this->_params.size() < 2)
		return(Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG("INVITE")));
	Channel		*g;
	g = this->_server->findChannelFromName(this->_params[1]);
	// 		bool			_logged;	
	if(g != reinterpret_cast<Channel*>(NULL))
	{
		printf("\nLa channel a bien ete trouvee\n");
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
		printf("\nA bien trouve l user associe\n");
		c->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost INVITE " + this->_params[0] + " " + this->_params[1]);
		this->_sender->sendMsg(":" + this->_sender->getNick() + "_!" + this->_sender->getUsername() + "@localhost "+ RPL_INVITING + " " + c->getNick() + "_ " + this->_params[1] + " " +this->_params[0]);
	}
	else
	{
		return(Message_p(ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG(this->_params[0])));
	}
	// RPL_AWAY
}

//		Client*							findClientNick(std::string nick);

//void					irc::Channel::rmClient(irc::Client* client)


//irc::Client*				irc::Channel::findClientNick(std::string nick)
//{


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
		// MANQUE BAD CHANNEL MASK
	}
	else
		return(Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG(this->_params[0])));
}

//	std::string		cutChar(std::string s, char c, int i)


// DONE mais a revoir
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
		printf("\n OK2 \n");
		extension = extensionValidPrivmsg(this->_params[0]);
		printf("\n OK3 \n");
		if(extension != "")
			printf(" \n extension : %s \n", extension.c_str());
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
					this->Message_cmds("PRIVMSG" , this->_msg , (*it));
			}
		}
	}
	else // CHANNEL MODE
	{
		std::vector<Channel*>	ext;
		
		printf("\n 1\n");
		if(extension != "")
			ext = this->_server->findChannelNameExtension(extension);
		else if(user != "" && host != "" && host == this->_server->getServername())
			ext.push_back(this->_server->findChannelFromName(user));
		else if(user == "")
			ext.push_back(this->_server->findChannelFromName(this->_params[0]));
		if(ext.size() == 0)
			return(this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG(this->_params[0])));
		else
		{
			printf("\nICI POUR LES CHANNELS\n");
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
					//c.clear();
				}
				else
					this->Message_p(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG((*it)->getName()));
			}
			printf("\n GOOD ENDING\n");
		}
	}
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
		// Florian ,il s agit pas uniquement du premier parametres il s agit du msg je t ai rajoute ca
		tmp->sendMsg("You were killed by an operator for the following reason " + this->_msg/*_params[1]*/);
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
	// N A PAS LE MESSAGE DE QUIT
	this->_sender->sendMsg(prefix(this->_sender) + " QUIT" + this->_msg);
}

// peut etre a faire squit
//

void	irc::Message::welcome()
{
	Message_p(RPL_WELCOME, RPL_WELCOME_MSG(_sender->getNick(), _sender->getUsername(), _server->getServername()));
	Message_p(RPL_YOURHOST, RPL_YOURHOST_MSG(_server->getServername(), "1.0"));
	Message_p(RPL_CREATED, RPL_CREATED_MSG(_server->getStartTimeString()));
	Message_p(RPL_MYINFO, RPL_MYINFO_MSG(_server->getServername(), "1.0", "aiwroOS", "c_modes"));
}
