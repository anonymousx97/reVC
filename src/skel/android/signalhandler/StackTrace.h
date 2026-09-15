//
// Created by mrxenginner on 13/07/2025.
//

#ifndef REVC_STACKTRACE_H
#define REVC_STACKTRACE_H

#if defined ANDROID

#include <dlfcn.h>
#include <execinfo.h>
#include <unwind.h>

extern uintptr_t g_libREVC;

#if defined(__aarch64__)
#define PRINT_CRASH_STATES(context) \
    Logger::CrashLog("1: libreVC.so + 0x%llx", (unsigned long long)(context->uc_mcontext.pc - g_libREVC)); \
    Logger::CrashLog("2: libreVC.so + 0x%llx", (unsigned long long)(context->uc_mcontext.regs[30] - g_libREVC));
#elif defined(__arm__)
#define PRINT_CRASH_STATES(context) \
    Logger::CrashLog("1: libreVC.so + 0x%lx", (unsigned long)(context->uc_mcontext.arm_pc - g_libREVC)); \
    Logger::CrashLog("2: libreVC.so + 0x%lx", (unsigned long)(context->uc_mcontext.arm_lr - g_libREVC));
#elif defined(__x86_64__)
#define PRINT_CRASH_STATES(context) \
    Logger::CrashLog("1: libreVC.so + 0x%llx", (unsigned long long)(context->uc_mcontext.gregs[REG_RIP] - g_libREVC));
#elif defined(__i386__)
#define PRINT_CRASH_STATES(context) \
    Logger::CrashLog("1: libreVC.so + 0x%lx", (unsigned long)(context->uc_mcontext.gregs[REG_EIP] - g_libREVC));
#else
#define PRINT_CRASH_STATES(context) \
    Logger::CrashLog("Crash states printing not implemented for this architecture");
#endif

class CStackTrace
{
public:
    static void printBacktrace()
    {
        Logger::CrashLog("------------ START BACKTRACE ------------");
        Logger::CrashLog(" ");
        PrintStackTrace();
    }

private:
    static _Unwind_Reason_Code TraceFunction(_Unwind_Context* context, void* arg) {
        uintptr_t pc = _Unwind_GetIP(context);

        Dl_info info;
        if (dladdr(reinterpret_cast<void*>(pc), &info) && info.dli_sname != nullptr) {
            Logger::CrashLog("[adr: %p reVC: %p] %s\n",
                     reinterpret_cast<void*>(pc),
                     reinterpret_cast<void*>(pc - g_libREVC),
                     info.dli_sname);
        } else {
            Logger::CrashLog("[adr: %p reVC: %p] name not found\n",
                     reinterpret_cast<void*>(pc),
                     reinterpret_cast<void*>(pc - g_libREVC));
        }

        return _URC_NO_REASON;
    }

    static void PrintStackTrace() {
        _Unwind_Backtrace(TraceFunction, nullptr);
    }

};
#endif

#endif
