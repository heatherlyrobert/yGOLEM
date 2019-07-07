/*============================[[    beg-code    ]]============================*/
#include    "yGOLEM.h"
#include    "yGOLEM_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
typedef     struct      stat        tSTAT;
typedef     struct      termios     tTERMIOS;
static      tTERMIOS    s_oldtio;
static      tTERMIOS    s_newtio;



/*====================------------------------------------====================*/
/*===----                         communication                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMM____________________o (void) {;}

char       /* ---- : open a communication channel to the robot ---------------*/
yGOLEM_device           (char *a_dev)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_YGOLEM   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGOLEM   yLOG_point   ("a_dev"     , a_dev);
   --rce;  if (a_dev == NULL) {
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGOLEM   yLOG_info    ("a_dev"     , a_dev);
   /*---(check on file)------------------*/
   rc = stat (a_dev, &s);
   DEBUG_YGOLEM   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGOLEM   yLOG_note    ("file exists");
   /*---(check type)---------------------*/
   DEBUG_YGOLEM   yLOG_value   ("dir"       , S_ISDIR (s.st_mode));
   DEBUG_YGOLEM   yLOG_value   ("link"      , S_ISLNK (s.st_mode));
   DEBUG_YGOLEM   yLOG_value   ("reg"       , S_ISREG (s.st_mode));
   DEBUG_YGOLEM   yLOG_value   ("char"      , S_ISCHR (s.st_mode));
   DEBUG_YGOLEM   yLOG_value   ("block"     , S_ISBLK (s.st_mode));
   if (!S_ISCHR (s.st_mode)) {
      DEBUG_YGOLEM   yLOG_note    ("not a char device");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGOLEM   yLOG_note    ("is a char device");
   /*---(save)---------------------------*/
   strlcpy (myGOLEM.device, a_dev, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YGOLEM   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : open a communication channel to the robot ---------------*/
yGOLEM_open             (void)
{
   /*---(notes)--------------------------*/
   /*
    *   O_RDRW    : both read and write
    *   O_NOCTTY  : don't be the controlling terminal for the port (no sigs)
    *   O_NODELAY : don't wait for the other end of the port to be ready
    *
    */
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         fd          =    0;       /* file descriptor                          */
   /*---(header)-------------------------*/
   DEBUG_YGOLEM   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGOLEM   yLOG_char    ("ready"     , myGOLEM.ready);
   --rce;  if (myGOLEM.ready != 'y') {
      DEBUG_YGOLEM   yLOG_note    ("must run yGOLEM_init before use");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGOLEM   yLOG_info    ("device"    , myGOLEM.device);
   /*---(open)---------------------------*/
   fd = open (myGOLEM.device, O_RDWR | O_NOCTTY | O_NONBLOCK);
   DEBUG_YGOLEM   yLOG_value   ("fd"        , fd);
   --rce;  if (fd == -1) {
      fprintf(stderr, "can not open serial port %s\n", myGOLEM.device);
      DEBUG_YGOLEM   yLOG_note    ("can not open serial port");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   fcntl (fd, F_SETFL, 0);
   /*---(get current term settings)------*/
   tcgetattr(fd, &s_oldtio);
   /*---(prepare new one)----------------*/
   bzero(&s_newtio, sizeof (tTERMIOS));
   /*> s_newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;                               <*/
   s_newtio.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
   cfsetispeed(&s_newtio, B115200);
   /*> cfsetispeed(&s_newtio, B2400);                                                   <*/
   cfsetospeed(&s_newtio, B115200);
   /*> cfsetospeed(&s_newtio, B2400);                                                   <*/
   /*> s_newtio.c_cflag |= (CLOCAL | CREAD);                                            <* 
    *> s_newtio.c_cflag &= ~CSIZE;                                                      <* 
    *> s_newtio.c_cflag &= ~PARENB;                                                     <* 
    *> s_newtio.c_cflag &= ~CSTOPB;                                                     <* 
    *> s_newtio.c_cflag |= CS8;                                                         <*/
   s_newtio.c_iflag  = IGNPAR  | ICRNL   ;
   s_newtio.c_oflag  = 0       ;
   s_newtio.c_lflag  = ICANON  ;
   tcflush   (fd, TCIFLUSH);
   tcsetattr (fd, TCSANOW, &s_newtio);
   /*---(save)---------------------------*/
   myGOLEM.port = fd;
   DEBUG_YGOLEM   yLOG_value   ("port"      , myGOLEM.port);
   /*---(complete)-----------------------*/
   DEBUG_YGOLEM   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : close the communcation channel to the robot -------------*/
yGOLEM_close            (void)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         rc          =    0;       /* generic return code    */
   /*---(header)-------------------------*/
   DEBUG_YGOLEM   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGOLEM   yLOG_char    ("ready"     , myGOLEM.ready);
   --rce;  if (myGOLEM.ready != 'y') {
      DEBUG_YGOLEM   yLOG_note    ("must run yGOLEM_init before use");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myGOLEM.port < 0) {
      DEBUG_YGOLEM   yLOG_note    ("serial port is not open");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   rc = close (myGOLEM.port);
   DEBUG_YGOLEM   yLOG_value   ("close"     , rc);
   if (rc <  0) {
      DEBUG_YGOLEM   yLOG_note    ("could not close the serial port");
      DEBUG_YGOLEM   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_YGOLEM   yLOG_note    ("serial port successfully closed");
   /*---(set terminal back)--------------*/
   tcsetattr (myGOLEM.port, TCSANOW, &s_oldtio);
   /*---(complete)-----------------------*/
   DEBUG_YGOLEM   yLOG_exit    (__FUNCTION__);
   return 0;
}




/*============================[[    end-code    ]]============================*/
