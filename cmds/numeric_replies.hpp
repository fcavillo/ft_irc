/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <labintei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:44:52 by labintei          #+#    #+#             */
/*   Updated: 2022/03/18 00:07:47 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		NUMERIC_REPLIES_HPP
#define		NUMERIC_REPLIES_HPP

#include "string"

#define		RPL_WELCOME				"001"
std::string	RPL_WELCOME_MSG(std::string prefix){return ":Welcome to the Internet Relay Network " + prefix;}

#define		RPL_YOURHOST			"002"
std::string	RPL_YOURHOST_MSG(std::string server, std::string version){return "Your host is " + servername ", running version " + version;}

#define		RPL_CREATED				"003"
std::string	RPL_CREATED_MSG(std::string time){return "this server was created " + time;}

#define		RPL_MYINFO				"004"
std::string	RPL_MYINFO_MSG(std::string server, std::string version, std::string usermodes, std::string channels)(return server + " " + version + " " + usermodes + " " + channels;)
// SUCESSFUL REGISTRATION

#define		RPL_BOUNCE				"005"
std::string	RPL_BOUNCE_MSG(std::string server, std::string port){return "Try server " + server + ", port " + port;}
#define		RPL_USERHOST			"302"
std::string	RPL_USERHOST_MSG(std::string list){return list;}//?
#define		RPL_ISON				"303"
std::string	RPL_ISON_MSG(std::string list){return list;}//?
#define		RPL_AWAY				"301"
std::string	RPL_AWAY_MSG(std::string nick, std::string msg){return nick + " : " + msg;}
#define		RPL_UNAWAY				"305"
std::string	RPL_UNAWAY_MSG(){return ": You are no longer marked as being away";}
#define		RPL_NOWAWAY				"306"
std::string	RPL_NOWAWAY_MSG(){return ": You have been marked as being away";}
// WHO IS

#define		RPL_WHOISUSER			"311"
std::string	RPL_WHOISUSER_MSG(std::string nick, std::string user, std::string host, std::string real){return nick + " " + user + " " + host + " * :" + real; }
#define		RPL_WHOISSERVER			"312"
std::string	RPL_WHOISSERVER_MSG(std::string nick, std::string server, std::string serverinfo){return nick + " " + server + " " + serverinfo;}
#define		RPL_WHOISOPERATOR		"313"
std::string	RPL_WHOISOPERATOR_MSG(std::string ){}
#define		RPL_WHOISIDLE			"317"
#define		RPL_ENDOFWHOIS			"318"
#define		RPL_WHOISCHANNELS		"319"

// WHOWAS

#define		RPL_WHOWASUSER			"314"
#define		RPL_ENDOFWHOWAS			"369"

// LIST

#define		RPL_LISTSTART			"321" // NOT USED
#define		RPL_LIST				"322"
#define		RPL_LISTEND				"323"

// TOPIC

#define		RPL_UNIQOPIS			"325"
#define		RPL_CHANNELMODEIS		"324"
#define		RPL_NOTOPIC				"331"
#define		RPL_TOPIC				"332"

// INVITE

#define		RPL_INVITING			"341"

// SUMMON

#define		RPL_SUMMONING			"342"
I
// LIST OF INVITATION MASK OF A GIVEN CHANNEL

#define		RPL_INVITELIST			"346"
#define		RPL_ENDOFINVITELIST		"347"

// LIST OF EXCEPTION MASKS FOR A GIVEN CHANNEL

#define		RPL_EXCEPTLIST			"348"
#define		RPL_ENDOFEXCEPTLIST		"349"

// VERSION DETAILS SERVER (DEBUG MODE0

#define		RPL_VERSION				"351"

// WHO

#define		RPL_WHOREPLY			"352"
#define		RPL_ENDOFWHO			"315"

// NAMES 

#define		RPL_NAMEREPLY			"353"
#define		RPL_ENDOFNAMES			"366"

// LINKS

#define		RPL_LINKS				"364"
#define		RPL_ENDOFLINKS			"365"

// LIST LES BANS ACTIF POUR UNE CHAINE DONNE

#define		RPL_BANLIST				"367"
#define		RPL_ENDOFBANLIST		"368"

// INFO

#define		RPL_INFO				"371"
#define		RPL_ENDOINFO			"374"

// MOTD

#define		RPL_MOTDSTART			"375"
#define		RPL_MOTD				"372"
#define		RPL_ENDOFMOTD			"376"

// Sucessful OPPER

#define		RPL_YOUREOPER			"381"

// REHASH OPTIONS

#define		RPL_REHASHING			"382"

//	sucessfull registration

#define		RPL_YOURESERVICE		"383"

// TIME

#define		RPL_TIME				"391"

// USERS

#define		RPL_USSERSSTART			"392"
#define		RPL_USERS				"393"
#define		RPL_ENDOFUSERS			"394"
#define		RPL_NOUSERS				"395"

// TEACE

#define		RPL_TRACELINK			"200"
#define		RPL_TRACECONNECTIMG		"201"
#define		RPL_TRACEHANDSHAKE		"202"
#define		RPL_TRACEUNKNOWN		"203"
#define		RPL_TRACEOPERATOR		"204"
#define		RPL_TRACEUSER			"205"
#define		RPL_TRACESERVER			"206"
#define		RPL_TRACESERVICE		"207"
#define		RPL_TRACENEWTYPE		"208"
#define		RPL_TRACECLASS			"209"
#define		RPL_TRACERECONNECT		"210" // unusued
#define		RPL_TRACELOG			"261"
#define		RPL_TRACEEND			"262"

// report de statistique dans une connection

#define		RPL_STATSLINKINFO		"211"

// reporst statistics on commandse usage

#define		RPL_STATSCOMMANDS		"212"

// reports the server uptime

#define		RPL_ENDOFSTATS			"219"
#define		RPL_STARTUPTIME			"242"

// Les hotes valables quand un user devient un operateur IRC

#define		RPL_STATOLINE			"243"

// To answer to a query about a client s own mode

#define		RPL_UMODEIS				"221"

// SERVLIST

#define		RPL_SERVLIST			"234"
#define		RPL_SERVLISTEND			"235"

// LUSERS

#define		RPL_LUSERCLIENT				"251"
#define		RPL_LUSEROP					"252"
#define		RPL_LUSERUNKNOWN		"	253"
#define		RPL_LUSERCHANNELS			"254"
#define		RPL_LUSERNE					"255"

// ADMIN

#define		RPL_ADMINME					"256"
#define		RPL_ADMINLOC1				"257"
#define		RPL_ADMINLOC2				"258"
#define		RPL_ADMINEMAIL				"259"

// DROP A COMMAND without processing it

#define		RPL_TRYAGAIN				"263"


// ERRORS REPLIES



#define		ERR_NOSUCHNICK				401
#define		ERR_NOSUCHSERVER			402
#define		ERR_NOSUCHCHANNEL			403
#define		ERR_CANNOTSENDTOCHAN		404
#define		ERR_TOOMANYCHANNELS			405
#define		ERR_WASNOSUCHNICK			406
#define		ERR_TOOMANYTARGETS			407
#define		ERR_NOSUCHSERVICE			408
#define		ERR_NOORIGIN				409
#define		ERR_NORECIPIENT				411


// PRIVMSG

#define		ERR_NOTEXTTOSEND			412
#define		ERR_NOTOPLEVEL				413
#define		ERR_WILDTOPLEVEL			414
#define		ERR_BADMASK					415

#define		ERR_UNKNOWCOMMAND			421
#define		ERR_NOMOTD					422
#define		ERR_NOADMININFO				423
#define		ERR_FILEERORR				424
#define		ERR_NONICKNAMEGIVEN			431
#define		ERR_ERRONEUSNICKNAME		432
#define		ERR_NICKNAMEINUSE			433
#define		ERR_NICKCOLLISION			436
#define		ERR_UNAVAILLABLERESOURCE	437
#define		ERR_USERNOTINCHANNEL		441
#define		ERR_NOTONCHANNEL			442
#define		ERR_USERONCHANNEL			443
#define		ERR_NOLOGIN					444
#define		ERR_SUMMONDISABLED			445
#define		ERR_USERSDISABLED			446
#define		ERR_NOTREGISTERED			451
#define		ERR_NEEDMOREPARAMS			461
#define		ERR_ALREADYREGISTRED		462
#define		ERR_NOPERMFORHOST			463
#define		ERR_PASSWDMISMATCH			464
#define		ERR_YOUREBANNEDCREEP		465
#define		ERR_YOUWILLBEBANNED			466
#define		ERR_KEYSET					467
#define		ERR_CHANNELISFULL			471
#define		ERR_UNKNOWMODE				472
#define		ERR_INVITEONLYCHAN			473
#define		ERR_BADCHANNELKEY			475
#define		ERR_BADCHANMASK				476
#define		ERR_NOCHANMODES				477
#define		ERR_BANLISTFULL				478
#define		ERR_NOPRIVILEGES			481
#define		ERR_CHANOPRIVSNEEDED		482
#define		ERR_CANTKILLSERVER			483
#define		ERR_RESTRICTED				484
#define		ERR_UNIQOPPRIVSNEEDED		485
#define		ERR_NOOPERHOST				491
#define		ERR_UMODEUNKNOWNFLAG		501
#define		ERR_USERSDONTMATCH			502


#endif
