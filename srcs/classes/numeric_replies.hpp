/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:44:52 by labintei          #+#    #+#             */
/*   Updated: 2022/04/07 17:43:09 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		NUMERIC_REPLIES_HPP
#define		NUMERIC_REPLIES_HPP

#include <iostream>
#include <cstring>

std::string message_print(std::string nameserver, std::string code, std::string nick, std::string msg, bool op)
{
    if(op == true)
        return("*:" + nameserver + " " + code + " " + nick + " " + msg);
    else
        return(":" + nameserver + " " + code + " " + nick + " " + msg);
}

#define		RPL_WELCOME				"001"
std::string	RPL_WELCOME_MSG(std::string nick, std::string user, std::string host){return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host;}

#define		RPL_YOURHOST			"002"
std::string	RPL_YOURHOST_MSG(std::string servername, std::string version){return ("Your host is " + servername + ", running version " + version);}

#define		RPL_CREATED				"003"
std::string	RPL_CREATED_MSG(std::string time){return "this server was created " + time;}

#define		RPL_MYINFO				"004"
std::string	RPL_MYINFO_MSG(std::string server, std::string version, std::string usermodes, std::string channels){return (server + " " + version + " " + usermodes + " " + channels);}
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
std::string	RPL_WHOISOPERATOR_MSG(std::string nick){return nick + ":is an operator";}
#define		RPL_WHOISIDLE			"317"
std::string	RPL_WHOISIDLE_MSG(std::string nick, std::string integer){return nick + " " + integer + ":second idle";}
#define		RPL_ENDOFWHOIS			"318"
std::string	RPL_ENDOFWHOIS_MSG(std::string nick){return nick + " :End of WHOIS list";}
#define		RPL_WHOISCHANNELS		"319"
std::string	RPL_WHOISCHANNELS_MSG(std::string nick, std::string channel ){return nick + " :" + channel;}
// WHOWAS

#define		RPL_WHOWASUSER			"314"
std::string	RPL_WHOWASUSER_MSG(std::string nick, std::string user, std::string host, std::string realname){return nick + " " + user + " " + host + " :" + realname;}
#define		RPL_ENDOFWHOWAS			"369"
std::string	RPL_ENDOFWHOWAS_MSG(std::string nick){return nick + ":End of WHOWAS";}

// LIST

#define		RPL_LISTSTART			"321" // NOT USED
#define		RPL_LIST				"322"
std::string	RPL_LIST_MSG(std::string channel, std::string nbusers,  std::string topic){return channel + " " + nbusers +" :" + topic;}
#define		RPL_LISTEND				"323"
std::string	RPL_LISTEND_MSG(){return ":End of LIST";}
// TOPIC

#define		RPL_UNIQOPIS			"325"
std::string	RPL_UNIQOPIS_MSG(std::string channel, std::string topic){return channel + " " + topic;}
#define		RPL_CHANNELMODEIS		"324"
std::string	RPL_CHANNELMODEIS_MSG(std::string channel, std::string mode, std::string modepar){return channel + " " + mode + " " + modepar;}
#define		RPL_NOTOPIC				"331"
std::string	RPL_NOTOPIC_MSG(std::string channel){return channel + ":No topic is set";}
#define		RPL_TOPIC				"332"
std::string	RPL_TOPIC_MSG(std::string channel, std::string topic){return channel + " :" + topic;}

// INVITE

#define		RPL_INVITING			"341"
std::string	RPL_INVITING_MSG(std::string channel, std::string nick){return channel + " " + nick;}
// SUMMON

#define		RPL_SUMMONING			"342"
std::string	RPL_SUMMONING_MSG(std::string user){return user + " :Summoning user IRC";}

// LIST OF INVITATION MASK OF A GIVEN CHANNEL

#define		RPL_INVITELIST			"346"
std::string	RPL_INVITELIST_MSG(std::string channel, std::string inmask){return channel + " " + inmask;}
#define		RPL_ENDOFINVITELIST		"347"
std::string	RPL_ENDOFINVITELIST_MSG(std::string channel){return channel + " :End of channel invite list";}
// LIST OF EXCEPTION MASKS FOR A GIVEN CHANNEL

#define		RPL_EXCEPTLIST			"348"
std::string	RPL_EXCEPTLIST_MSG(std::string channel, std::string exceptmask){return channel + " " + exceptmask;}
#define		RPL_ENDOFEXCEPTLIST		"349"
std::string	RPL_ENDOFEXCEPTLIST_MSG(std::string channel){return channel + " :End of invite list";}

// VERSION DETAILS SERVER (DEBUG MODE0

#define		RPL_VERSION				"351"
std::string	RPL_VERSION_MSG(std::string version, std::string debug, std::string server, std::string comments){return version + "." + debug + " " + server + " :" + comments;}

// WHO

#define		RPL_WHOREPLY			"352"
std::string	RPL_WHOREPLY_MSG(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string state, std::string real ){return channel + " " + user + " " + host + " " + server + " " + nick + " " + state + " " + real;}
#define		RPL_ENDOFWHO			"315"
std::string	RPL_ENDOFWHO_MSG(std::string name){return name + " :End of WHO list";}
// NAMES 

#define		RPL_NAMEREPLY			"353"
std::string	RPL_NAMEREPLY_MSG(std::string chan_mod, std::string channel, std::string nick_list){return chan_mod + " " + channel + " " + nick_list;}
#define		RPL_ENDOFNAMES			"366"
std::string	RPL_ENDOFNAMES_MSG(std::string channel){return channel + " :End of NAMES list";}
// LINKS

#define		RPL_LINKS				"364"
std::string	RPL_LINKS_MSG(std::string mask, std::string server, std::string hopcount, std::string serverinfo){return mask + " " + server + " :" + hopcount + " " + serverinfo;}
#define		RPL_ENDOFLINKS			"365"
std::string	RPL_ENDOFLINKS_MSG(std::string mask){return mask + " :End of LINKS list";}

// LIST LES BANS ACTIF POUR UNE CHAINE DONNE

#define		RPL_BANLIST				"367"
std::string	RPL_BANLIST_MSG(std::string channel, std::string banmask){return channel + " " + banmask;}
#define		RPL_ENDOFBANLIST		"368"
std::string	RPL_ENDOFBANLIST_MSG(std::string channel){return channel + ":End of channel ban list";}

// INFO

#define		RPL_INFO				"371"
std::string	RPL_INFO_MSG(std::string string){return ":" + string;}
#define		RPL_ENDOFINFO			"374"
std::string	RPL_ENDOFINFO_MSG(){return "End of INFO list";}

// MOTD

#define		RPL_MOTDSTART			"375"
std::string	RPL_MOTDSTART_MSG(std::string server){return ":- " + server + " Message of the day";}
#define		RPL_MOTD				"372"
std::string	RPL_MOTD_MSG(std::string text){return ":- " + text;}
#define		RPL_ENDOFMOTD			"376"
std::string	RPL_ENDOFMOTD_MSG(){return ": End of MOTD command";}

// Sucessful OPER

#define		RPL_YOUREOPER			"381"
std::string	RPL_YOUREOPER_MSG(){return ":You are now an IRC operator";}

// REHASH OPTIONS

#define		RPL_REHASHING			"382"
std::string	RPL_REHASHING_MSG(std::string config){return config + " :Rehashing";}
//	sucessfull registration

#define		RPL_YOURESERVICE		"383"
std::string	RPL_YOURESERVICE_MSG(std::string servicename){return "You are service " + servicename;}
// TIME

#define		RPL_TIME				"391"
std::string	RPL_TIME_MSG(std::string server, std::string time){return server + " :" + time;}
// USERS

#define		RPL_USSERSSTART			"392"
std::string	RPL_USSERSSTART_MSG(){return ":UserID	Terminal	Host";}
#define		RPL_USERS				"393"
std::string	RPL_USERS_MSG(std::string user, std::string term, std::string host){return ":" + user + "	" + term + "	" + host;}
#define		RPL_ENDOFUSERS			"394"
std::string	RPL_ENDOFUSERS_MSG(){return ":End of Users";}
#define		RPL_NOUSERS				"395"
std::string	RPL_NOUSERS_MSG(){return ":Nobody logged in";}

// TRACE

#define		RPL_TRACELINK			"200"
std::string	RPL_TRACELINK_MSG(std::string versiondebug, std::string dest, std::string nextserver, std::string proto, std::string linkuptime, std::string backupsend, std::string upstreamsend){return "Link " + versiondebug + " " + dest + " " + nextserver + " V" + proto + " " + linkuptime + " " + backupsend + " " + upstreamsend;}
#define		RPL_TRACECONNECTING		"201"
std::string	RPL_TRACECONNECTING_MSG(std::string classe, std::string server){return "Try. " + classe + " " + server;}
#define		RPL_TRACEHANDSHAKE		"202"
std::string	RPL_TRACEHANDSHAKE_MSG(std::string classe, std::string server){return "H.S. " + classe + " " + server;}
#define		RPL_TRACEUNKNOWN		"203"
std::string	RPL_TRACEUNKNOWN_MSG(std::string classe,std::string ip){return "???? " + classe + " " + ip;}
#define		RPL_TRACEOPERATOR		"204"
std::string	RPL_TRACEOPERATOR_MSG(std::string classe, std::string nick){return "Oper " + classe + " " + nick;}
#define		RPL_TRACEUSER			"205"
std::string	RPL_TRACEUSER_MSG(std::string classe, std::string nick){return "User " + classe + " " + nick;}
#define		RPL_TRACESERVER			"206"
std::string	RPL_TRACESERVER_MSG(std::string classe, std::string int1, std::string int2 , std::string server){return "Serv " + classe + " " + int1 + "S " + int2 + "C " + server;}
#define		RPL_TRACESERVICE		"207"
std::string	RPL_TRACESERVICE_MSG(std::string classe, /*std::string name,*/ std::string type, std::string activetype){return "Service " + classe + " " + type + " " + activetype;}
#define		RPL_TRACENEWTYPE		"208"
std::string	RPL_TRACENEWTYPE_MSG(std::string newtype, std::string clientname){return newtype + " 0 " + clientname;}
#define		RPL_TRACECLASS			"209"
std::string	RPL_TRACECLASS_MSG(std::string classe, std::string count){return "Class " + classe + " " + count;}
#define		RPL_TRACERECONNECT		"210" // unusued
#define		RPL_TRACELOG			"261"
std::string	RPL_TRACELOG_MSG(std::string logfile, std::string debuglevel){return "File " + logfile + " " + debuglevel;}
#define		RPL_TRACEEND			"262"
std::string	RPL_TRACEEND_MSG(std::string servername, std::string versiondedug){return servername + " " + versiondedug + " :End of TRACE";}
// report de statistique dans une connection

