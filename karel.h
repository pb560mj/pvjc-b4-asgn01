/* 
 * File:   karel.h
 * Author: Patrik Blahuta
 *
 * Created on April 11, 2013, 9:50 PM
 */

#ifndef ZDV_H
#define	ZDV_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/**
 * Maximalne sirka sveta
 */
#define MAX_WIDTH 30
 /**
  *Maximalna vyska sveta
  */
#define MAX_HEIGHT 30
    /**
     * @def EMPTY 
     * @brief Empty place
     */
#define EMPTY 0
    /**
     * @def WALL
     * @brief WALL
     */
#define WALL -1
    
#define USLEEP_TIME 1000 * 1000 * 1


void turnOn(void);
void draw(void);
void turnOff(void);
void movek(void);
void turnLeft();
void putBeeper(void);
void pickBeeper(void);
int frontIsClear(void);
int frontIsBlocked(void);
int leftIsClear(void);
int leftIsBlocked(void);
int rightIsClear(void);
int rightIsBlocked(void);
int beepersInBag(void);
int noBeepersInBag(void);
int beepersPresent(void);
int noBeepersPresent(void);

void die(char *msg);

typedef enum {
    EAST = 0,
    NORTH = 90,
    WEST = 180,
    SOUTH = 270
} Direction;

/**
 * @struct Robot
 * @brief Karel structure
 */
typedef struct {
    /**
     * @var x
     * @ brief X-ova suradnica Karla
     */
    int x;
    /**
     * @var y
     * @brief Y-ova suradnica Karla
     */
    int y;
    /**
     * @var beepers
     * @brief Pocet znaciek ktore ma karel
     */
    int beepers;
    Direction direction;
} Robot;

/**
 * @struct world
 * @brief Struktura sveta
 */
typedef struct {
   /**
    * @var height
    * @brief Vyska sveta
    */
    int height;
    /**
     * @var width
     * @brief Sirka sveta
     */
    int width;
    /**
     * @var data
     * @brief Dvojrozmerna pole v ktorom je ulozeny svet.
     */
    int data[MAX_WIDTH + 1][MAX_HEIGHT + 1];
} World;



#ifdef	__cplusplus
}
#endif

#endif	/* ZDV_H */

