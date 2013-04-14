#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <unistd.h>

#include "karel.h"

/**
 *@brief Struktura Karel je vlastnej typu ROBOT ktora obsahuje premenne tykajuca sa karla.
 */
Robot karel;
/**
 * @brief Struktura world je vlasnej typu WORLD ktora obsahuje premenne tykajuce sa Karlovho sveta.
 */
World world;


/**
 * @brief Analyza sveta, inicializuje kniznice, priraduje hodnoty, nacitava retazce znakov, 
 */
void turnOn(void){
    
    char direction;
    
//    FILE* subor;
//    
//    subor = fopen("map.kw", "r");
//    
//    if (subor == NULL)
//        die("\nSubor sa nepodarilo otvorit.");

//    int position_wall_x, position_wall_y, number_beepers;
    
    scanf("%d %d %d %d %c %d\n", &world.width, &world.height, 
            &karel.x, &karel.y, &direction, &karel.beepers);
//    Flush buffer
//    while (getchar() != '\n');
    
    
    switch(direction){
        case 'E': 
            karel.direction = EAST;       
            break;
        case 'N': 
            karel.direction = NORTH;       
            break;
        case 'W': 
            karel.direction = WEST;      
            break;
        case 'S': 
            karel.direction = SOUTH;      
            break;        
    }
    
    if((world.width > MAX_WIDTH) || (world.height > MAX_HEIGHT))
        die("Rozmery sveta prevysuju pristupne hodnoty\n");
     
    
    if((world.width < 1) || (world.height < 1))
        die("Svet je prilis maly.\n");

    
    
    if ((karel.x > world.width) || (karel.y > world.height) || 
    karel.x < 1 || karel.y < 1)
        die("Umiestnenie karla je mimo aktualneho sveta\n");

    
        //Generate empty world    
    int i, j;
    for (i = 0; i < world.width; i++) {
        for (j = 0; j < world.height; j++) {
            world.data[i][j] = EMPTY;
        }
    }
    
    char c;
    int x, y, n;
    while (scanf("%c %d %d %d", &c, &x, &y, &n)) {

        switch (c) {
            case '.':
                // We found the end of a file, unable to break cycle with 
                // break inside switch, need to use goto
                goto endSwitch;
            case 'W':
                if (x < 1 || y < 1 || x > world.width || y > world.height)
                    die("Stena je mimo mapu.");
                else
                    world.data[x][y] = WALL;
                break;
            case 'B':
                if (n < 0)
                    die("Pocet beeprov musi byt nenulove cislo.");
                else
                    world.data[x][y] = n;
        }
//                
//        if (c == '.')
//            break;
//        
//        if (c != 'W')
//            die("Prvy znak nie je W.\n");           
//        
//        if (x < 1 || y < 1 || x > world.width || y > world.height)
//            die("Stena je mimo mapu.");
//
//        world.data[x][y] = WALL;
    }
    
    endSwitch:

    draw();
    
}

/**
 * Funkcia, pomocou ktorej sa vykresli svet.
 */
void draw (void){
    // Escape sequence for clear tenrminal and move cursor to 1,1
    printf("\033[2J\033[1;1H");
    
    printf("POSITION = [%d,%d]:%d - ", karel.x, karel.y, world.data[karel.x][karel.y]);
    switch(karel.direction) {
        case EAST:
            printf("East");
            break;
        case NORTH:
            printf("North");
            break;
        case WEST:
            printf("West");
            break;
        case SOUTH:
            printf("South");
            break;            
    }
    printf(", BEEP-BAG = %d\n", karel.beepers);
    int x, y;
    for (y = world.height; y >= 1; y--){
        for (x = 1; x <= world.width; x++){
            if (karel.x == x && karel.y == y) {
                switch (karel.direction) {
                    case EAST:
                        printf(">");
                        break;
                    case NORTH:
                        printf("^");
                        break;
                    case WEST:
                        printf("<");
                        break;
                    case SOUTH:
                        printf("v");
                        break;            
                }
            } 
            else {
                switch (world.data[x][y]) {
                    case EMPTY: printf ("."); break;
                    case WALL: printf ("#"); break;
                    default: printf ("*"); break;
            
                }
            }
            
        }
        printf ("\n");
    }
    usleep(USLEEP_TIME);
}

/**
 * @brief Funkcia pomocou ktorej vypiname Karla.
 */
void turnOff(void) {
    
}

/**
 * @brief Funkcia posunie karla o 1 poziciu dopredu posla smeru otocenia
 */
void movek(void) {
    if (frontIsClear()) {
        switch (karel.direction) {
            case EAST:
                karel.x += 1;
                break;
            case NORTH:
                karel.y += 1;
                break;
            case WEST:
                karel.x -= 1;
                break;
            case SOUTH:
                karel.y -= 1;
                break;            
        }    
    }
    else
        die("Karol nemoze ist vpred!");
    
    draw();
}

/**
 * @brief Funkcia otoci karla o 90° dolava
 */
void turnLeft() {
    karel.direction = (karel.direction + 90) % 360;
    draw();
}

/**
 * @brief Funckia zistuje ci je pred karlom prazdno alebo znacka.
 * @return vracia FALSE ak je pred karlom prekazka alebo koniec sveta. TRUE ak je pred karlom prazdno alebo znacka.
 */
