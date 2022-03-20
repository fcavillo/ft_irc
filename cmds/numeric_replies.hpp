/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <labintei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:44:52 by labintei          #+#    #+#             */
/*   Updated: 2022/03/20 03:35:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		NUMERIC_REPLIES_HPP
#define		NUMERIC_REPLIES_HPP

#include "string"

#define		RPL_WELCOME				001
std::string	RPL_WELCOME_MSG(std::string prefix){return ":Welcome to the Internet Relay Network " + prefix;}

#define		RPL_YOURHOST			002
std::string	RPL_YOURHOST_MSG(std::string server, std::string version){return "Your host is " + servername ", running version " + version;}

#define		RPL_CREATED				003
std::string	RPL_CREATED_MSG(std::string time){return "this server was created " + time;}

#define		RPL_MYINFO				004
std::string	RPL_MYINFO_MSG(std::string server, std::string version, std::string usermodes, std::string channels)(return server + " " + version + " " + usermodes + " " + channels;)
// SUCESSFUL REGISTRATION

#define		RPL_BOUNCE				005
std::string	RPL_BOUNCE_MSG(std::string server, std::string port){return "Try server " + server + ", port " + port;}
#define		RPL_USERHOST			302
std::string	RPL_USERHOST_MSG(std::string list){return list;}//?
#define		RPL_ISON				303
std::string	RPL_ISON_MSG(std::string list){return list;}//?
#define		RPL_AWAY				301
std::string	RPL_AWAY_MSG(std::string nick, std::string msg){return nick + " : " + msg;}
#define		RPL_UNAWAY				305
std::string	RPL_UNAWAY_MSG(){return ": You are no longer marked as being away";}
#define		RPL_NOWAWAY				306
std::string	RPL_NOWAWAY_MSG(){return ": You have been marked as being away";}
// WHO IS

#define		RPL_WHOISUSER			311
std::string	RPL_WHOISUSER_MSG(std::string nick, std::string user, std::string host, std::string real){return nick + " " + user + " " + host + " * :" + real; }
#define		RPL_WHOISSERVER			312
std::string	RPL_WHOISSERVER_MSG(std::string nick, std::string server, std::string serverinfo){return nick + " " + server + " " + serverinfo;}
#define		RPL_WHOISOPERATOR		313
std::string	RPL_WHOISOPERATOR_MSG(std::string nick){return nick + ":is an operator";}
#define		RPL_WHOISIDLE			317
std::string	RPL_WHOISIDLE_MSG(std::string nick, std::string integer){return nick + " " + integer + ":second idle";}
#define		RPL_ENDOFWHOIS			318
std::string	RPL_ENDOFWHOIS_MSG(std::string nick){return nick + " :End of WHOIS list";}
#define		RPL_WHOISCHANNELS		319
std::string	RPL_WHOISCHANNELS_MSG(std::string nick, std::string channel ){return nick + " :" + channel;}
// WHOWAS

#define		RPL_WHOWASUSER			314
std::string	RPL_WHOWASUSER_MSG(std::string nick, std::string user, std::string host, std::string realname){return nick + " " + user + " " + host + " :" + realname;}
#define		RPL_ENDOFWHOWAS			369
std::string	RPL_ENDOFWHOWAS_MSG(std::string nick){return nick + ":End of WHOWAS";}

// LIST

#define		RPL_LISTSTART			321 // NOT USED
#define		RPL_LIST				322
std::string	RPL_LIST_MSG(std::string channel, std::string nbusers,  std::string topic){return channel + " " + nbusers +" :" + topic;}
#define		RPL_LISTEND				323
std::string	RPL_LISTEND_MSG(){return ":End of LIST";}
// TOPIC

#define		RPL_UNIQOPIS			325
std::string	RPL_UNIQOPIS_MSG(std::string channel, std::string topic){return channel + " " + topic;}
#define		RPL_CHANNELMODEIS		324
std::string	RPL_CHANNELMODEIS_MSG(std::string channel, std::string mode, std::string modepar){return channel + " " + mode + " " + modepar;}
#define		RPL_NOTOPIC				331
std::string	RPL_NOTOPIC_MSG(std::string channel){return channel + ":No topic is set";}
#define		RPL_TOPIC				332
std::string	RPL_TOPIC_MSG(std::string channel, std::string topic){return channel + " :" + topic;}

// INVITE

#define		RPL_INVITING			341
std::string	RPL_INVITING_MSG(std::string channel, std::string nick){return channel + " " + nick;}
// SUMMON

#define		RPL_SUMMONING			342
std::string	RPL_SUMMONING_MSG(std::string user){return user + " :Summoning user IRC";}

// LIST OF INVITATION MASK OF A GIVEN CHANNEL

#define		RPL_INVITELIST			346
std::string	RPL_INVITELIST_MSG(std::string channel, std::string inmask){return channel + " " + inmask;}
#define		RPL_ENDOFINVITELIST		347
std::string	RPL_ENDOFINVITELIST_MSG(std::string channel){return channel + " :End of channel invite list"};
// LIST OF EXCEPTION MASKS FOR A GIVEN CHANNEL

#define		RPL_EXCEPTLIST			348
std::string	RPL_EXCEPTLIST_MSG(std::string channel, std::string exceptmask){return channel + " " + exceptmask;}
#define		RPL_ENDOFEXCEPTLIST		349
std::string	RPL_ENDOFEXCEPTLIST_MSG(std::string channel){return channel + " :End of invite list";}

// VERSION DETAILS SERVER (DEBUG MODE0

#define		RPL_VERSION				351
std::string	RPL_VERSION_MSG(std::string version. std::string debug, std::string server, std::string comments){return version + "." + debug + " " + server + " :" + comments;}

// WHO

#define		RPL_WHOREPLY			352
std::string	RPL_WHOREPLY_MSG(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string state, std::string real ){return channel + " " + user + " " + host + " " + server + " " + nick + " " + state + " " + real;}
#define		RPL_ENDOFWHO			315
std::string	RPL_ENDOFWHO_MSG(std::string name){return name + " :End of WHO list";}
// NAMES 

#define		RPL_NAMEREPLY			353
std::string	RPL_NAMEREPLY_MSG(std::string chan_mod, std::string channel, std::string nick_list){return chan_mod + " " + channel + " " + nick_list;}
#define		RPL_ENDOFNAMES			366
std::string	RPL_ENDOFNAMES_MSG(std::string channel){return channel + " :End of NAMES list";}
// LINKS

#define		RPL_LINKS				364
std::string	RPL_LINKS_MSG(std::string mask, std::string server, std::string hopcount, std::string serverinfo){return mask + " " + server + " :" + hopcount + " " + serverinfo;}
#define		RPL_ENDOFLINKS			365
std::string	RPL_ENDOFLINKS_MSG(std::string mask){return mask + " :End of LINKS list";}

// LIST LES BANS ACTIF POUR UNE CHAINE DONNE

#define		RPL_BANLIST				367
std::string	RPL_BANLIST_MSG(std::string channel, std::string banmask){return channel + " " + banmask;}
#define		RPL_ENDOFBANLIST		368
std::string	RPL_ENDOFBANLIST_MSG(std::string channel){return channel + ":End of channel ban list";}

// INFO

#define		RPL_INFO				371
std::string	RPL_INFO_MSG(std::string string){return ":" + string;}
#define		RPL_ENDOFINFO			374
std::string	RPL_ENDOFINFO_MSG(){return "End of INFO list";}

// MOTD

#define		RPL_MOTDSTART			375
std::string	RPL_MOTDSTART_MSG(std::string server){return ":- " + server + " Message of the day";}
#define		RPL_MOTD				372
std::string	RPL_MOTD_MSG(std::string text){return ":- " + test;}
#define		RPL_ENDOFMOTD			376
std::string	RPL_ENDOFMOTD_MSG(){return ": End of MOTD command";}

// Sucessful OPPER

#define		RPL_YOUREOPER			381
std::string	RPL_YOUREOPER_MSG(){return ":You are now an IRC operator";}

// REHASH OPTIONS

#define		RPL_REHASHING			382
std::string	RPL_REHASHING_MSG(std::string config){return config + " :Rehashing";}
//	sucessfull registration

#define		RPL_YOURESERVICE		383
std::string	RPL_YOURESERVICE_MSG(std::string servicename){return "You are service " + servicename;}
// TIME

#define		RPL_TIME				391
std::string	RPL_TIME_MSG(std::string server, std::string time){return server + " :" + time;}
// USERS

#define		RPL_USSERSSTART			392
std::string	RPL_USSERSSTART_MSG(){return ":UserID	Terminal	Host";}
#define		RPL_USERS				393
std::string	RPL_USERS_MSG(std::string user, std::string term, std::string host){return ":" + user + "	" + term + "	" + host;}
#define		RPL_ENDOFUSERS			394
std::string	RPL_ENDOFUSERS_MSG(){return ":End of Users";}
#define		RPL_NOUSERS				395
std::string	RPL_NOUSERS_MSG(){return ":Nobody logged in";}

// TRACE

#define		RPL_TRACELINK			200
std::string	RPL_TRACELINK_MSG(std::string versiondebug, std::string dest, std::string nextserver, std::string proto, std::string linkuptime, std::string backupsend, std::string upstreamsend){return "Link " + versiondebug + " " + dest + " " + nestserver + " V" + proto + " " + linkuptime + " " + backupsend + " " + upstreamsend;}
#define		RPL_TRACECONNECTING		201
std::string	RPL_TRACECONNECTING_MSG(std::string classe, std::string server){return "Try. " + classe + " " + server;}
#define		RPL_TRACEHANDSHAKE		202
std::string	RPL_TRACEHANDSHAKE_MSG(std::string classe, std::string server){return "H.S. " + classe + " " + server;}
#define		RPL_TRACEUNKNOWN		203
std::string	RPL_TRACEUNKNOWN_MSG(std::string classe,std::string ip){return "???? " + classe + " " + ip;}
#define		RPL_TRACEOPERATOR		204
std::string	RPL_TRACEOPERATOR_MSG(std::string classe, std::string nick){return "Oper " + classe + " " + nick;}
#define		RPL_TRACEUSER			205
std::string	RPL_TRACEUSER_MSG(std::string classe, std::string nick){return "User " + classe + " " + nick;}
#define		RPL_TRACESERVER			206
#define		RPL_TRACESERVICE		207
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