#define		RPL_STATSLINKINFO		"211"
std::string	RPL_STATSLINKINFO_MSG(std::string linkname, std::string sendq, std::string sentmessages, std::string skbytes, std::string receivedmessages, std::string rkbytes, std::string timeopen){return linkname + " " + sendq + " " + sentmessages + " " + skbytes + " " + receivedmessages + " " + rkbytes + " " + timeopen;}
// reporst statistics on commandse usage

#define		RPL_STATSCOMMANDS		"212"
std::string	RPL_STATSCOMMANDS_MSG(std::string command, std::string count, std::string bytescount, std::string remotecount){return command  + " "+ count + " " + bytescount + " " + remotecount;}
// reports the server uptime

#define		RPL_ENDOFSTATS			"219"
std::string	RPL_ENDOFSTATS_MSG(std::string statsletter){return statsletter + " :End of STATS report";}
#define		RPL_STARTUPTIME			"242"
std::string	RPL_STARTUPTIME_MSG(std::string time){return ":Server Up " + time;}
// Les hotes valables quand un user devient un operateur IRC

#define		RPL_STATOLINE			"243"
std::string	RPL_STATOLINE_MSG(std::string hostmask, std::string name){return "O " + hostmask + " * " + name;}
// To answer to a query about a client s own mode

