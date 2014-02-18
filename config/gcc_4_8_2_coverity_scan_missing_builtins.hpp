#ifndef CONFIG_GCC_4_8_2_COVERITY_SCAN_MISSING_BUILTINS_HPP
#define CONFIG_GCC_4_8_2_COVERITY_SCAN_MISSING_BUILTINS_HPP

# define __builtin_ia32_bsrsi(x) ((int)x)
# define __builtin_ia32_rdpmc(x) ((unsigned long long)x)
# define __builtin_ia32_rdtsc()  ((unsigned long long)0)
# define __builtin_ia32_rdtscp(x) ((unsigned long long)x)
# define __builtin_ia32_rolqi(x,  c) ((unsigned char)x)
# define __builtin_ia32_rolhi(x, c) ((unsigned short)x)
# define __builtin_ia32_rorqi(x, c) ((unsigned char)x)
# define __builtin_ia32_rorhi(x, c) ((unsigned short)x)
# define __builtin_ia32_pause() ((void)0)
# define __builtin_ia32_bsrdi(x) ((int)x)
# define __builtin_ia32_fxsave(x) ((void)x)
# define __builtin_ia32_fxrstor(x) ((void)x)
# define __builtin_ia32_fxsave64(x) ((void)x)
# define __builtin_ia32_fxrstor64(x) ((void)x)
# define __builtin_ia32_addcarryx_u32(...) ((unsigned char)0)
# define __builtin_ia32_addcarryx_u64(...) ((unsigned char)0)

#endif /* CONFIG_GCC_4_8_2_COVERITY_SCAN_MISSING_BUILTINS_HPP */