/**
 * @file main.c
 * @brief Karel the robot library
 * 
 * @author Patrik Blahuta
 * @date 11/4/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include "karel.h"

/**
*@brief Hlavna funkcia
*/

int main(void) {
    turnOn();

//    clears();
//    printf("%d\n\n", frontIsClear());
    turnLeft();
    turnLeft();    
//    draw();
    
    
    return EXIT_SUCCESS;
}

/**
 * @mainpage Task no.1: Karel Game
 * 
 * @section s_statement Statement of the library
 * Create a C library for creating programs in a programming language Karel.
 * 
 * @section s_define Define the assignment
 * Restrictive conditions for the solution:
 * 
 *      @subsection ss_ww Maximal width of Karel world.
 *      @see MAX_WIDTH
 * 
 *      @subsection ss_wh Maximal height of Karel world.
 *      @see MAX_HEIGHT
 * 
 * @section s_suggestion Suggestion of the problem solution
 *      
 *      @subsection ss_structure Used data structures
 *      @see World
 *      @see Robot
 * 
 *      @subsection ss_type Used data types
 *      @see World
 *      @see Robot
 * 
 * @section s_use Use of the program
 *      Use of the program are detailed written in closure.
 * 
 *      @subsection ss_translation Translation of the program
 *      Program is translated by translator of C language
 * 
 * @section s_conclusion Conclusion
 *      
 *      @subsection ss_evaluation Evaluation of solutions
 *      Library contain implementation of all functions which are on API page.
 *      Function turnOn() read whole karel world to two dimensional array and during translation it shouldn't came to any errors or warning.
 * 
 *      @subsection ss_oportunities Opportunities of use and expansion
 *      Karel can be use for teaching and demonstration C language.
 *      Program can be expand for example by eliminating limiting terms by automatic adjusting.
 * 
 * @section s_reference Reference documentation 
 * Documentation source code is create with automated tool Doxygen.
 * @see main.c enclosure 
 * 
 */

