#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys_include.h"
#include "gpio_public.h"

#define GPIO_NAME_LEN       15
#define GPIO_LINE_LEN       1023

#define GPIO_NUMBER_SATA    40
#define GPIO_NUMBER_SYS     41
#define GPIO_NUMBER_RESET   44

#define GPIO_NAME_SATA      "sata"
#define GPIO_NAME_SYS       "sys"
#define GPIO_NAME_RESET     "reset"

#define GPIO_R      0x01
#define GPIO_W      0x02
#define GPIO_RW     (GPIO_R | GPIO_W)

struct gpio {
    char name[1+GPIO_NAME_LEN];
    int number;
    int flag;
};

#define GPIO_INIT(_name, _number, _flag)  {.name=_name, .number=_number, .flag=_flag}
static struct gpio GPIO[] = {
    GPIO_INIT(GPIO_NAME_SATA,   GPIO_NUMBER_SATA,   GPIO_W),
    GPIO_INIT(GPIO_NAME_SYS,    GPIO_NUMBER_SYS,    GPIO_W),
    GPIO_INIT(GPIO_NAME_RESET,  GPIO_NUMBER_RESET,  GPIO_RW),
};

#define ASIZE(x)    (sizeof(x)/sizeof((x)[0]))
#define COUNT       ASIZE(GPIO)

#define println(fmt, args...)   printf(fmt "\n", ##args)
#define dprintln println

static inline struct gpio *
getgpio_byname(char *name)
{
    int i;

    for (i=0; i<COUNT; i++) {
        if (0==strcmp(name, GPIO[i].name)) {
            return &GPIO[i];
        }
    }

    return NULL;
}

static inline int
gpio_read(struct gpio *gpio)
{
    int err = 0;
    int value = 0;
    
    if (GPIO_R != (GPIO_R & gpio->flag)) {
        println("no support read gpio %s", gpio->name);

        return -1;
    }
    
    err = read_gpio_status(gpio->number, &value);
    if (err) {
        println("read gpio %s error(%d)", gpio->name, err);

        return -1;
    }
    
    return !!value;
}

static inline int
gpio_write(struct gpio *gpio, int value)
{
    int err = 0;

    if (GPIO_W != (GPIO_W & gpio->flag)) {
        println("no support write gpio %s", gpio->name);

        return -1;
    }

    err = write_gpio_status(gpio->number, !!value);
    if (err) {
        println("write gpio %s error(%d)", gpio->name, err);

        return -1;
    }

    return 0;
}

void usage(int argc, char *argv[])
{
    println("%s ==> get all gpio", argv[0]);
    println("%s name ==> get gpio by name", argv[0]);
    println("%s name1=value1 name2=value2 ... ==> set gpio by name and value", argv[0]);
}

int main(int argc, char *argv[])
{
    int err = 0;
    int len;
    int var;
    int i;
    char *name;
    char *value;
    struct gpio *gpio;
    
    /*
    * display all
    */
    if (1==argc) {
        for (i=0; i<COUNT; i++) {
            gpio = &GPIO[i];

            if (GPIO_R & gpio->flag) {
                var = gpio_read(gpio);
                if (var<0) {
                    continue;
                }
                
                println("%s=%d", gpio->name, var);
            }
        }

        return 0;
    }
    else if (2==argc) {
        char *name = argv[1];
        /*
        * help
        */
        if (0==strcmp("-h", name) || 0==strcmp("--help", name)) {
            usage(argc, argv);
            
            return 0;
        }
        /*
        * get by name
        */
        else if (NULL==strchr(name, '=')) {
            gpio = getgpio_byname(name);
            if (NULL==gpio) {
                println("argv[1](%s) bad name", name);

                return -1;
            }
            
            var = gpio_read(gpio);
            if (var<0) {
                return -1;
            }

            println("%d", var);

            return 0;
        }
    }
    
    /*
    * set by name
    */
    for (i=1; i<argc; i++) {
        char line[1+GPIO_LINE_LEN] = {0};
        len = strlen(argv[i]);
        
        /*
        * check input length
        */
        if (len > GPIO_LINE_LEN) {
            println("argv[%d](%s) too long", i, argv[i]);

            return -1;
        }
        
        strcpy(line, argv[i]);

        /*
        * get name
        */
        name = line;
        value = strchr(line, '=');
        if (NULL==value) {
            println("argv[%d](%s) should as xxx=xxxx", i, argv[i]);

            return -1;
        }
        *value = 0; value++;
        
        /*
        * check name
        */
        gpio = getgpio_byname(name);
        if (NULL==gpio) {
            println("argv[%d](%s) bad name(%s)", i, argv[i], name);
            
            return -1;
        }
        
        /*
        * set value
        */
        err = gpio_write(gpio, atoi(value));
        if (err<0) {
            return err;
        }
    }
    
    return 0;
}

