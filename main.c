#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <conio.h>

#include "config.h"
#include "main.h"

#define COUNT(x) (int)(sizeof x / sizeof *x)

#define BUF_SIZE 150



struct conf {
    char *label;
    char *(*function)();
    bool cached;
} config[] = CONFIG;

struct {
    char *substring;
    char *repl_str;
    size_t length;
    size_t repl_len;
} cpu_config[] = CPU_CONFIG, gpu_config[] = GPU_CONFIG;

int title_length, status;

void remove_newline(char *s) {
    while (*s != '\0' && *s != '\n')
        s++;
    *s = '\0';
}


void truncate_spaces(char *str) {
    /*
     Cleans up repeated spaces in a string
     Trim spaces at the front of a string
    */
     int src = 0, dst = 0;
    while(*(str + dst) == ' ') dst++;

    while(*(str + dst) != '\0') {
        *(str + src) = *(str + dst);
        if(*(str + (dst++)) == ' ')
            while(*(str + dst) == ' ') dst++;
        src++;
    }
    *(str + src) = '\0';
}

void remove_substring(char *str, const char* substring, size_t len) {
/*
 * Removes the first len characters of substring from str
 * Assumes that strlen(substring) >= len
 * Returns index where substring was found, or -1 if substring isn't found
 */
    /* shift over the rest of the string to remove substring */
    char *sub = strstr(str, substring);
    if(sub == NULL) return;

    int i = 0;
    do *(sub+i) = *(sub+i+len);
    while(*(sub+(++i)) != '\0');
}

/*
 * Replaces the first sub_len characters of sub_str from str
 * with the first repl_len characters of repl_str
 */
void replace_substring(char *str, const char *sub_str, const char *repl_str, size_t sub_len, size_t repl_len) {
    char buffer[BUF_SIZE / 2];
    char *start = strstr(str, sub_str);
    if (start == NULL) return; // substring not found

    /* check if we have enough space for new substring */
    if (strlen(str) - sub_len + repl_len >= BUF_SIZE / 2) {
        status = -1;
    }

    strcpy(buffer, start + sub_len);
    strncpy(start, repl_str, repl_len);
    strcpy(start + repl_len, buffer);
}

char *cmd_return(char command[]){
    int size = 1;
    FILE *in=NULL;
    char list[size][256];

    in = popen(command, "r");
    fgets(list[0], 255,in);
    for (int i = 0; i < size; i++) {
        fgets(list[i], 255, in);
    }
    char *p1 = malloc(BUF_SIZE);
    snprintf(p1, BUF_SIZE, "%s", list[0]);
    remove_newline(p1);
//    truncate_spaces(p1);
    return p1;
}


char *get_title(){
    char *hostname, *name;
    hostname = cmd_return("hostname");
    name = cmd_return("wmic ComputerSystem get Name");
    title_length = strlen(hostname)+ strlen(name) - 2;
    return hostname;
}



char *get_bar(){
    char *bar = malloc(BUF_SIZE);
    char *s = bar;
    for(int i = 0; i < title_length; i++) *(s++) = '=';
    *s = '\0';
//    printf("%s", bar);
    return bar;
}


char *get_name(){
    return cmd_return("wmic ComputerSystem get Name");
}


char *get_manufacturer(){
    return cmd_return("wmic ComputerSystem get Manufacturer");
}


char *get_model(){
    return cmd_return("wmic CsProduct get Name");
}


char *get_cpu(){
    char *cpu_model;
//    char *num_cores = malloc(BUF_SIZE);

    cpu_model = cmd_return("wmic CPU get name");
//    num_cores = cmd_return("wmic CPU get NumberOfCores");

    for (int i = 0; i < COUNT(cpu_config); ++i) {
        if (cpu_config[i].repl_str == NULL) {
            remove_substring(cpu_model, cpu_config[i].substring, cpu_config[i].length);
        } else {
            replace_substring(cpu_model, cpu_config[i].substring, cpu_config[i].repl_str, cpu_config[i].length, cpu_config[i].repl_len);
        }
    }

    truncate_spaces(cpu_model);
//
//    char *cpu = malloc(BUF_SIZE);
//    snprintf(cpu, BUF_SIZE, "%s (%d)", cpu_model, num_cores);
    return cpu_model;
}


