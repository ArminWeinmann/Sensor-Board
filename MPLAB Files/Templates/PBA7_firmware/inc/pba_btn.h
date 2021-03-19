/**
 * @defgroup 		BTN
 * @brief			Stellt Funktionen im Umgang mit Tastern zur Verf�gung.
 * @{
 *******************************************************************************
 * @file            pba_btn.h
 * @brief           Stellt Funktionen im Umgang mit Tastern zur Verf�gung.
 * @author          ICT Berufsbildungscenter AG
 *******************************************************************************
 *
 * @copyright
 * @{
 *
 * Diese Software kann unter den Bedingungen der MIT-Lizenz verwendet werden.
 *
 * Copyright &copy; 2021 ICT Berufsbildungscenter AG
 *
 * #####MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @}
 */

#ifndef PBA_BTN_H
#define	PBA_BTN_H

/***Includes*******************************************************************/

#include "../inc/pba_config.h"

/***Defines********************************************************************/

/**
 * @brief Port mit Tastern, die �berpr�ft werden.
 */
#define TASTER_PORT     TASTER      //< Port mit den Tastern.

/***Funktionsprototypen********************************************************/
bool BTN_GetPosEdge(uint8_t button);
bool BTN_GetNegEdge(uint8_t button);

#endif	/* PBA_BTN_H */

