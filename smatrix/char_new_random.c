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

/*	The purpose of this function is to select a random character to be the	*/
/*	Next value of a drop that has been moved forward by "advance()". Right	*/
/*	now this function can only print the Roman alphabet, but we are in the	*/
/*	process of adding support for Cyrillic, Kanji, and Kana.				*/

char
char_new_random()
{
	/*	ASCII range is 33-126 inclusive	*/
	return ( ( rand() % (94) ) + 33 ) ;
}

