#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "filename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char* pname)
{
    fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
    exit(EXIT_FAILURE);
}

ssize_t bulk_read(int fd, char* buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(read(fd, buf, count));
        if (c < 0)
            return c;
        if (c == 0)
            return len;  // EOF
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

ssize_t bulk_write(int fd, char* buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(write(fd, buf, count));
        if (c < 0)
            return c;
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}
int menu(int argc, char** argv)
{
    int c;

    int i = 0, remove;
    char *package, *new_env_name, **ex_env_name;

    while ((c = getopt(argc, argv, "c:v:i:r")) != -1)
    {
        switch (c)
        {
            case 'c':
                new_env_name = optarg;
                break;
            case 'v':
                ex_env_name[i++] = optarg;
                break;
            case 'i':
                package = optarg;
                break;
            case 'r':
                remove = true;
                break;
            case '?':
                fprintf(stderr, "Wrong arguments");
                exit(EXIT_FAILURE);
            default:
                continue;
        }
    }
}

//      snprintf();
//     strcpy();
//     strcat();

//      1. Funkcja memset wypełnia blok pamięci określoną wartością. Wywołanie: memset(pointer,
// value, size). Pointer to początek obszaru pamięci, value to wartość, którą ustawiamy, a size to
// liczba bajtów.

//      2. Funkcja memcpy kopiuje dane z jednego miejsca w pamięci do drugiego. Wywołanie:
// memcpy(destination, source, size). Destination to miejsce docelowe, source to dane do
// skopiowania, a size to liczba bajtów. Przykład: memcpy(manager->buffer + manager-
// >buffer_len, data, data_len).

//      3. Funkcja strstr wyszukuje pierwsze wystąpienie podłańcucha w ciągu znaków. Wywołanie:
// strstr(text, subtext). text to ciąg, w którym szukamy, a subtext to podłańcuch, który chcemy
// znaleźć. Zwraca wskaźnik do pierwszego wystąpienia podłańcucha lub NULL, jeśli nie
// znaleziono.

//      4. Funkcja strncpy_s kopiuje określoną liczbę znaków z jednego ciągu do drugiego,
// zapewniając bezpieczeństwo przed przepełnieniem bufora. Wywołanie: strncpy_s(destination,
// destsz, source, count). destination to miejsce docelowe, destsz to rozmiar bufora docelowego,
// source to źródło, a count to liczba znaków do skopiowania. Gwarantuje, że ciąg docelowy
// będzie null-terminowany.

//      5. Funkcja strlen oblicza długość ciągu znaków (liczbę znaków przed pierwszym znakiem null-
// terminującym). Wywołanie: strlen(str). Zwraca liczbę znaków w ciągu str, nie wliczając znaku
// null-terminującego.

//      6. Funkcja _countof oblicza liczbę elementów w statycznej tablicy. Wywołanie: _countof(array).
// array to statyczna tablica, której liczba elementów jest obliczana. Funkcja jest przydatna do
// określenia limitów operacji na tablicach, takich jak kopiowanie danych, aby uniknąć
// przepełnienia bufora.

// 7. Funkcja snprintf pozwala na zapisanie sformatowanego tekstu, zamiast wyświetlania go na
// konsoli, do zmiennej. Na przykład, zamiast używać `printf` do wypisania tekstu, możesz
// zapisać go do bufora, co pozwala na dalsze przetwarzanie lub przekazywanie tego tekstu w
// programie.
