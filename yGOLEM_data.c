/*============================[[    beg-code    ]]============================*/
#include    "yGOLEM.h"
#include    "yGOLEM_priv.h"



typedef     struct cSERVO   tSERVO;
struct cSERVO {
   /*---(key info)----------*/
   char        leg;
   char        seg;
   char        servo;
   char        ykine;
   /*---(descriptive)-------*/
   char        leg_name    [LEN_LABEL];
   char        leg_short   [LEN_LABEL];
   char        seg_name    [LEN_LABEL];
   char        seg_short   [LEN_LABEL];
   /*---(setup data)--------*/
   double      zero;
   float       dmin;
   float       dattn;
   float       dmax;
   int         min;
   int         attn;
   int         max;
   /*---(dynamic adj)-------*/
   char        flip;
   int         adj_min;
   int         adj_attn;
   int         adj_max;
   char        type;
   int         a_fzero;
   int         a_free     [19];
   int         a_lzero;
   int         a_load     [19];
   /*---(descriptive)-------*/
   char        min_dir    [LEN_LABEL];
   int         curr;
   int         a, b, c;
   float       pct;
   int         adj;
   /*---(done)--------------*/
};

static      tSERVO      s_servo_data   [YKINE_MAX_SERVO] = {
   /* ===header======================================= ===key numbers==================================  ===free adjustments========================================================================================================   ===loaded adjustments============================================================================================   ========= */
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_RR, YKINE_FEMU,  15 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  -50,    0,   25, '3',    -10,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_RR, YKINE_PATE,   1 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  -25,  -25,  -25, '3',      0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    -50,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_RR, YKINE_TIBI,   2 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1, -225, -225, -225, '3',   -250,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_RM, YKINE_FEMU,   4 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  -25,    0,   75, '3',      0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_RM, YKINE_PATE,   5 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,   75,   75,   35, '3',     60,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    -20,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_RM, YKINE_TIBI,   6 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1, -125, -150, -150, '3',   -180,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_RF, YKINE_FEMU,   8 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,   25,   25,  100, '3',     20,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_RF, YKINE_PATE,   9 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,   50,   50,   25, '3',     60,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    -30,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_RF, YKINE_TIBI,  10 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1,   50,   50,   75, '3',     30,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_LF, YKINE_FEMU,  24 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  -50,    0,    0, '3',      0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_LF, YKINE_PATE,  25 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1,  250,  250,  250, '3',    210,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,     50,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_LF, YKINE_TIBI,  26 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  -25,   25,    0, '3',     10,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_LM, YKINE_FEMU,  20 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,    0,  -50,  -50, '3',    -20,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_LM, YKINE_PATE,  21 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1,  250,  200,  250, '3',    200,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,     80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_LM, YKINE_TIBI,  22 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,  225,  250,  225, '3',    230,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  YKINE_LR, YKINE_FEMU,  16 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,   25,   50,   50, '3',     30,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "cclock" ,  0  },
   {  YKINE_LR, YKINE_PATE,  17 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,   1,   50,  -25,  -25, '3',    -30,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,     80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "up"     ,  0  },
   {  YKINE_LR, YKINE_TIBI,  18 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1, -225, -175, -175, '3',   -170,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   "out"    ,  0  },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits------------ flip --min -attn --max type  -base--   --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   base- --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24-   -min-dir- */
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0, 0, 0, 0,  -1,    0,    0,    0, '-',      0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   ""       ,  0  },
   /*---(done)--------------*/
};
static int            s_nservo     = 0;

char
ygolem__data_init       (void)
{
   int         i           = 0;
   double      x_attn      = 0.0;
   double      x_value     = 0.0;
   char        x_name      [LEN_LABEL];
   s_nservo = 0;
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (s_servo_data [i].leg <  0)   break;
      strlcpy (s_servo_data [i].leg_name , yKINE_legfull (s_servo_data [i].leg), LEN_LABEL);
      strlcpy (s_servo_data [i].leg_short, yKINE_legcaps (s_servo_data [i].leg), LEN_LABEL);
      strlcpy (s_servo_data [i].seg_name , yKINE_segfull (s_servo_data [i].seg), LEN_LABEL);
      strlcpy (s_servo_data [i].seg_short, yKINE_segfour (s_servo_data [i].seg), LEN_LABEL);
      s_servo_data [i].dattn  = yKINE_segattn (s_servo_data [i].seg);
      s_servo_data [i].zero   = s_servo_data [i].dattn;
      s_servo_data [i].attn   = 1500;
      s_servo_data [i].dmin   = yKINE_segmin  (s_servo_data [i].seg);
      x_value                 = s_servo_data [i].dattn - s_servo_data [i].dmin;
      x_value                *= 10.0;
      s_servo_data [i].min    = 1500 - x_value;
      s_servo_data [i].dmax   = yKINE_segmax  (s_servo_data [i].seg);
      x_value                 = s_servo_data [i].dmax - s_servo_data [i].dattn;
      x_value                *= 10.0;
      s_servo_data [i].max    = 1500 + x_value;
      sprintf (x_name, "%s.%s", s_servo_data [i].leg_short, s_servo_data [i].seg_short);
      s_servo_data [i].ykine = yKINE_servo (x_name);
      ++s_nservo;
   }
   return 0;
}

