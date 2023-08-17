#include "media/windows10.h"
//#define COLOR "\e[1;36m"
#define COLOR ""


#define CONFIG \
{ \
   /* name                 function                 cached */\
    { "Isira@"       ,     get_title,                false }, \
    { "\b"           ,     get_bar,                  false }, \
    { "Name:        ",     get_name,                 false }, \
    { "Manufacturer:",     get_manufacturer,          true }, \
    { "Model:       ",     get_model,                 true }, \
    SPACER \
    { "CPU:         ",     get_cpu,                  true  }, \
    { "GPU:         ",     get_gpu1,                 true  }, \
    { "Memory:      ",     get_memory,               false }, \
    SPACER     \
    { "OS:          ",     get_os,                   true  }, \
    { "Battery:     ",     get_battery_percentage,   false }, \
    { "Packages:    ",     get_packages_pacman,      false }, \
    { "Shell:       ",     get_shell,                false }, \
    { "Resolution:  ",     get_resolution,           false }, \
    { "Terminal:    ",     get_terminal,             false }, \
    { "             ",     get_colors1,              false }, \
    { "             ",     get_colors2,              false }, \
}

#define CPU_CONFIG \
{ \
    REMOVE("(R)"), \
    REMOVE("(TM)"), \
    REMOVE("Dual-Core"), \
    REMOVE("Quad-Core"), \
    REMOVE("Six-Core"), \
    REMOVE("Eight-Core"), \
    REMOVE("Core"), \
    REMOVE("CPU"),  \
    REMOVE("11th Gen"),  \
    REMOVE("10th Gen"), \
    REMOVE("9th Gen"), \
    REMOVE("8th Gen"),\
    REMOVE("7th Gen"), \
    REMOVE("5th Gen"),\
    REMOVE("4th Gen"), \
}

#define GPU_CONFIG \
{ \
    REMOVE("Corporation"), \
}