int frontIsClear(void) {
    int clear = 0;
    
    switch (karel.direction) {
        case EAST:
            if (world.data[karel.x + 1][karel.y] != WALL && karel.x + 1 <= world.width)
                clear = 1;
            break;
        case NORTH:
            if (world.data[karel.x][karel.y + 1] != WALL && karel.y + 1 <= world.height)
                clear = 1;
            break;
        case WEST:
            if (world.data[karel.x - 1][karel.y] != WALL && karel.x - 1 > 0)
                clear = 1;
            break;
        case SOUTH:
            if (world.data[karel.x][karel.y - 1] != WALL && karel.y - 1 > 0)
                clear = 1;
            break;            
    }
    
    return clear;
}

/**
 * @brief Funkcia zistuje ci je pred karlom stena alebo koniec sveta.
 * @return Vracia TRUE ak je pred karlom stena alebo koniec sveta. FALSE ak je pred karlom prazdno alebo znacka.
 */
int frontIsBlocked(void) {
    return !frontIsClear();
}

/**
 * @brief Funckia zistuje ci je na lavo od karla prazdno alebo znacka.
 * @return vracia FALSE ak je na lavo od karla prekazka alebo koniec sveta. TRUE ak je na lavo od karla prazdno alebo znacka.
 */
int leftIsClear(void) {
    int clear = 0;
    
    switch (karel.direction) {
        case SOUTH:
            if (world.data[karel.x + 1][karel.y] != WALL && karel.x + 1 <= world.width)
                clear = 1;
            break;
        case EAST:
            if (world.data[karel.x][karel.y + 1] != WALL && karel.y + 1 <= world.height)
                clear = 1;
            break;
        case NORTH:
            if (world.data[karel.x - 1][karel.y] != WALL && karel.x - 1 > 0)
                clear = 1;
            break;
        case WEST:
            if (world.data[karel.x][karel.y - 1] != WALL && karel.y - 1 > 0)
                clear = 1;
            break;            
    }
    
    return clear;
}

/**
 * @brief Funkcia zistuje ci je na lavo od karla stena alebo koniec sveta.
 * @return Vracia TRUE ak je na  lavo od karla prekazka alebo koniec sveta. FALSE ak je na lavo od karla prazdno alebo znacka.
 */
int leftIsBlocked(void) {
    return !leftIsClear();
}

/**
 * @brief Funckia zistuje ci je na pravo od karla prazdno alebo znacka.
 * @return vracia FALSE ak je na pravo od karla prekazka alebo koniec sveta. TRUE ak je na pravo od karla prazdno alebo znacka.
 */
int rightIsClear(void) {
    int clear = 0;
    
    switch (karel.direction) {
        case NORTH:
            if (world.data[karel.x + 1][karel.y] != WALL && karel.x + 1 <= world.width)
                clear = 1;
            break;
        case WEST:
            if (world.data[karel.x][karel.y + 1] != WALL && karel.y + 1 <= world.height)
                clear = 1;
            break;
        case SOUTH:
            if (world.data[karel.x - 1][karel.y] != WALL && karel.x - 1 > 0)
                clear = 1;
            break;
        case EAST:
            if (world.data[karel.x][karel.y - 1] != WALL && karel.y - 1 > 0)
                clear = 1;
            break;            
    }
    
    return clear;
}

/**
 * @brief Funkcia zistuje ci je na pravo od karla stena alebo koniec sveta.
 * @return Vracia TRUE ak je na  pravo od karla prekazka alebo koniec sveta. FALSE ak je na pravo od karla prazdno alebo znacka.
 */
int rightIsBlocked(void) {
    return !rightIsClear();
}


void die(char *msg) {
    printf("%s\n\n", msg);
    exit(EXIT_FAILURE);
}

/**
 * @brief Funckia zistuje ci ma karol vo vaku nejaku znacku.
 * @return Vracia TRUE ak ma karel znacku vo vaku. FALSE ak nema.
 */
int beepersInBag(void) {
    return (karel.beepers > 0);
}

/**
 * @brief Funckia zistuje ci ma karol vo vaku nejaku znacku.
 * @return Vracia FALSE ak ma karel znacku vo vaku. TRUE ak nema.
 */
int noBeepersInBag(void) {
    return !beepersInBag();
}

/**
 * @brief Funckia zistuje ci sa na mieste kde karol stoji nachadza nejaka znacka.
 * @return Vracia TRUE ak je pod karlom znacka. FALSE ak nieje.
 */
int beepersPresent(void) {
    return (world.data[karel.x][karel.y] > 0);
}

/**
 * @brief Funckia zistuje ci sa na mieste kde karol stoji nachadza nejaka znacka.
 * @return Vracia FALSE ak je pod karlom znacka. TRUE ak nieje.
 */
int noBeepersPresent(void) {
    return !beepersPresent();
}

/**
 * @brief Funkcia pomocou ktorej karel polozi  pod seba znacku, ak nejaky ma vo vaku.
 */
void putBeeper(void) {
    if (beepersInBag()) {
        world.data[karel.x][karel.y]++;
        karel.beepers--;
    }
    else{
        die("V batohu nie su ziadne dalsie znacky.");
    }
    draw();
}

/**
 * @brief Funkcia pomocou ktore karel dvihne znacku, ak tam nejaka je.
 */
void pickBeeper(void) {
    if (beepersPresent()) {
        world.data[karel.x][karel.y]--;
        karel.beepers++;
    }
    else{
        die("Na danom mieste sa nenachadza znacka.");
    }
    draw();
}