#define		RPL_UMODEIS				"221"
std::string	RPL_UNODEIS_MSG(std::string usernodestring){return usernodestring;}
// SERVLIST

#define		RPL_SERVLIST			"234"
std::string	RPL_SERVLIST_MSG(std::string name, std::string server, std::string mask, std::string type, std::string hopcount, std::string info){return name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info;}
#define		RPL_SERVLISTEND			"235"
std::string	RPL_SERVLISTEND_MSG(std::string mask, std::string type){return mask  + " " + type + " :End of service listing";}
// LUSERS

#define		RPL_LUSERCLIENT			"251"
std::string	RPL_LUSERCLIENT_MSG(std::string int1 , std::string int2, std::string int3){return "There are " + int1 + " users and " + int2 + " services on " + int3 + " servers";}
#define		RPL_LUSEROP				"252"
std::string	RPL_LUSEROP_MSG(std::string int1){return int1 + " :operator (s) online";}
#define		RPL_LUSERUNKNOWN		"253"
std::string	RPL_LUSERUNKNOWN_MSG(std::string int1){return int1 + " :unknoen connections (s)";}
#define		RPL_LUSERCHANNELS		"254"
std::string	RPL_LUSERCHANNELS_MSG(std::string int1){return int1 + " :channels formed";}
#define		RPL_LUSERNE				"255"
std::string	RPL_LUSERNE_MSG(std::string int1, std::string int2){return "I have " + int1 + " clients and " + int2 + " servers";}

