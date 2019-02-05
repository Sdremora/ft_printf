#include <stdio.h>
#include <string.h>
#include "ft_printf.h"
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <float.h>
#include <wchar.h>
#include <math.h>

#define FILE_NAME "test/output.txt"
#define BUFF_SIZE 10000

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define NC "\033[0m"

#define COMPARE(...) \
    write_char_origin = 0; \
    write_char_copy = 0; \
    dup2(fd_write, STDOUT_FILENO); \
    write_char_origin = printf(__VA_ARGS__); \
    fflush(stdout); \
    read_bytes_count = read(fd_read, line1, BUFF_SIZE); \
    line1[read_bytes_count] = '\0'; \
    write_char_copy = ft_printf(__VA_ARGS__); \
    fflush(stdout); \
    read_bytes_count = read(fd_read, line2, BUFF_SIZE); \
    line2[read_bytes_count] = '\0'; \
    dup2(fd_std, STDOUT_FILENO); \
    format = #__VA_ARGS__; \
    count++; \
    if (!compare(line1, line2, write_char_origin, write_char_copy, count, format)) \
        miss_count++; \
    fflush(stdout);

int compare(char *original, char *copy, int write_char_origin, int write_char_copy, int num, char *format)
{
    if (strcmp(original, copy) == 0 && write_char_origin == write_char_copy)
    {
        printf("#%d -> %sOK%s\n", num, GREEN, NC);
		printf("  ==> printf(%s)\n", format);
		printf("\tOrigin str -> %s;\n\t       out -> %d\n", original, write_char_origin);
        printf("\t  Copy str -> %s;\n\t       out -> %d\n", copy, write_char_copy);
        return (TRUE);
    }
    else
    {
        printf("#%d -> %sFALSE%s", num, RED, NC);
        printf("  ==> printf(%s)\n", format);
        printf("\tOrigin str -> %s;\n\t       out -> %d\n", original, write_char_origin);
        printf("\t  Copy str -> %s;\n\t       out -> %d\n", copy, write_char_copy);
        return (FALSE);
    }
}
void    print_result(int miss_count)
{
    char *str;
    if (miss_count > 0)
    {
        if (miss_count == 1)
            str = "тест не пройден";
        if (miss_count == 2 || miss_count == 3 || miss_count == 4)
            str = "теста не пройдено";
        if (miss_count > 4)
            str = "тестов не пройдено";
        printf("<=========== %s%d %s%s ===========>\n", RED, miss_count, str, NC);
    }
    else
        printf("<=========== %s^_^%s ===========>\n", GREEN, NC);
}

