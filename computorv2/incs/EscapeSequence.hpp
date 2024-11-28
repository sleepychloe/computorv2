/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EscapeSequence.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:54:13 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/29 00:11:20 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCAPE_SEQUENCE_HPP
#define ESCAPE_SEQUENCE_HPP

/* Arrow Keys */
#define ESCAPE_UP_ARROW		"\033[A"
#define ESCAPE_DOWN_ARROW	"\033[B"
#define ESCAPE_RIGHT_ARROW	"\033[C"
#define ESCAPE_LEFT_ARROW	"\033[D"

/* Function Keys */
#define ESCAPE_F1		"\033OP"
#define ESCAPE_F2		"\033OQ"
#define ESCAPE_F3		"\033OR"
#define ESCAPE_F4		"\033OS"
#define ESCAPE_F5		"\033[15~"
#define ESCAPE_F6		"\033[17~"
#define ESCAPE_F7		"\033[18~"
#define ESCAPE_F8		"\033[19~"
#define ESCAPE_F9		"\033[20~"
#define ESCAPE_F10		"\033[21~"
#define ESCAPE_F11		"\033[25~"
#define ESCAPE_F12		"\033[24~"

/* Navigation Keys */
#define ESCAPE_INSERT		"\033[2~"
#define ESCAPE_DELETE		"\033[3~"
#define ESCAPE_PAGE_UP		"\033[5~"
#define ESCAPE_PAGE_DOWN	"\033[6~"
#define ESCAPE_HOME		"\033[H"
#define ESCAPE_END		"\033[F"

/* Alt (Meta) Keys */
#define ESCAPE_ALT_A		"\033a"
#define ESCAPE_ALT_B		"\033b"
#define ESCAPE_ALT_C		"\033c"
#define ESCAPE_ALT_D		"\033d"

#endif