char
ygolem__data_find       (char a_leg, char a_seg)
{
   int         i           = 0;
   for (i = 0; i < s_nservo; ++i) {
      if (s_servo_data [i].leg < 0)       continue;
      if (s_servo_data [i].leg != a_leg)  continue;
      if (s_servo_data [i].seg != a_seg)  continue;
      return i;
   }
   return -1;
}

char
ygolem__joint           (char a_leg, char a_seg, float a_deg, float a_sec)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_value     =    0;
   int         x_msec      =    0;
   char        n           =    0;
   char        x_buf       [1000]   = "";
   char        x_flip      =    0;
   float       x_min, x_max;
   int         a           =    0;
   int         x_fbase, x_lbase;
   float       x_pct       =    0;
   int         b, c;
   int         x_adj;
   /*---(defense)------------------------*/
   n = ygolem__data_find (a_leg, a_seg);
   --rce;  if (n < 0)  return rce;
   /*---(range check)--------------------*/
   x_min    = s_servo_data [n].dmin;
   x_max    = s_servo_data [n].dmax;
   if (a_deg < x_min)  a_deg = x_min;
   if (a_deg > x_max)  a_deg = x_max;
   /*---(convert)------------------------*/
   x_msec   = a_sec * 1000;
   x_flip   = s_servo_data [n].flip;
   x_value  = 1500 + (-a_deg * 10.0);
   x_value  = (1500 + (x_value - 1500) * x_flip);
   /*---(adjust)-------------------------*/
   x_fbase   = s_servo_data [n].a_fzero;
   x_lbase   = s_servo_data [n].a_lzero;
   a        = trunc (x_value / 100);
   b        = s_servo_data [n].a_free [a - 6] + s_servo_data [n].a_load [a - 6];
   c        = s_servo_data [n].a_free [a - 5] + s_servo_data [n].a_load [a - 5];
   if (x_value == a * 100)   x_adj = a;
   x_pct    = (x_value - (a * 100)) / 100.0;
   x_adj    = (b * (1.0 - x_pct) + (c * x_pct));
   x_value += x_fbase + x_lbase + x_adj;
   /*---(write)--------------------------*/
   snprintf (x_buf, 1000, "#%d P%d T%d\r", s_servo_data [n].servo, x_value, x_msec);
   /*> printf ("%s\n\n", x_buf);                                                      <*/
   write  (myGOLEM.port, x_buf, strlen (x_buf));
   /*---(save)---------------------------*/
   s_servo_data [n].curr = x_value;
   s_servo_data [n].a    = a;
   s_servo_data [n].b    = b;
   s_servo_data [n].c    = c;
   s_servo_data [n].pct  = x_pct;
   s_servo_data [n].adj  = x_adj;
   /*---(complete)-----------------------*/
   return 0;
}

char
yGOLEM_leg              (char a_leg, float a_femu, float a_pate, float a_tibi, float a_sec)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGOLEM   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGOLEM   yLOG_char    ("ready"     , myGOLEM.ready);
   --rce;  if (myGOLEM.ready != 'y') {
      DEBUG_YGOLEM   yLOG_note    ("must run yGOLEM_init before use");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(run)----------------------------*/
   rc = ygolem__joint  (a_leg, YKINE_FEMU, a_femu, a_sec);
   DEBUG_YGOLEM   yLOG_value   ("femu"      , rc);
   if (rc < 0) {
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   rc = ygolem__joint  (a_leg, YKINE_PATE, a_pate, a_sec);
   DEBUG_YGOLEM   yLOG_value   ("pate"      , rc);
   if (rc < 0) {
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   rc = ygolem__joint  (a_leg, YKINE_TIBI, a_tibi, a_sec);
   DEBUG_YGOLEM   yLOG_value   ("tibi"      , rc);
   if (rc < 0) {
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGOLEM   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================[[    end-code    ]]============================*/
