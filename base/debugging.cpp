#ifndef _DEBUGGING_HPP_
#define _DEBUGGING_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <vector>
#include <utility>

#include "debugging.hpp"
#include "misc.hpp"

using namespace std;
namespace base {

/* borrow code from 
 * https://github.com/santazhang/base-utils/blob/master/base/debugging.cc 
 */ 

void print_stack_trace(FILE* fp /* =? */) {
    const int max_trace = 1024;
    void* callstack[max_trace];
    memset(callstack, 0, sizeof(callstack));
    int frames = backtrace(callstack, max_trace);

    char **str_frames = backtrace_symbols(callstack, frames);
    if (str_frames == nullptr) {
        fprintf(fp, "  *** failed to obtain stack trace!\n");
        return;
    }

    fprintf(fp, "  *** begin stack trace ***\n");
    for (int i = 0; i < frames - 1; i++) {
        string trace = str_frames[i];
        size_t idx = trace.rfind(' ');
        size_t idx2 = trace.rfind(' ', idx - 1);
        idx = trace.rfind(' ', idx2 - 1) + 1;
        string mangled = trace.substr(idx, idx2 - idx);
        string left = trace.substr(0, idx);
        string right = trace.substr(idx2);

        string cmd = "c++filt -n ";
        cmd += mangled;

        auto demangle = popen(cmd.c_str(), "r");
        if (demangle) {
            string demangled = getline(demangle);
            fprintf(fp, "%s%s%s\n", left.c_str(), demangled.c_str(), right.c_str());
            pclose(demangle);
        } else {
            fprintf(fp, "%s\n", str_frames[i]);
        }
    }
    fprintf(fp, "  ***  end stack trace  ***\n");
    fflush(fp);

    free(str_frames);
}


} // namespace base


#endif
