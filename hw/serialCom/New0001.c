#include "sys_include.h"

#define use_ir_dev_num 4
#define ir_filter_num 10

typedef struct {
    int circle;
    int start_tm;
    int end_tm;
}ir_report_item;

static ir_report_item ir_report[use_ir_dev_num][ir_filter_num];

int init_ir_report_filter_module(void)
{
    int i, j;

    for (i = 0; i < use_ir_dev_num; i++)
    {
        for (j = 0; j < ir_filter_num; j++)
        {

            ir_report[i][j].start_tm = 0;
            ir_report[i][j].end_tm = 0;
            ir_report[i][j].circle = 0;
        }

    }

    return 1;
}

void config_ir_report(int circle, int start_tm, int end_tm, int index)
{


}

