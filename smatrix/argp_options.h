/*  This file is part of smatrix.                                           */
/*                                                                          */
/*  Smatrix is free software: you can redistribute it and/or modify it      */
/*  under the terms of the GNU General Public License as published by       */
/*  the Free Software Foundation, either version 2 of the License, or       */
/*  (at your option) any later version.                                     */
/*                                                                          */
/*  Smatrix is distributed in the hope that it will be useful, but WITHOUT  */
/*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY      */
/*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public         */
/*  License for more details.                                               */
/*                                                                          */
/*  You should have received a copy of the GNU General Public License       */
/*  along with smatrix. If not, see <https://www.gnu.org/licenses/>.        */

static struct
argp_option
options[] = 
{
	{"Cyrillic",	'C', 0,			0,		"Print russian Characters"		},
	{"hiragana",	'H', 0,			0,		"Print Japanese Hiragana"		},
	{"Kanji",		'K', 0,			0,		"Print Japanese Kanji"			},
	{"katakana",	'k', 0,			0,		"Print Japanese Katakana"		},
	{"Schizo",		'z', 0,			0,		"Prints cryptic messages"		},
	{"MaxVelocity",	'V', "VMAX",	0,		"Velocity of fastest drop"		},
	{"MinVelocity",	'v', "VMIN",	0,		"Velocity of slowest drop"		},
	{ 0 }
};

