#include "sys_include.h"
#include "gpio_public.h"

static int bSharp = 1;
static int gpio40_value = 0;
static int gpio41_value = 0;
static int gpio44_value = 0;
static struct timeval record_tm;
static struct timeval gpio_force_exit_tm;
static int bgpio_quit = 0;

int init_gpio_borad(void)
{

    //read_gpio_status(44, &gpio44_value);
    write_gpio_status(44, &gpio44_value);

    write_gpio_status(40, gpio40_value);
    write_gpio_status(41, gpio41_value);

    gettimeofday(&(record_tm), NULL);
    gettimeofday(&(gpio_force_exit_tm), NULL);

    return 0;
}

int get_force_exit_gpio(void)
{
    return bgpio_quit;
}

int gpio_sharp_filter(void)
{
    static struct timeval cur_tm;
    unsigned int distms = 0;
    int ret;

    gettimeofday(&cur_tm, NULL);

    if (bgpio_quit == 0)
    {
        distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(gpio_force_exit_tm.tv_sec*1000+(gpio_force_exit_tm.tv_usec)/1000));
        if (distms >= 90*1000)
        {
            bgpio_quit = 1;
        }
    }

    distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(record_tm.tv_sec*1000+(record_tm.tv_usec)/1000));
    if (distms >= 200)
    {
        if (bSharp)
        {
            write_gpio_status(40, gpio40_value);
            write_gpio_status(41, gpio41_value);

            //M_TRACE(DEBUG_TRACE, SYS_MODE, "gpio40 = %d, gpio41 = %d\n", gpio40_value, gpio41_value);
            if (gpio40_value == 0)
            {
                gpio40_value = 1;
            }
            else
            {
                gpio40_value = 0;
            }

            if (gpio41_value == 0)
            {
                gpio41_value = 1;
            }
            else
            {
                gpio41_value = 0;
            }

        }

        record_tm = cur_tm;
        return 1;
    }

    ret = read_gpio_status(44, &gpio44_value);
    //if (ret)
    {
        if (gpio44_value == 0)
        {
            //printf("\ngpio test finish\n");
            set_test_status(gpio_test);
            bSharp = 0;
        }
        else
        {
            bSharp = 1;
        }
    }

    return 0;
}


