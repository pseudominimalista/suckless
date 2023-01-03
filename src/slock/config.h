/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#1e1e2e",     /* after initialization */
	[INPUT] =  "#a6e3a1",   /* during input */
	[FAILED] = "#f38ba8",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
/* default message */
static const char * message = "Suckless Desktop Environment\nDigite a senha de login.";

/* text color */
static const char * text_color = "#f9e2af";

/* text size (must be a valid size) */
//static const char * font_name = "-misc-fixed-medium-r-normal-ko-18-120-100-100-c-180-iso10646-1";*/
static const char * font_name = "9x15";