// ADMIN

#define		RPL_ADMINME				"256"
std::string	RPL_ADMINME_MSG(std::string server){return server + " :Administrative info";}
#define		RPL_ADMINLOC1			"257"
std::string	RPL_ADMINLOC1_MSG(std::string admininfo1){return ":"+admininfo1;}
#define		RPL_ADMINLOC2			"258"
std::string	RPL_ADMINLOC2_MSG(std::string admininfo2){return ":"+admininfo2;}
#define		RPL_ADMINEMAIL			"259"
std::string	RPL_ADMINEMAIL_MSG(std::string admininfo){return ":"+admininfo;}

// DROP A COMMAND without processing it

#define		RPL_TRYAGAIN			"263"
std::string	RPL_TRYAGAIN_MSG(std::string cmds){return cmds + " :Please wait a while and try again";}

// ERRORS REPLIES



#define		ERR_NOSUCHNICK			"401"
std::string	ERR_NOSUCHNICK_MSG(std::string nick){return nick + " :No such server";}
#define		ERR_NOSUCHSERVER		"402"
std::string	ERR_NOSUCHSERVER_MSG(std::string servername){return servername + " :No such server";}
#define		ERR_NOSUCHCHANNEL		"403"
std::string	ERR_NOSUCHCHANNEL_MSG(std::string channelname){return channelname + " :No suchchannel";}
#define		ERR_CANNOTSENDTOCHAN	"404"
std::string	ERR_CONNOTSENDTOCHAN_MSG(std::string channelname){return channelname + " :Cannot send to channel";}
#define		ERR_TOOMANYCHANNELS		"405"
std::string	ERR_TOOMANYCHANNELS_MSG(std::string channelname){return channelname + " :You have joined too many channel";}
#define		ERR_WASNOSUCHNICK		"406"
std::string	ERR_WASNOSUCHNICK_MSG(std::string nickname){return nickname + " :There was no such nickname";}
#define		ERR_TOOMANYTARGETS		"407"
std::string	ERR_TOOMANYTARGETS_MSG(std::string target, std::string abortmessages){return target + " :107 recipients. " + abortmessages;}
#define		ERR_NOSUCHSERVICE		"408"
std::string	ERR_NOSUCHSERVICE_MSG(std::string servicename){return servicename + " :No such service";}
#define		ERR_NOORIGIN			"409"
std::string	ERR_NOORIGIN_MSG(){return ":No origin specified";}
#define		ERR_NORECIPIENT			"411"
std::string	ERR_NORECIPIENT_MSG(std::string cmds){return "No recipient given (" + cmds + ")";}


