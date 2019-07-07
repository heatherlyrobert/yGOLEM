/*============================[[    beg-code    ]]============================*/
#include    "yGOLEM.h"



/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

#define     P_FOCUS     "RO (robotics)"
#define     P_NICHE     "hx (hexapoda)"
#define     P_PURPOSE   "wickedly accurate and useful hexapod visualization and simulation"

#define     P_NAMESAKE  "talos-automoton"
#define     P_HERITAGE  "living statue made by hephaestus to protect the island of crete"
#define     P_IMAGERY   "giant man made of bronze who hurled rocks at pirates and invaders"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "moderate    (less than 5,000 lines of code)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2017-01"
#define     P_DEPENDS   "none"

#define     P_VERMAJOR  "0.--, getting ready for the big time"
#define     P_VERMINOR  "0.6-, tying into arachne for real-time control"
#define     P_VERNUM    "0.6a"
#define     P_VERTXT    "updated femu flipping so that it drives correctly"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"



/*===[[ library headers -- standard ]]========================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <stdio.h>               /* CLIBC   standard input/output          */
#include    <stdlib.h>              /* CLIBC   standard general purpose       */
#include    <string.h>              /* CLIBC   standard string handling       */

#include    <termios.h>           /* clibc standard terminal control          */
#include    <unistd.h>            /* clibc standard unix interface            */
#include    <sys/types.h>         /* CLIBC types                              */
#include    <sys/stat.h>          /* CLIBC status checking                    */
#include    <fcntl.h>             /* clibc standard file control              */


/*===[[ library headers -- heatherly ]]=======================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <yURG.h>                /* CUSTOM heatherly urgent processing     */
#include    <yLOG.h>                /* CUSTOM heatherly program logging       */
#include    <ySTR.h>                /* CUSTOM heatherly string handling       */
#include    <yKINE.h>               /* CUSTOM heatherly kinematics            */



/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define   YGOLEM_VER_NUM      "0.6a"
#define   YGOLEM_VER_TXT      "updated femu flipping so that it drives correctly from arachne"



/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20



extern char yGOLEM__unit_answer [ LEN_STR  ];



#define     DEV_SPIDER   "/dev/ttyUSB0"
/*> #define     DEV_SPIDER   "/dev/eva"                                               <*/
typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(yLOG/yURG)---------*/
   char        logger;                          /* yURG debugging handle      */
   char        ready;                           /* library initialized        */
   /*---(datacomm)----------*/
   char        device      [LEN_RECD];
   int         port;
};
extern   tACCESSOR  myGOLEM;



/*--------- ----------- ----------- ----------- ------------------------------*/
char        ygolem__data_init       (void);


/*============================[[    end-code    ]]============================*/
