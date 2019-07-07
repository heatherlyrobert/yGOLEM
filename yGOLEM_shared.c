/*============================[[    beg-code    ]]============================*/
#include    "yGOLEM.h"
#include    "yGOLEM_priv.h"


/*--------- ----------- ----------- ----------- ------------------------------*/
tACCESSOR   myGOLEM;
static      char        yGOLEM_ver  [200] = "";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*        /*-> library versioning -----------------[ leaf   [gs.420.012.00]*/ /*-[00.0000.000.!]-*/ /*-[--.---.---.--]-*/
yGOLEM_version          (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yGOLEM_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yGOLEM_ver;
}

char         /*-> initialize library for use ---------[ shoot  [gz.321.011.02]*/ /*-[00.0000.000.!]-*/ /*-[--.---.---.--]-*/
yGOLEM_init             (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGOLEM   yLOG_enter   (__FUNCTION__);
   rc  = ygolem__data_init ();
   myGOLEM.port      = -1;
   rc  = yGOLEM_device (DEV_SPIDER);
   myGOLEM.ready = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YGOLEM   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> yVIKEYS interface for yGOLEM -------[ ------ [ge.320.114.32]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
yGOLEM_toggle           (char *a_option)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   --rce;  if (a_option == NULL)  return rce;
   if (strcmp ("on"  , a_option) == 0) {
      return yGOLEM_open ();
   } else if (strcmp ("off" , a_option) == 0) {
      return yGOLEM_close ();
   }
   return --rce;
}






/*============================[[    end-code    ]]============================*/