// PRIVMSG

#define		ERR_NOTEXTTOSEND		"412"
std::string	ERR_NOTEXTTOSEND_MSG(){return ":No text to send";}
#define		ERR_NOTOPLEVEL			"413"
std::string	ERR_NOTOPLEVEL_MSG(std::string mask){return mask + " :No toplevel domain specified";}
#define		ERR_WILDTOPLEVEL		"414"
std::string	ERR_WILDTOPLEVEL_MSG(std::string mask){return mask + " :Wildcard in toplevel domain";}
#define		ERR_BADMASK				"415"
std::string	ERR_BADMASK_MSG(std::string mask){return mask + " :Bad Server/host mask";}
#define		ERR_UNKNOWCOMMAND		"421"
std::string	ERR_UNKNOWCOMMAND_MSG(std::string cmds){return cmds + " :Unknown command";}
#define		ERR_NOMOTD				"422"
std::string	ERR_NOMOTD_MSG(){return ":MOTD File is missing";}
#define		ERR_NOADMININFO			"423"
std::string	ERR_NOADMININFO_MSG(std::string server){return server + " :No administrative info available";}
#define		ERR_FILEERORR			"424"
std::string	ERR_FILEERORR_MSG(std::string fileop, std::string file){return ":File error doing " + fileop + " on " + file;}
#define		ERR_NONICKNAMEGIVEN		"431"
std::string	ERR_NONICKNAMEGIVEN_MSG(){return ":No nickname given";}
#define		ERR_ERRONEUSNICKNAME	"432"
std::string	ERR_ERRONEUSNICKNAME_MSG(std::string nick){return nick + " :Erroneous nickname";}
#define		ERR_NICKNAMEINUSE		"433"
std::string	ERR_NICKNAMEINUSE_MSG(std::string nick){return nick + " :Nickname is already in use";}
#define		ERR_NICKCOLLISION		"436"
std::string	ERR_NICKCOLLISION_MSG(std::string nick){return nick + " :Nickname collision KILL form <user>@<host>";}
#define		ERR_UNAVAILLABLERESOURCE	"437"
std::string	ERR_UNAVAILLABLERESOURCE_MSG(std::string nick){return nick +  " :Nick/chaannel is temporaryly unavailable";}
#define		ERR_USERNOTINCHANNEL		"441"
std::string	ERR_USERNOTINCHANNEL_MSF(std::string nick, std::string channel){return nick + " " + channel + " :They aren't on that channel";}
#define		ERR_NOTONCHANNEL			"442"
std::string	ERR_NOTONCHANNEL_MSG(std::string channel){return channel + " :You're not on that channel";}
#define		ERR_USERONCHANNEL			"443"
std::string	ERR_USERONCHANNEL_MSG(std::string nick, std::string channel){return nick + " " + channel + " :is already on channel";}
#define		ERR_NOLOGIN					"444"
std::string	ERR_NOLOGIN_MSG(std::string user){return user + " :User not logged in";}
#define		ERR_SUMMONDISABLED			"445"
std::string	ERR_SUMMONDISABLED_MSG(){return ":SUMMON has been disabled";}
#define		ERR_USERSDISABLED			"446"
std::string	ERR_USERSDISABLED_MSG(){return "USERS has been disabled";}
#define		ERR_NOTREGISTERED			"451"
std::string	ERR_NOTREGISTERED_MSG(){return ":You have nit registered";}
#define		ERR_NEEDMOREPARAMS			"461"
std::string	ERR_NEEDMOREPARAMS_MSG(std::string cmds){return cmds + " :Not enough parameters";}
#define		ERR_ALREADYREGISTRED		"462"
std::string	ERR_ALREADYREGISTRED_MSG(){return "Unauthorized command (already registered)";}
#define		ERR_NOPERMFORHOST			"463"
std::string	ERR_NOPERMFORHOST_MSG(){return "Your host isn't among the privileged";}
#define		ERR_PASSWDMISMATCH			"464"
std::string	ERR_PASSWDMISMATCH_MSG(){return ":Password incorrect";}
#define		ERR_YOUREBANNEDCREEP		"465"
std::string	ERR_YOUREBANNEDCREEP_MSG(){return "You are banned from this server";}
#define		ERR_YOUWILLBEBANNED			"466"
// a envoyer au server imform que l acces au server sera bientot denied
#define		ERR_KEYSET					"467"
std::string	ERR_KEYSET_MSG(std::string channel){return channel + " :Channel key already set";}
#define		ERR_CHANNELISFULL			"471"
std::string	ERR_CHANNELISFULL_MSG(std::string channel){return channel + " :Cannot join channel (+l)";}
#define		ERR_UNKNOWMODE				"472"
std::string	ERR_UNKNOWMODE_MSG(std::string char1){return char1 + " :is unknow mode char to me for channel (+i)";}
#define		ERR_INVITEONLYCHAN			"473"
std::string	ERR_INVITEONLYCHAN_MSG(std::string channel){return channel + " :Cannot join channel (+b)";}
#define		ERR_BADCHANNELKEY			"475"
std::string	ERR_BADCHANNELKEY_MSG(std::string channel){return channel + " :Cannot join channel (+k)";}
#define		ERR_BADCHANMASK				"476"
std::string	ERR_BADCHANMASK_MSG(std::string channel){return channel + " :Bad Channel Mask";}
#define		ERR_NOCHANMODES				"477"
std::string	ERR_NOCHANMODES_MSG(std::string channel){return channel + " :Channel doesn't support modes";}
#define		ERR_BANLISTFULL				"478"
std::string	ERR_BANLISTFULL_MSG(std::string channel, std::string char1){return channel + " " + char1 + " :Channel list is full";}
#define		ERR_NOPRIVILEGES			"481"
std::string	ERR_NOPRIVILEGES_MSG(){return "Permission Denied- You're not an IRC operator";}
#define		ERR_CHANOPRIVSNEEDED		"482"
std::string	ERR_CHANOPRIVSNEEDED_MSG(std::string channel){return channel + " :You're not channel operator";}
#define		ERR_CANTKILLSERVER			"483"
std::string	ERR_CANTKILLSERVER_MSG(){return ":You can't kill a server!";}
#define		ERR_RESTRICTED				"484"
std::string	ERR_RESTRICTED_MSG(){return "Your connection is restricted!";}
#define		ERR_UNIQOPPRIVSNEEDED		"485"
std::string	ERR_UNIQOPPRIVSNEEDED_MSG(){return ":You're not the original channel operator";}
#define		ERR_NOOPERHOST				"491"
std::string	ERR_NOOPERHOST_MSG(){return ":No 0-lines for your host";}
#define		ERR_UMODEUNKNOWNFLAG		"501"
std::string	ERR_UMODEUNKNOWNFLAG_MSG(){return ":Unknown MODE flag";}
#define		ERR_USERSDONTMATCH			"502"
std::string	ERR_USERSDONTMATCH_MSG(){return ":Cannot change mode for other users";}

#endif