int     main(void)
{
    char    line1[BUFF_SIZE];
    char    line2[BUFF_SIZE];
    int     read_bytes_count;
    int     fd_write;
    int     fd_read;
    int     fd_std;
    char    *format;
    int     miss_count;
    int     count;
    int     write_char_origin;
    int     write_char_copy;

	//setbuf(stdout, NULL);
	if (access(FILE_NAME, F_OK) == 0)
		remove(FILE_NAME);
    FILE *fp = fopen(FILE_NAME, "ab+");
    fd_write = open(FILE_NAME, O_RDWR);
    fd_read = open(FILE_NAME, O_RDONLY);
    fd_std = dup(STDOUT_FILENO);
    miss_count = 0;
	setlocale(LC_ALL, "en_US.UTF-8");

    printf("%sГруппа: Закусон%s\n", YELLOW, NC);
    	count = 0;
    	COMPARE("Hi");
    	COMPARE("");
    	COMPARE("\n");

    printf("%sГруппа: sS%s\n", YELLOW, NC);  //      <==== sS
    	count = 0;
    	COMPARE("%s", "it's work!");
    	COMPARE("%s%s", "it's work!", "really work =)");
    	COMPARE("%s%s%s%s%s%s%s%s", "it's work!", "really work =)", "<>", "<>", "<>", "<>", "<>", "<>");
    	COMPARE("%s%s%s%s%s%s%s%s", "it's work!", "really work =)", "<>", "<>", "<>", "<>", "<>", "<>");
		COMPARE("123%s34%5.2s78%s10s", "one", "two", "three");
		COMPARE("23%s34%5.2s78%s10s", "one", "two", "three");
		COMPARE("%12.2s", "123");
		COMPARE("%s", "Юникод?");
		COMPARE("%s", "Ё");
		COMPARE("Проверочка%s", "Ё");
		COMPARE("=>%10s", "abcdef");
		COMPARE("=>%10s", "123456789abcdef");
		COMPARE("=>%10.4s", "123456789abcdef");
		COMPARE("=>%10.0s", "123456789abcdef");
		COMPARE("=>%10.s", "123456789abcdef");
		COMPARE("=>%-10s", "abcdef");
		COMPARE("=>%-10s", "abc  ");
		COMPARE("=>%-10s", "  abc  ");
		COMPARE("=>%-10.2s", "abc  ");
		COMPARE("=>%-10.2s", "  abc");
		COMPARE("=>%-10.2s", "  abc  ");
		COMPARE("=>%-10.2s", "  abc  ");
		COMPARE("=>%10s", "abc  ");
		COMPARE("=>%10s", "  abc");
		COMPARE("=>%10s", "  abc  ");
		COMPARE("=>%10s", "  abc  ");
		COMPARE("123%10s456", "  abc  ");
		COMPARE("%s", "raz");
		COMPARE("%*s", 10, "raz");
		COMPARE("%.5s", "1234567");
		COMPARE("%.5s", "12");
		COMPARE("%5s", "12345");
		COMPARE("%5s", "123");
		COMPARE("%5s", "12345678");
		COMPARE("%05s", "12");
		COMPARE("% 05s", "12");
		COMPARE("%+05s", "12");
		COMPARE("%-05s", "12");
		COMPARE("%#05s", "12");
		COMPARE("%10s", NULL);
		COMPARE("%010s", NULL);
		COMPARE("%s%2s", "", "123");
		COMPARE("%.0s", "123");
		COMPARE("@@%ls\n", L"∑∑œß∂ƒ");
		COMPARE("%S", NULL);
		COMPARE("%S", L"");
		COMPARE("%S", L"ϡϡϬϬɷɷ");
		COMPARE("%S", L"ϡϡϬϬɷɷw");
		COMPARE("%ls", L"ϡϡϬϬɷɷw");
		COMPARE("%ls", L"ϡϡϬϬɷɷw");
		COMPARE("%20ls", L"ϡϡϬϬɷɷw");
		COMPARE("%12ls", L"ϡϡϬϬɷɷw");
		COMPARE("%.5ls", L"ϡϡϬϬɷɷw");
		COMPARE("%6.3ls", L"©©");
		COMPARE("% -10.5S bla", L"∆∆πµ≥÷æ");
		COMPARE("%S", NULL);
		COMPARE("%S", L"");
		COMPARE("%8S", L"©®©®");
		COMPARE("%9S", L"©®©®");
		COMPARE("%-9S", L"©®©®");
		COMPARE("%09S", L"©®©®");
		COMPARE("%.4S", L"©®©®");
		COMPARE("%.5S", L"©®©®");
		COMPARE("%.4S", L"߿߿");
		COMPARE("%.2S", L"߿߿");
		COMPARE("%.2S", L"߿߿");
		COMPARE("%.4S", L"߿߿");
		COMPARE("%.5S", L"߿߿");
		COMPARE("%.2S", L"ࠀࠀ");
		COMPARE("%.3S", L"ࠀࠀ");
		COMPARE("%.5S", L"ࠀࠀ");
		COMPARE("%.6S", L"ࠀࠀ");
		COMPARE("%.7S", L"ࠀࠀ");
		COMPARE("%10.4S", L"߿ࠀ߿ࠀ");
		COMPARE("%-10.2S", L"߿ࠀ߿ࠀ");
		COMPARE("%10.5S", L"߿ࠀ߿ࠀ");
		COMPARE("%-10.6S", L"߿ࠀ߿ࠀ");
		wchar_t *s = L"a√æb";
		COMPARE("%S", s);
		s = L"√æƒÄb";
		COMPARE("%S", s);
		s = L"S„™º";
		COMPARE("%.5ls", s);
		s = L"S";
		COMPARE("%.2ls", s);
		s = L"a√∫b";
		COMPARE("%-4S", s);
		s = L"aƒÄb";
		COMPARE("%9ls", s);
		s = L"S„™º ";
		COMPARE("%9.6ls %S", s, L"a");
		COMPARE("%-+-12.7Dt%0 4i %04.2% et %lc titi", 125, 124, 256);

	printf("%sГруппа: cС%s\n", YELLOW, NC); //      <==== cС
    	count = 0;
		COMPARE("%c", 0);
		COMPARE("%10c", 0);
		COMPARE("%-10c", 0);
		COMPARE("==>%2c", 0);
		COMPARE("%.0%");
		COMPARE("%.5%");
		COMPARE("%.0c", '1');
		COMPARE("%+C", 0);
		COMPARE("% C", 0);
		COMPARE("% C", L'ϡ');
		COMPARE("% C", L'Ϭ');
		COMPARE("%.1C", L'Ϭ');
		COMPARE("%10c", 'b');
		COMPARE("%.4c", 'b');
		COMPARE("%-4c", 'b');
		COMPARE("%+c", 'b');
		COMPARE("% c", 'b');
		COMPARE("%#c", 'b');
		COMPARE("%0c", 'b');
		COMPARE("%010c", 'b');
		COMPARE("%0*c", 10, 'b');
		COMPARE("%c%c%c%c", 'a', 'b', 'c', 'd');
		COMPARE("%+lc", 0);
		COMPARE("% lc", 0);
		COMPARE("% lc", L'ϡ');
		COMPARE("% lc", L'Ϭ');
		COMPARE("%.1lc", L'Ϭ');
		COMPARE("%10c bla %10c bla", 0, 0);
		COMPARE("%lc", 0x40501);
		COMPARE("%lc", 0x1F680);
		COMPARE("%C", L'🚀');
		COMPARE("yo%2C%-12lc et %C titi %C tyty", 'u', 254, 256, 'a');
		COMPARE("%C", 0xbffe);
		COMPARE("%lc", 254);
		COMPARE("%C", 256);
		COMPARE("%LC", 0xbffe);


	printf("%sГруппа: %%%s\n", YELLOW, NC); //      <==== %
    	count = 0;

		COMPARE("%%");
		COMPARE("%%%%%%%%");
		COMPARE("%10%");
 		COMPARE("%.10%");
		COMPARE("%+%");
		COMPARE("%-%");
		COMPARE("%0%");
		COMPARE("%#%");
		COMPARE("%ll%");
		COMPARE("%h%");
		COMPARE("%hh%");
		COMPARE("%z%");
		COMPARE("%-10%");
		COMPARE("% 010%");
		COMPARE("% 010.5%");
		COMPARE("%- 010.5%");
		COMPARE(".0%%=%.0%\n");

    printf("%sГруппа: d and i%s\n", YELLOW, NC); //      <==== d and i
    	count = 0;
    	COMPARE("%d", 777);
    	COMPARE("%d%d%d", 1, 2, 3);

		COMPARE("%d", 123);
		COMPARE("%d", -123);
		COMPARE("%d", -123);
		COMPARE("%d", 2147483647);
		COMPARE("%d", 2147483648);
		COMPARE("%d", -2147483648);
		COMPARE("%d", 2147483650);
		COMPARE("%d", 3147483647);
		COMPARE("%d", 0);
		COMPARE("%d", -3147483648);
		COMPARE("%d", 9223372036854775807);
		COMPARE("%d", 9223372036854775810);
		COMPARE("%d", -9223372036854775808);

		COMPARE("%ld", 123l);
		COMPARE("%ld", 0l);
		COMPARE("%ld", -123l);
		COMPARE("%ld", INT_MAX);
		COMPARE("%ld", INT_MAX + 1);
		COMPARE("%ld", INT_MIN);
		COMPARE("%ld", INT_MIN - 1);
		COMPARE("%ld", LONG_MAX);
		COMPARE("%ld", LONG_MAX + 1);
		COMPARE("%ld", LONG_MIN);
		COMPARE("%ld", LONG_MIN - 1);

		COMPARE("%lld", 123l);
		COMPARE("%lld", 0l);
		COMPARE("%lld", -123l);
		COMPARE("%lld", INT_MAX);
		COMPARE("%lld", INT_MAX + 1);
		COMPARE("%lld", INT_MIN);
		COMPARE("%lld", INT_MIN - 1);
		COMPARE("%lld", LONG_MAX);
		COMPARE("%lld", LONG_MAX + 1);
		COMPARE("%lld", LONG_MIN);
		COMPARE("%lld", LONG_MIN - 1);

		COMPARE("%d", 4);
		COMPARE("% d", 4);
		COMPARE("%8d", 4);
		COMPARE("% 8d", 4);
		COMPARE("0d=%.0d\n", 0);
		COMPARE("% 8d", 12345678);
		COMPARE("%+8d", 12345678);
		COMPARE("%+ 8d", 12345678);
		COMPARE("%+ 8d", 12);
		COMPARE("% 8d", 12);
		COMPARE("%#d", 4);
		COMPARE("%0d", 4);
		COMPARE("%03d", 4);
		COMPARE("%0+3d", 4);
		COMPARE("% 1d", 4);
		COMPARE("% +1d", 4);
		COMPARE("% 1d", 16);
		COMPARE("% 1d", -16);
		COMPARE("% +1d", 16);
		COMPARE(".0d=%#.0d\n", 0);
		COMPARE("%5d", 16);
		COMPARE("%.5d", 16);
		COMPARE("%6.5d", 16);
		COMPARE("%4.5d", 16);
		COMPARE("%010.5d", 16);
		COMPARE("%.5d", -16);
		COMPARE("%5d", -16);
		COMPARE("%5d", -16456);
		COMPARE("%5d", -1645);
		COMPARE("%-5d", -16);
		COMPARE("%-5d", 16);
		COMPARE("%-5.3d", 16);
		COMPARE("%-5.3d", -16);
		COMPARE("%-05.3d", -16);
		COMPARE("%0d", 4);
		COMPARE("%0d", -4);
		COMPARE("%05d", -4);
		COMPARE("%05d", 4);
		COMPARE("% 05d", 4);
		COMPARE("% 05d", -4);
		COMPARE("%010.0d", -4);
		COMPARE("%010.2d", -4);
		COMPARE("%010.3d", -4);
		COMPARE("%-010.0d", -4);
		COMPARE("%-010.2d", -4);
		COMPARE("%-010.3d", -4);
		COMPARE("%- 10d", 4);
		COMPARE("%+- 10d", 4);
		COMPARE("%+d", 4);
		COMPARE("%.4d", 16);
		COMPARE("%.4d", -16);
		COMPARE("%.2d", 16);
		COMPARE("%.2d", -16);
		COMPARE("%.3d", 16);
		COMPARE("%.3d", -16);
		COMPARE("%10.3d", -16);
		COMPARE("%+.4d", 16);
		COMPARE("%+6.4d", 16);
		COMPARE("%+.4d", 16);
		COMPARE("%0+.4d", 16);
		COMPARE("% 0+.4d", 16);
		COMPARE("% 0.4d", 16);
		COMPARE("% 0.2d", 16);
		COMPARE("%.2d", 16);
		COMPARE("%.4d", 16);
		COMPARE("%+.2d", 16);
		COMPARE("%+.4d", 16);
		COMPARE("%+.4d", 16);
		COMPARE("%+4d", 16);
		COMPARE("%+04d", 16);
		COMPARE("%-05d", 16);
		COMPARE("%05d", 16);
		COMPARE("%.d", 16);
		COMPARE("%.d", 0);
		COMPARE("%d", 0);
		COMPARE("%10.d", 0);
		COMPARE("%+10.d", 0);
		COMPARE("%+10.d", -0);
		COMPARE("%+- 10.d", 0);
		COMPARE("%+-010.d", 0);
		COMPARE("%.d", 1);
		COMPARE("%d", 0);
		COMPARE("%+-5d", 0);
		COMPARE("%+-5d", 4);
		COMPARE("%*d", -20, 10);
		COMPARE("%*.*d", -20, -10, 10);
		COMPARE("%.*d", -10, 10);
		COMPARE("%D", LONG_MAX);
		COMPARE("%--d", 1234);
		COMPARE("%------+++++    --- ++###0-#d", 1234);
		COMPARE("-+**%------+++++    --- ++###0-#8d", 1234);
		COMPARE("%------+++++    --- ++###-#8d", 1234);
		COMPARE("%------    --- ###-#8d", 1234);
		COMPARE("%00000   00000008d", 1234);
		COMPARE("+++%00000   00000008d", -1234);
		COMPARE("%00000   00000008d", +1234);
		COMPARE("%00000   0+0000008d", +1234);
		COMPARE("%0000000000008d", +1234);
		COMPARE("%0000000000008d", -1234);
		COMPARE("%5d", -1234);
		COMPARE("%5d", +12345678);
		COMPARE("%5d", 123);
		COMPARE("%5d", -123);
		COMPARE("%-+ ##5d", -123);
		COMPARE("%-+ ##0d", -123);
		COMPARE("%2147483649d",1235678910);
		COMPARE("%-+ ##9999999999999999999999999999999999.5d", -1235678910);
		COMPARE("%-+ ##.5d", -1235678910);
		COMPARE("%.5d", -1235678910);
		COMPARE("%.5d", -12);
		COMPARE("%*d", 5, -12);
		COMPARE("%*d", 5, +1234567);
		COMPARE("%*d", 5, 1234567);
		COMPARE("%-+*d", 5, -12);
		COMPARE("%+ -*d", 5, +1234567);
		COMPARE("%#-+ *d", 5, 1234567);
		COMPARE("%21474836490d", 123);
		COMPARE("%.d", 123);
		COMPARE("%.d", 12345678);
		COMPARE("%.d", +12345678);
		COMPARE("%.8d", -123);
		COMPARE("%.8d", +123);
		COMPARE("%.0d", 123);
		COMPARE("%.1d", 123);
		COMPARE("%ld", 9223372036854775807);
		COMPARE("%lld", 9223372036854775807);
		COMPARE("%.*d", 5, 123);
		COMPARE("%0.*d", 5, 123);
		COMPARE("%0.*d", 5, -123);
		COMPARE("%0.*d", 5, +123);
		COMPARE("%0.*d", 5, -1234556);
		COMPARE("%hd", -32769);

	printf("%sГруппа: u%s\n", YELLOW, NC); //      <==== u
    	count = 0;
    	COMPARE("%d", 777);
    	COMPARE("%d%d%d", 1, 2, 3);

		COMPARE("%u", 123);
		COMPARE("%u", -123);
		COMPARE("%u", -123);
		COMPARE("%u", 2147483647);
		COMPARE("%u", 2147483648);
		COMPARE("%u", -2147483648);
		COMPARE("%u", 2147483650);
		COMPARE("%u", 3147483647);
		COMPARE("%u", 0);
		COMPARE("%u", -3147483648);
		COMPARE("%u", 9223372036854775807);
		COMPARE("%u", 9223372036854775810);
		COMPARE("%u", -9223372036854775808);
		COMPARE("%u", 123);
		COMPARE("%u", 0);
		COMPARE("%u", -123);
		COMPARE("%u", INT_MAX);
		COMPARE("%u", INT_MAX + 1);
		COMPARE("%u", INT_MIN);
		COMPARE("%u", INT_MIN - 1);
		COMPARE("%u", UINT_MAX);
		COMPARE("%u", UINT_MAX + 1);

		COMPARE("%lu", 123l);
		COMPARE("%lu", 0l);
		COMPARE("%lu", -123l);
		COMPARE("%lu", UINT_MAX);
		COMPARE("%lu", UINT_MAX + 1);
		COMPARE("%lu", ULONG_MAX);
		COMPARE("%lu", ULONG_MAX + 1);

		COMPARE("%llu", 123l);
		COMPARE("%llu", 0l);
		COMPARE("%llu", -123l);
		COMPARE("%llu", UINT_MAX);
		COMPARE("%llu", UINT_MAX + 1);
		COMPARE("%llu", ULONG_MAX);
		COMPARE("%llu", ULONG_MAX + 1);

		COMPARE("%u", 4);
		COMPARE("% u", 4);
		COMPARE("%8u", 4);
		COMPARE(".0u=%#.0u\n", 0);
		COMPARE("% 8u", 4);
		COMPARE("% 8u", 12345678);
		COMPARE("%+8u", 12345678);
		COMPARE("%+ 8u", 12345678);
		COMPARE("%+ 8u", 12);
		COMPARE("% 8u", 12);
		COMPARE("%#u", 4);
		COMPARE("%0u", 4);
		COMPARE("%03u", 4);
		COMPARE("%0+3u", 4);
		COMPARE("% 1u", 4);
		COMPARE("% +1u", 4);
		COMPARE("% 1u", 16);
		COMPARE("% 1u", -16);
		COMPARE("% +1u", 16);
		COMPARE("%5u", 16);
		COMPARE("%.5u", 16);
		COMPARE("%6.5u", 16);
		COMPARE("%4.5u", 16);
		COMPARE("%010.5u", 16);
		COMPARE("%.5u", -16);
		COMPARE("%5u", -16);
		COMPARE("%5u", -16456);
		COMPARE("%5u", -1645);
		COMPARE("%-5u", -16);
		COMPARE("%-5u", 16);
		COMPARE("%-5.3u", 16);
		COMPARE("%-5.3u", -16);
		COMPARE("%-05.3u", -16);
		COMPARE("%0u", 4);
		COMPARE("0u=%.0u\n", 0);
		COMPARE("%0u", -4);
		COMPARE("%05u", -4);
		COMPARE("%05u", 4);
		COMPARE("% 05u", 4);
		COMPARE("% 05u", -4);
		COMPARE("%010.0u", -4);
		COMPARE("%010.2u", -4);
		COMPARE("%010.3u", -4);
		COMPARE("%-010.0u", -4);
		COMPARE("%-010.2u", -4);
		COMPARE("%-010.3u", -4);
		COMPARE("%- 10u", 4);
		COMPARE("%+- 10u", 4);
		COMPARE("%+u", 4);
		COMPARE("%.4u", 16);
		COMPARE("%.4u", -16);
		COMPARE("%.2u", 16);
		COMPARE("%.2u", -16);
		COMPARE("%.3u", 16);
		COMPARE("%.3u", -16);
		COMPARE("%10.3u", -16);
		COMPARE("%+.4u", 16);
		COMPARE("%+6.4u", 16);
		COMPARE("%+.4u", 16);
		COMPARE("%0+.4u", 16);
		COMPARE("% 0+.4u", 16);
		COMPARE("% 0.4u", 16);
		COMPARE("% 0.2u", 16);
		COMPARE("%.2u", 16);
		COMPARE("%.4u", 16);
		COMPARE("%+.2u", 16);
		COMPARE("%+.4u", 16);
		COMPARE("%+.4u", 16);
		COMPARE("%+4u", 16);
		COMPARE("%+04u", 16);
		COMPARE("%-05u", 16);
		COMPARE("%05u", 16);
		COMPARE("%.u", 16);
		COMPARE("%.u", 0);
		COMPARE("%u", 0);
		COMPARE("%.u", 1);
		COMPARE("%.10u", 0);
		COMPARE("%*.*u", -20, -10, 10);
		COMPARE("%.*u", -10, 10);
		COMPARE("%U", LONG_MAX);

	printf("%sГруппа: o%s\n", YELLOW, NC); //      <==== o
		count = 0;

		COMPARE("%o", 0);
		COMPARE("%o", 1);
		COMPARE("%o", 7);
		COMPARE("%o", 8);
		COMPARE("%o", 9);
		COMPARE("%o", 10);
		COMPARE("%o", -10);
		COMPARE("%o", 20);
		COMPARE("%.0o", 0);
		COMPARE("%#.0o", 0);
		COMPARE("%-#.0o", 0);
		COMPARE("% #.0o", 5);
		COMPARE("% #.0o", 7);
		COMPARE("% 0o", 7);
		COMPARE("%.0o", 7);
		COMPARE(".0o=%#.0o\n", 0);
		COMPARE("0o=%.0o\n", 0);
		COMPARE("%.0o", 0);
		COMPARE("%#.0o", 0);

		COMPARE("%o", SIZE_T_MAX);
		COMPARE("%llo", SIZE_T_MAX);
		COMPARE("%#o", 16);
		COMPARE("%#5o", 16);
		COMPARE("%#05o", 16);
		COMPARE("%#6o", 2500);
		COMPARE("%o", 123);
		COMPARE("%o", -123);
		COMPARE("%o", -123);
		COMPARE("%o", 2147483647);
		COMPARE("%o", 2147483648);
		COMPARE("%o", -2147483648);
		COMPARE("%o", 2147483650);
		COMPARE("%o", 3147483647);
		COMPARE("%o", 0);
		COMPARE("%o", -3147483648);
		COMPARE("%o", 9223372036854775807);
		COMPARE("%o", 9223372036854775810);
		COMPARE("%o", -9223372036854775808);
		COMPARE("%o", 123);
		COMPARE("%o", 0);
		COMPARE("%o", -123);
		COMPARE("%o", INT_MAX);
		COMPARE("%o", INT_MAX + 1);
		COMPARE("%o", INT_MIN);
		COMPARE("%o", INT_MIN - 1);
		COMPARE("%o", UINT_MAX);
		COMPARE("%o", UINT_MAX + 1);

		COMPARE("%lo", 123l);
		COMPARE("%lo", 0l);
		COMPARE("%lo", -123l);
		COMPARE("%lo", UINT_MAX);
		COMPARE("%lo", UINT_MAX + 1);
		COMPARE("%lo", ULONG_MAX);
		COMPARE("%lo", ULONG_MAX + 1);

		COMPARE("%llo", 123l);
		COMPARE("%llo", 0l);
		COMPARE("%llo", -123l);
		COMPARE("%llo", UINT_MAX);
		COMPARE("%llo", UINT_MAX + 1);
		COMPARE("%llo", ULONG_MAX);
		COMPARE("%llo", ULONG_MAX + 1);
		COMPARE("%*.*o", -20, -10, 10);
		COMPARE("%.*o", -10, 10);
		COMPARE("%O", LONG_MAX);

		COMPARE("%#.O", 0);
		COMPARE("%#.3o", 1);
		COMPARE("%#.3o", 1);
		COMPARE("%.3o", 1);
		COMPARE("%.o", 1);
		COMPARE("%o", 1);
		COMPARE("%#2o", 0);
		COMPARE("%2o", 0);
		COMPARE("%*o", 0, 0);
		COMPARE("t%04.2o%#2oet %#-8.3o titi", 0, 0, 0);
		COMPARE("m%#.9odee", 123456789);

	printf("%sГруппа: x%s\n", YELLOW, NC); //      <==== xX
		count = 0;

		COMPARE("%x", 0);
		COMPARE("%x", 1);
		COMPARE("%x", 7);
		COMPARE("%x", 8);
		COMPARE("%x", 9);
		COMPARE("%x", 10);
		COMPARE("%x", -10);
		COMPARE("%x", 20);
		COMPARE("%.0x", 0);
		COMPARE("%x", SIZE_T_MAX);
		COMPARE("%llx", SIZE_T_MAX);
		COMPARE("%10llx", 16);
		COMPARE("0x=%.0x\n", 0);
		COMPARE("%10.5llx", 16);
		COMPARE("%010llx", 16);
		COMPARE("%#10llx", 16);
		COMPARE("%#10.5llx", 16);
		COMPARE("%#010llx", 16);
		COMPARE("%-#10llx", 16);
		COMPARE("%-#10.5llx", 16);
		COMPARE("%-#010llx", 16);
		COMPARE("%-10x", 16);
		COMPARE("%-010x", 10);
		COMPARE("%-0#10x", 16);
		COMPARE("%-0#.10x", 16);
		COMPARE("%10x", 12);
		COMPARE("%3x", 16);
		COMPARE(".0x=%#.0x\n", 0);
		COMPARE("%#3x", 18);
		COMPARE("%-#3x", 16);
		COMPARE("%5X", 2123456);
		COMPARE("%#5X", 456878);
		COMPARE("%.0x", 0);
		COMPARE("% .0x", 0);
		COMPARE("%#.0x", 0);
		COMPARE("%#5.0x", 0);
		COMPARE("%#-5.0x", 0);
		COMPARE("%x", 123);
		COMPARE("%x", -123);
		COMPARE("%x", -123);
		COMPARE("%x", 2147483647);
		COMPARE("%x", 2147483648);
		COMPARE("%x", -2147483648);
		COMPARE("%x", 2147483650);
		COMPARE("%x", 3147483647);
		COMPARE("%x", 0);
		COMPARE("%x", -3147483648);
		COMPARE("%x", 9223372036854775807);
		COMPARE("%x", 9223372036854775810);
		COMPARE("%x", -9223372036854775808);
		COMPARE("%x", 123);
		COMPARE("%x", 0);
		COMPARE("%x", -123);
		COMPARE("%x", INT_MAX);
		COMPARE("%x", INT_MAX + 1);
		COMPARE("%x", INT_MIN);
		COMPARE("%x", INT_MIN - 1);
		COMPARE("%x", UINT_MAX);
		COMPARE("%x", UINT_MAX + 1);

		COMPARE("%lX", 123l);
		COMPARE("%lX", 0l);
		COMPARE("%lX", -123l);
		COMPARE("%lX", UINT_MAX);
		COMPARE("%lX", UINT_MAX + 1);
		COMPARE("%lX", ULONG_MAX);
		COMPARE("%lX", ULONG_MAX + 1);

		COMPARE("%llX", 123l);
		COMPARE("%llX", 0l);
		COMPARE("%llX", -123l);
		COMPARE("%llX", UINT_MAX);
		COMPARE("%llX", UINT_MAX + 1);
		COMPARE("%llX", ULONG_MAX);
		COMPARE("%llX", ULONG_MAX + 1);
		COMPARE("%X", LONG_MAX);

		COMPARE("%#x", 0);
		COMPARE("%x", 0);
		COMPARE("%#X", 0);
		COMPARE("%#X", 1);
		COMPARE("%#o", 0);
		COMPARE("%#.0o", 0);
		COMPARE("%.0o", 0);
		COMPARE("%o", 0);
		COMPARE("%#u", 0);
		COMPARE("%#.0x", 0);
		COMPARE("%#.0x", 4);
		COMPARE("%.0x", 0);
		COMPARE("%.0x", 4);
		COMPARE("%#0x", 0);
		COMPARE("%#0x", 4);
		COMPARE("%0x", 0);
		COMPARE("%0x", 4);
		COMPARE("%x", 0);
		COMPARE("%x", 4);
		COMPARE("% x", 0);
		COMPARE("%*.*x", -20, -10, 10);
		COMPARE("%.*x", -10, 10);
		COMPARE("%#X", 0);

	printf("%sГруппа: p%s\n", YELLOW, NC); //      <==== p
		count = 0;
		COMPARE("%p", NULL);
		int point = 2;
		COMPARE("%p", &point);
		COMPARE("%#p", &point);
		COMPARE("%+p", &point);
		COMPARE("% p", &point);
		COMPARE("%20p", &point);
		COMPARE("%-20p", &point);
		COMPARE("%.4p", &point);
		COMPARE("%0p", 0);
		COMPARE("%020p", 0);
		COMPARE("%020p", &point);
		COMPARE("%-020p", &point);
		COMPARE("%.p, %.0p", 0, 0);
		COMPARE("%.p, %.0p", 1, 1);
		COMPARE("%.p", 0);
		COMPARE("%p", 0);
		COMPARE("%.5p", 1)
		ft_printf("%Lf\n", 12313L);
		printf("%Lf", 12313L);
		// ft_printf("123{red}dfgfdh{UNDERLINE}sdfsd\n");
	// printf("%sГруппа: fF%s\n", YELLOW, NC); //      <==== fF
	// 	count = 0;
	// 	long double num;

	// 	COMPARE("%f", 0.);
	// 	COMPARE("%f", 8.125);
	// 	COMPARE("%f", -8.125);
	// 	COMPARE("%.3f", 8.125);
	// 	COMPARE("%.2f", 8.125);
	// 	COMPARE("%.2f", 8.9999);
	// 	COMPARE("%.3f", 8.1239);
	// 	COMPARE("%.30f", 8.1239);
	// 	COMPARE("%.50f", 1.3);
	// 	COMPARE("%f", -1234567.125);
	// 	COMPARE("%f", 0.);
	// 	COMPARE("%f", 1.);
	// 	COMPARE("%f", 0.123456789);
	// 	COMPARE("%f", 1.123);
	// 	COMPARE("%f", -1.123);
	// 	COMPARE("%f", +1.123);
	// 	COMPARE("%f", +1.12321432342353453463463452345243534534634634523456435646534564563456324632463456457324634563245346354346534634634652345634653245324634645634535346346346456346346456346534634999);
	// 	COMPARE("%.50f", +1.12321432342353453463463452345243534534634634523456435646534564563456324632463456457324634563245346354346534634634652345634653245324634645634535346346346456346346456346534634999);
	// 	COMPARE("%.15f", +1.123456789);
	// 	COMPARE("%.50f", +1.123456789);
	// 	COMPARE("%.5f", +1.123456789);
	// 	COMPARE("%.3f", +1.1205);
	// 	COMPARE("%.3f", +1.1215);
	// 	COMPARE("%.3f", +1.1225);
	// 	COMPARE("%.3f", +1.1235);
	// 	COMPARE("%.3f", +1.1245);
	// 	COMPARE("%.3f", +1.1255);
	// 	COMPARE("%.3f", +1.1265);
	// 	COMPARE("%.3f", +1.1275);
	// 	COMPARE("%.3f", +1.1285);
	// 	COMPARE("%.3f", +1.1295);
	// 	COMPARE("%.3f", -1.1205);
	// 	COMPARE("%.3f", -1.1215);
	// 	COMPARE("%.3f", -1.1225);
	// 	COMPARE("%.3f", -1.1235);
	// 	COMPARE("%.3f", -1.1245);
	// 	COMPARE("%.3f", -1.1255);
	// 	COMPARE("%.3f", -1.1265);
	// 	COMPARE("%.3f", -1.1275);
	// 	COMPARE("%.3f", -1.1285);
	// 	COMPARE("%.3f", -1.1295);
	// 	COMPARE("%.0f", 1.7e308);
	// 	COMPARE("%f", 12.5);
	// 	COMPARE("%f", 11.5);
	// 	COMPARE("%f", -1.0/0.0);
	// 	COMPARE("%f", 1.0/0.0);
	// 	COMPARE("%f", 0.0/0.0);
	// 	COMPARE("%f", 0.0/1.0);
	// 	COMPARE("%f", 11.5);
	// 	COMPARE("%S", L"фывфывыфв");
	// 	COMPARE("%hx", -1);
	// 	COMPARE("%x", -1);
	// 	COMPARE("%lx", -1);
	// 	COMPARE("%llx", -1);
	// 	COMPARE("%i %i", 1.0123, 1);


	// 	COMPARE("%.3f", +1.1905);
	// 	COMPARE("%.3f", +1.1915);
	// 	COMPARE("%.3f", +1.1925);
	// 	COMPARE("%.3f", +1.1935);
	// 	COMPARE("%.3f", +1.1945);
	// 	COMPARE("%.3f", +1.1955);
	// 	COMPARE("%.3f", +1.1965);
	// 	COMPARE("%.3f", +1.1975);
	// 	COMPARE("%.3f", +1.1985);
	// 	COMPARE("%.3f", +1.1995);

	// 	COMPARE("%.3f", +1.1805);
	// 	COMPARE("%.3f", +1.1815);
	// 	COMPARE("%.3f", +1.1825);
	// 	COMPARE("%.3f", +1.1835);
	// 	COMPARE("%.3f", +1.1845);
	// 	COMPARE("%.3f", +1.1855);
	// 	COMPARE("%.3f", +1.1865);
	// 	COMPARE("%.3f", +1.1875);
	// 	COMPARE("%.3f", +1.1885);
	// 	COMPARE("%.3f", +1.1895);

	// 	COMPARE("%.3f", +1.1905);
	// 	COMPARE("%.3f", +1.1915);
	// 	COMPARE("%.3f", +1.1925);
	// 	COMPARE("%.3f", +1.1935);
	// 	COMPARE("%.3f", +1.1945);
	// 	COMPARE("%.3f", +1.1955);
	// 	COMPARE("%.3f", +1.1965);
	// 	COMPARE("%.4f", +1.1965);
	// 	COMPARE("%.5f", +1.1965);
	// 	COMPARE("%.3f", +1.1975);
	// 	COMPARE("%.3f", +1.1985);
	// 	COMPARE("%.3f", +1.1995);
	// 	COMPARE("%.3f", -1.1905);
	// 	COMPARE("%.3f", -1.1915);
	// 	COMPARE("%.3f", -1.1925);
	// 	COMPARE("%.3f", -1.1935);
	// 	COMPARE("%.3f", -1.1945);
	// 	COMPARE("%.3f", -1.1955);
	// 	COMPARE("%.3f", -1.1965);
	// 	COMPARE("%.3f", -1.1975);
	// 	COMPARE("%.3f", -1.1985);
	// 	COMPARE("%.3f", -1.1995);
	// 	COMPARE("%.0f", +1.123456789);
	// 	COMPARE("%.f", +1.123456789);
	// 	COMPARE("%.2f", +1.6992);
	// 	COMPARE("%.3f", +1.6992);
	// 	COMPARE("%.4f", +1.6992);
	// 	COMPARE("%.f", +1.6992);
	// 	COMPARE("%.f", +2.6992);
	// 	COMPARE("%.f", +2.99);
	// 	COMPARE("%.f", +2.95);
	// 	COMPARE("%.f", +2.4);
	// 	COMPARE("%.f", +2.1);
	// 	COMPARE("%.f", +3.99);
	// 	COMPARE("%.f", +3.95);
	// 	COMPARE("%.f", +3.4);
	// 	COMPARE("%.f", +3.1);
	// 	COMPARE("%.f", 9.99);
	// 	COMPARE("%.1f", 9.99);
	// 	COMPARE("%f", INFINITY);
	// 	COMPARE("%.f", -INFINITY);
	// 	COMPARE("%.f", NAN);
	// 	COMPARE("%10f", NAN);
	// 	COMPARE("%20.f", +3.4);
	// 	COMPARE("%20f", -3.12);
	// 	COMPARE("%20.20f", -3.12);
	// 	COMPARE("%30.20f", -32.12);
	// 	COMPARE("%15f", -INFINITY);
	// 	COMPARE("%+f", 34.2345);
	// 	COMPARE("%+f", -34.2345);
	// 	COMPARE("%020.24f", -23.1244);
	// 	COMPARE("%040.24f", -23.1244);
	// 	COMPARE("%040.24f", 0.0);
	// 	COMPARE("%040.24f", 123124.0);
	// 	COMPARE("%-.f", -INFINITY);
	// 	COMPARE("%-10.f", -INFINITY);
	// 	COMPARE("%10.f", -INFINITY);
	// 	COMPARE("%010.f", -INFINITY);
	// 	COMPARE("%010f", -INFINITY);
	// 	COMPARE("%010.f", 2.234);
	// 	COMPARE("%010f", 2.345);
	// 	COMPARE("%f", NAN);
	// 	COMPARE("%#f", 123.41);
	// 	COMPARE("%#f", NAN);
	// 	COMPARE("%#f", INFINITY);
	// 	COMPARE("% f", -234.423);
	// 	COMPARE("% 10f", 234.423);
	// 	COMPARE("% 10f", 0.0);
	// 	num = NAN;
	// 	COMPARE("%Lf", num);
	// 	COMPARE("%f", -NAN);
	// 	COMPARE("%Lf", -NAN);
	// 	COMPARE("%LF", NAN);
	// 	num = 1.0 / 0.0;
	// 	COMPARE("%LF", num);
	// 	COMPARE("%LF", -num);
	// 	COMPARE("%LF", NAN);
	// 	COMPARE("%LF", -NAN);
	// 	COMPARE("%010LF", 2222.345L);
	// 	COMPARE("%-10LF", 2123124122.345L);
	// 	COMPARE("%-10.30LF", 2123124122.3412412345L);
	// 	COMPARE("%f", 777.0);
    // 	COMPARE("%f%f%f", 1.0, 2.0, 3.0);

	// 	COMPARE("%f", 123.0);
	// 	COMPARE("%f", -123.0);
	// 	COMPARE("%f", -123.0);
	// 	COMPARE("%f", 2147483647.0);
	// 	COMPARE("%f", 2147483648.0);
	// 	COMPARE("%f", -2147483648.0);
	// 	COMPARE("%f", 2147483650.0);
	// 	COMPARE("%f", 3147483647.0);
	// 	COMPARE("%f", 0.0);
	// 	COMPARE("%f", -3147483648.0);
	// 	COMPARE("%f", 9223372036854775807.0);
	// 	COMPARE("%f", 9223372036854775810.0);
	// 	COMPARE("%f", -9223372036854775808.0);
	// 	COMPARE("%.100f", 8.000000000001);
	// 	COMPARE("%S", L"🚀🚀🚀🚌🚌🚌🚌");


    // printf("%sГруппа: левые, но рабочие последовательности%s\n", YELLOW, NC);  //      <==== левые, но рабочие последовательности
	// 	count = 0;
 	// 	COMPARE("%23+.4ll-# 012.2hhs", "123");
	// 	COMPARE("%23+.4ll-# 012.2hhs%34.4.3.2.1----+++ 23hhhhhs", "123", "456");
	// 	COMPARE("%-+s%-++rs", "-1235678910");
	// 	COMPARE("==> %-+10hhl", "-1235678910");
	// 	COMPARE("==> %10hhl", "-1235678910");
	// 	COMPARE("==> %10l", "-1235678910");
	// 	COMPARE("==> %10hh", "-1235678910");
	// 	COMPARE("==> %10", "-1235678910");
	// 	COMPARE("==> %10");
	// 	COMPARE("%10", "-1235678910");
	// 	COMPARE("%-+sasdf%s%+ - s%s", "it's work!", "really work =)", "<>", "<>");
	// 	COMPARE("%-+sasdf%s%+ - s%s", "it's work!", "really work =)", "<>", "<>");
    // 	COMPARE("%-+sasdf%s%+ - s%s%s%s%s%s", "it's work!", "really work =)", "<>", "<>", "<>", "<>", "<>", "<>");
	// 	COMPARE("%-+ ##9999999999999999999999999999999999s", "-1235678910");
	// 	COMPARE("%-+s%s%+ - s%s%s%s%s%s", "it's work!", "really work =)", "<>", "<>", "<>", "<>", "<>", "<>");
	// 	COMPARE("%%%");
	// 	COMPARE("%%%10<=");
	// 	COMPARE("% ");
	// 	COMPARE("%10");
	// 	COMPARE("%10<=");
	// 	COMPARE("%500.4+llhd", 1234567);
	// 	COMPARE("%+ *0.5d bla", -10, 4);
	// 	COMPARE("%%%");
	// 	COMPARE("%%%10<=");
	// 	COMPARE("% ");
	// 	COMPARE("%llld", 9223372036854775807);
	// 	COMPARE("%lhhltzLlld", 9223372036854775807);
	// 	COMPARE("%hhlhhltzLlld", 9223372036854775807);
	// 	COMPARE("%hhd", 9223372036854775807);
	// 	COMPARE("%hhlld", 9223372036854775807);
	// 	COMPARE("%hhllhhd", 9223372036854775807);
	// 	COMPARE("%hhd", 9223372036854775807);
	// 	COMPARE("%hhhd", 9223372036854775807);
	// 	COMPARE("%hhhlld", 9223372036854775807);
	// 	COMPARE("%llhhhd", 9223372036854775807);
	// 	COMPARE("%llhhd", 9223372036854775807);
	// 	COMPARE("%llhhd", 9223372036854775807);
	// 	COMPARE("%ll0hhd", 9223372036854775807);
	// 	COMPARE("%ll0h.hd", 9223372036854775807);
	// 	COMPARE("%ll0h.hd", 9223372036854775807);
	// 	COMPARE("%hhhd", 9223372036854775807);
	// 	COMPARE("%hhlhd", 9223372036854775807);
	// 	COMPARE("%hhllhd", 9223372036854775807);
	// 	COMPARE("%hhhhd", 9223372036854775807);
	// 	COMPARE("%hhhhhhhhhhhhhhhhhhhhhhd", 9223372036854775807);
	// 	COMPARE("%hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhlhhhd", 9223372036854775807);
	// 	COMPARE("%hd", 9223372036854775807);
	// 	COMPARE("%h40d", 9223372036854775807);
	// 	COMPARE("%h.d", 9223372036854775807);
	// 	COMPARE("%h.00d", 9223372036854775807);
	// 	COMPARE("%020hd", 9223372036854775807);
	// 	COMPARE("%ll020hd", 9223372036854775807);
	// 	COMPARE("%020hds", 9223372036854775807);
	// 	COMPARE("%ll020hds", 9223372036854775807);
	// 	COMPARE("%0.*2d", 5, -123);
	// 	COMPARE("% 5.*10s", 4, "1234567");
	// 	COMPARE("% 5.*s", 4, "1234567");
	// 	COMPARE("% *5.*s", 8, 4, "1234567");
	// 	COMPARE("% 5*.*s", 8, 4, "1234567");
	// 	COMPARE("% 5*5.*s", 8, 4, "1234567");
	// 	COMPARE("% *.*s", 8, 4, "1234567");
	// 	COMPARE("% *.*5s", 8, 4, "1234567");
	// 	COMPARE("% *.*5-s", 8, 4, "1234567");
	// 	COMPARE("% *.*5.2s", 8, 4, "1234567");
	// 	COMPARE("% *.*5.2342hhhhhs%4.*s", 8, 4, "1234567", 3, "777666");
	// 	COMPARE("% *.*5.2342hhyhhhs%4.s", 8, 4, "1234567", 3, "777666");
	// 	COMPARE("% 5.2%2.5s", "12345")
	// 	COMPARE("%w10 8.0 2s", "334455");
	// 	COMPARE("==>%+010.20wd", 'r', 10);
	// 	COMPARE("==>%+010.20cd", 'r', 10);
	// 	COMPARE("-%-010.20wd", 'r', 10);
	// 	COMPARE("-%-010.20cd", 'r', 10);

	// 	COMPARE("%-10.30LF", 2123124122.3412412345L);
	// // 	// COMPARE("%09223372032559808515d", 12);
	// // 	// COMPARE("%922337203685477580700000000000d\n", 123); //на один ноль меньше, чем внизу
	// // 	// // COMPARE("%9223372036854775807000000000000d\n", 123);  //Печатает дохрена пробелов
	// // 	// COMPARE("%92233720368547758070000000000000d\n", 123); //на один ноль больше, чем вверху

    // printf("%sГруппа: обработка ошибок%s\n", YELLOW, NC);  //      <==== обработка ошибок
	// 	// ==> Случаи когда настоящий printf выкидывает ошибку.
	// 	// когда printf выкидывает ошибку, все остальные вызовы printf отрабатывают
	// 	// но возвращают -1 восcтановление errno в ноль не спасает ситуацию
	// 	// https://lists.gnu.org/archive/html/coreutils/2016-03/msg00026.html
	// 	count = 0;
	// 	COMPARE("%C", (wint_t)-2);
	// 	COMPARE("%C", 0xd800);
	// 	COMPARE("%C", 0xdb02);
	// 	COMPARE("%C", 0xdfff);
	// 	COMPARE("%8C et coco %C titi %lc", 3250, 0x11ffff, 'a');
	// 	COMPARE("%6C et coco %C titi %C tyty", 3250, 0xd800, 'u');

    print_result(miss_count);
    close(fd_write);
    close(fd_read);
}