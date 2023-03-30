/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_11776451211234093749_1478632937_init();
    work_m_11385613784037778305_3866583278_init();
    work_m_15912895016269551841_0886308060_init();
    work_m_14445525051671594774_0295930199_init();
    work_m_10125002929297041455_2221974671_init();
    work_m_16541823861846354283_2073120511_init();


    xsi_register_tops("work_m_10125002929297041455_2221974671");
    xsi_register_tops("work_m_16541823861846354283_2073120511");


    return xsi_run_simulation(argc, argv);

}
