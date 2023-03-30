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

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab3/ALU.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {3U, 0U};
static unsigned int ng5[] = {4U, 0U};
static unsigned int ng6[] = {5U, 0U};
static unsigned int ng7[] = {6U, 0U};
static unsigned int ng8[] = {7U, 0U};



static void Always_11_0(char *t0)
{
    char t8[8];
    char t10[8];
    char t41[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t9;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;

LAB0:    t1 = (t0 + 3000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(11, ng0);
    t2 = (t0 + 3320);
    *((int *)t2) = 1;
    t3 = (t0 + 3032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(12, ng0);

LAB5:    xsi_set_current_line(13, ng0);
    t4 = ((char*)((ng1)));
    t5 = (t0 + 2088);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(14, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);

LAB6:    t2 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng8)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t6 == 1)
        goto LAB21;

LAB22:
LAB23:    goto LAB2;

LAB7:    xsi_set_current_line(15, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    memset(t8, 0, 8);
    xsi_vlog_unsigned_add(t8, 5, t5, 4, t7, 4);
    t4 = (t0 + 1528U);
    t9 = *((char **)t4);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_add(t10, 5, t8, 5, t9, 1);
    t4 = (t0 + 1928);
    xsi_vlogvar_assign_value(t4, t10, 0, 0, 4);
    t11 = (t0 + 2088);
    xsi_vlogvar_assign_value(t11, t10, 4, 0, 1);
    goto LAB23;

LAB9:    xsi_set_current_line(16, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    memset(t8, 0, 8);
    xsi_vlog_unsigned_minus(t8, 5, t5, 4, t7, 4);
    t4 = (t0 + 1528U);
    t9 = *((char **)t4);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_minus(t10, 5, t8, 5, t9, 1);
    t4 = (t0 + 1928);
    xsi_vlogvar_assign_value(t4, t10, 0, 0, 4);
    t11 = (t0 + 2088);
    xsi_vlogvar_assign_value(t11, t10, 4, 0, 1);
    goto LAB23;

LAB11:    xsi_set_current_line(17, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    t12 = *((unsigned int *)t5);
    t13 = *((unsigned int *)t7);
    t14 = (t12 | t13);
    *((unsigned int *)t8) = t14;
    t4 = (t5 + 4);
    t9 = (t7 + 4);
    t11 = (t8 + 4);
    t15 = *((unsigned int *)t4);
    t16 = *((unsigned int *)t9);
    t17 = (t15 | t16);
    *((unsigned int *)t11) = t17;
    t18 = *((unsigned int *)t11);
    t19 = (t18 != 0);
    if (t19 == 1)
        goto LAB24;

LAB25:
LAB26:    t36 = (t0 + 1928);
    xsi_vlogvar_assign_value(t36, t8, 0, 0, 4);
    goto LAB23;

LAB13:    xsi_set_current_line(18, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    t12 = *((unsigned int *)t5);
    t13 = *((unsigned int *)t7);
    t14 = (t12 & t13);
    *((unsigned int *)t8) = t14;
    t4 = (t5 + 4);
    t9 = (t7 + 4);
    t11 = (t8 + 4);
    t15 = *((unsigned int *)t4);
    t16 = *((unsigned int *)t9);
    t17 = (t15 | t16);
    *((unsigned int *)t11) = t17;
    t18 = *((unsigned int *)t11);
    t19 = (t18 != 0);
    if (t19 == 1)
        goto LAB27;

LAB28:
LAB29:    t36 = (t0 + 1928);
    xsi_vlogvar_assign_value(t36, t8, 0, 0, 4);
    goto LAB23;

LAB15:    xsi_set_current_line(19, ng0);
    t4 = ((char*)((ng1)));
    t5 = (t0 + 1048U);
    t7 = *((char **)t5);
    memset(t10, 0, 8);
    t5 = (t10 + 4);
    t9 = (t7 + 4);
    t12 = *((unsigned int *)t7);
    t13 = (t12 >> 0);
    *((unsigned int *)t10) = t13;
    t14 = *((unsigned int *)t9);
    t15 = (t14 >> 0);
    *((unsigned int *)t5) = t15;
    t16 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t16 & 7U);
    t17 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t17 & 7U);
    xsi_vlogtype_concat(t8, 4, 4, 2U, t10, 3, t4, 1);
    t11 = (t0 + 1928);
    xsi_vlogvar_assign_value(t11, t8, 0, 0, 4);
    goto LAB23;

LAB17:    xsi_set_current_line(20, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t10, 0, 8);
    t4 = (t10 + 4);
    t7 = (t5 + 4);
    t12 = *((unsigned int *)t5);
    t13 = (t12 >> 1);
    *((unsigned int *)t10) = t13;
    t14 = *((unsigned int *)t7);
    t15 = (t14 >> 1);
    *((unsigned int *)t4) = t15;
    t16 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t16 & 7U);
    t17 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t17 & 7U);
    t9 = ((char*)((ng1)));
    xsi_vlogtype_concat(t8, 4, 4, 2U, t9, 1, t10, 3);
    t11 = (t0 + 1928);
    xsi_vlogvar_assign_value(t11, t8, 0, 0, 4);
    goto LAB23;

LAB19:    xsi_set_current_line(21, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t10, 0, 8);
    t4 = (t10 + 4);
    t7 = (t5 + 4);
    t12 = *((unsigned int *)t5);
    t13 = (t12 >> 3);
    t14 = (t13 & 1);
    *((unsigned int *)t10) = t14;
    t15 = *((unsigned int *)t7);
    t16 = (t15 >> 3);
    t17 = (t16 & 1);
    *((unsigned int *)t4) = t17;
    t9 = (t0 + 1048U);
    t11 = *((char **)t9);
    memset(t41, 0, 8);
    t9 = (t41 + 4);
    t22 = (t11 + 4);
    t18 = *((unsigned int *)t11);
    t19 = (t18 >> 0);
    *((unsigned int *)t41) = t19;
    t20 = *((unsigned int *)t22);
    t21 = (t20 >> 0);
    *((unsigned int *)t9) = t21;
    t24 = *((unsigned int *)t41);
    *((unsigned int *)t41) = (t24 & 7U);
    t25 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t25 & 7U);
    xsi_vlogtype_concat(t8, 4, 4, 2U, t41, 3, t10, 1);
    t23 = (t0 + 1928);
    xsi_vlogvar_assign_value(t23, t8, 0, 0, 4);
    goto LAB23;

LAB21:    xsi_set_current_line(22, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t10, 0, 8);
    t4 = (t10 + 4);
    t7 = (t5 + 4);
    t12 = *((unsigned int *)t5);
    t13 = (t12 >> 1);
    *((unsigned int *)t10) = t13;
    t14 = *((unsigned int *)t7);
    t15 = (t14 >> 1);
    *((unsigned int *)t4) = t15;
    t16 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t16 & 7U);
    t17 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t17 & 7U);
    t9 = (t0 + 1048U);
    t11 = *((char **)t9);
    memset(t41, 0, 8);
    t9 = (t41 + 4);
    t22 = (t11 + 4);
    t18 = *((unsigned int *)t11);
    t19 = (t18 >> 0);
    t20 = (t19 & 1);
    *((unsigned int *)t41) = t20;
    t21 = *((unsigned int *)t22);
    t24 = (t21 >> 0);
    t25 = (t24 & 1);
    *((unsigned int *)t9) = t25;
    xsi_vlogtype_concat(t8, 4, 4, 2U, t41, 1, t10, 3);
    t23 = (t0 + 1928);
    xsi_vlogvar_assign_value(t23, t8, 0, 0, 4);
    goto LAB23;

