#ifndef _MISC_HPP_
#define _MISC_HPP_

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <string>


namespace base { 

// "YYYY-mm-DD HH:MM:SS uuu"
#define TIME_NOW_STR_SIZE 30
void time_now_str(char *now);

// NOTE: \n is stripped from input
std::string getline(FILE *fp, char delim='\n');

} // namespace base


#endif
