/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:05 by labintei          #+#    #+#             */
/*   Updated: 2022/03/23 17:53:08 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MODE est la commandes qu on recoit sous cette forme
//
// MODE nickname (droits d execution +i)
// Exemples MODE labintei +i

// Differents flags
//
// -a (away ????)
// -i (invisible)
// -w (wallops ???)
// -r (restricited user connection)
// -o (operator flag)
// -O (local operator flag)
// -s (marks a user for receipt of server notices)
//

// Rajouter une classe flag a User pour les differents flags ?? 

// Implementer de cette facon
//
// Client[USERS_MAX]

std::string	irc::Server::ModeUser(std::string nickname, std::string flags)
{
	if(!nickname)
		return()
}

// MODE(channel)
// changes les caracteristiqut d un channel
// <channel> *(("-" / "+") *<modes> *<modeparams>) (complique a faire)
//
// regarder channel protocol et channel management
//