char *get_gpu1(){
    return cmd_return("wmic path win32_videocontroller get name");
}


char *get_gpu2(){
    return 0;
}


char *get_memory(){
    // memorychip get Capacity -- 8589934592
//    7,991 MB
//    Total Physical Memory:     7,991 MB
//    Available Physical Memory: 1,073 MB
//    char *total_memory;
//    char *available_memory;
//    total_memory     = cmd_return("wmic ComputerSystem get TotalPhysicalMemory");
////    available_memory = cmd_return("wmic ComputerSystem get FreePhysicalMemory");
////    printf("%s  / %s", total_memory, available_memory);
//    double total_mem;
//    total_mem = atof(total_memory);
//    char *memory = malloc(BUF_SIZE);
//    snprintf(memory, BUF_SIZE, "%s",total_memory);



    return cmd_return("wmic MemoryChip get Capacity");
}


char *get_os(){
    // wmic os get caption -- Microsoft Windows 10 Home Single Language
    // wmic os get CSName -- ASPIRE5
    char *os = malloc(BUF_SIZE);
    snprintf(os, BUF_SIZE, "%s", cmd_return("wmic os get caption"));
    return os;
}


char *get_battery_percentage(){
    char *battery_capacity;
//    char *battery_status;

    battery_capacity = cmd_return("WMIC PATH Win32_Battery Get EstimatedChargeRemaining");
//    battery_status   = cmd_return("WMIC PATH Win32_Battery Get BatteryStatus");
//    char *battery = malloc(BUF_SIZE);
//    printf("\n\n%s  %s\n\n\n", battery_status, battery_capacity);
//    strcat(battery_capacity, battery_status);
//    printf("\n\n%s\n\n\n", battery_status);
//    snprintf(battery, 20, "%s %%", battery_capacity);
    return battery_capacity;
}


char *get_packages_pacman(){
    return 0;
}


char *get_shell(){
    return 0;
}


char *get_resolution(){
    return 0;
}


char *get_terminal(){
    return 0;
}


char *get_disk_usage_root(){
    return 0;
}


char *get_disk_usage_home(){
    return 0;
}


char *get_colors1(){
    return 0;
}


char *get_colors2(){
    return 0;
}


static char *spacer() {
    // freeable, null-terminated string of length 1
    return calloc(1, 1);
}


char *get_value(struct conf c) {
    char *value;
    value = c.function();
    return value;
}

int main() {
//    printf("\033[1;31m");
//    printf("Hello World\n");
//    printf(ANSI_RED "Hello World\n");
//    printf("\033[32mHello World\n");

    int offset =0;
    for (int i = 0; i < COUNT(LOGO); i++) {
        // If we've run out of information to show...
        if(i >= COUNT(config) - offset) {
            // just print the next line of the logo
            printf(COLOR"\t %s\n", LOGO[i+offset]);
        }
        else {
            char *label = config[i+offset].label, *value = get_value(config[i+offset]);
            if (strcmp(label, "") != 0) {// check if label is empty, otherwise it's a spacer
                printf("\t %s \t %s %s\n", LOGO[i+offset], label, value);
//                ++offset; // print next line of information
                free(value); // free memory allocated for empty value
//                label = config[i+offset].label; // read new label and value
//                printf("%d \t %s \t %s \t %s\n", i , LOGO[i], label, value);
//                value = get_value(config[i+offset]);
//                printf("%d \t %s \t %s \t %s\n", i , LOGO[i], label, value);
            }
//            printf(COLOR"%s\t %s \t %s \n", LOGO[i], label, value);
        }

    }
    system("pause");

    return 0;
}