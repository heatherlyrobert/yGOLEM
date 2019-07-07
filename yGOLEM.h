/*============================[[    beg-code    ]]============================*/
#ifndef   YGOLEM_HGUARD
#define   YGOLEM_HGUARD       loaded



/*--------- ----------- ----------- ----------- ------------------------------*/
char*       yGOLEM_version          (void);
char        yGOLEM_device           (char *a_dev);
char        yGOLEM_init             (void);

/*--------- ----------- ----------- ----------- ------------------------------*/
char        yGOLEM_toggle           (char *a_option);

/*--------- ----------- ----------- ----------- ------------------------------*/
char        yGOLEM_leg              (char a_leg, float a_femu, float a_pate, float a_tibi, float a_sec);



#endif
/*============================[[    end-code    ]]============================*/