LAB24:    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t11);
    *((unsigned int *)t8) = (t20 | t21);
    t22 = (t5 + 4);
    t23 = (t7 + 4);
    t24 = *((unsigned int *)t22);
    t25 = (~(t24));
    t26 = *((unsigned int *)t5);
    t27 = (t26 & t25);
    t28 = *((unsigned int *)t23);
    t29 = (~(t28));
    t30 = *((unsigned int *)t7);
    t31 = (t30 & t29);
    t32 = (~(t27));
    t33 = (~(t31));
    t34 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t34 & t32);
    t35 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t35 & t33);
    goto LAB26;

LAB27:    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t11);
    *((unsigned int *)t8) = (t20 | t21);
    t22 = (t5 + 4);
    t23 = (t7 + 4);
    t24 = *((unsigned int *)t5);
    t25 = (~(t24));
    t26 = *((unsigned int *)t22);
    t28 = (~(t26));
    t29 = *((unsigned int *)t7);
    t30 = (~(t29));
    t32 = *((unsigned int *)t23);
    t33 = (~(t32));
    t27 = (t25 & t28);
    t31 = (t30 & t33);
    t34 = (~(t27));
    t35 = (~(t31));
    t37 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t37 & t34);
    t38 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t38 & t35);
    t39 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t39 & t34);
    t40 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t40 & t35);
    goto LAB29;

}


extern void work_m_15739607883473090421_0886308060_init()
{
	static char *pe[] = {(void *)Always_11_0};
	xsi_register_didat("work_m_15739607883473090421_0886308060", "isim/test_3_isim_beh.exe.sim/work/m_15739607883473090421_0886308060.didat");
	xsi_register_executes(pe);
}
