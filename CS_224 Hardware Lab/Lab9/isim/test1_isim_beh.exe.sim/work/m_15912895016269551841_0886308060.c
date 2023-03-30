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
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab9/ALU.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {3U, 0U};
static unsigned int ng6[] = {4U, 0U};
static unsigned int ng7[] = {5U, 0U};
static unsigned int ng8[] = {6U, 0U};
static unsigned int ng9[] = {7U, 0U};



static void Always_11_0(char *t0)
{
    char t6[8];
    char t31[8];
    char t41[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    int t30;
    int t32;
    int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;

LAB0:    t1 = (t0 + 3160U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(11, ng0);
    t2 = (t0 + 3480);
    *((int *)t2) = 1;
    t3 = (t0 + 3192);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(12, ng0);

LAB5:    xsi_set_current_line(13, ng0);
    t4 = (t0 + 1688U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(13, ng0);

LAB13:    xsi_set_current_line(14, ng0);
    t28 = ((char*)((ng2)));
    t29 = (t0 + 2248);
    xsi_vlogvar_assign_value(t29, t28, 0, 0, 1);
    xsi_set_current_line(15, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);

LAB14:    t2 = ((char*)((ng2)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng3)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng4)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng5)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng6)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng7)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng8)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng9)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 3, t2, 3);
    if (t30 == 1)
        goto LAB29;

LAB30:
LAB31:    goto LAB12;

LAB15:    xsi_set_current_line(16, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 9, t5, 8, t7, 8);
    t4 = (t0 + 1528U);
    t8 = *((char **)t4);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_add(t31, 9, t6, 9, t8, 1);
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t31, 0, 0, 8);
    t21 = (t0 + 2248);
    xsi_vlogvar_assign_value(t21, t31, 8, 0, 1);
    goto LAB31;

LAB17:    xsi_set_current_line(17, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 9, t5, 8, t7, 8);
    t4 = (t0 + 1528U);
    t8 = *((char **)t4);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_minus(t31, 9, t6, 9, t8, 1);
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t31, 0, 0, 8);
    t21 = (t0 + 2248);
    xsi_vlogvar_assign_value(t21, t31, 8, 0, 1);
    goto LAB31;

LAB19:    xsi_set_current_line(18, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t7);
    t11 = (t9 | t10);
    *((unsigned int *)t6) = t11;
    t4 = (t5 + 4);
    t8 = (t7 + 4);
    t21 = (t6 + 4);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t8);
    t14 = (t12 | t13);
    *((unsigned int *)t21) = t14;
    t15 = *((unsigned int *)t21);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB32;

LAB33:
LAB34:    t29 = (t0 + 2088);
    xsi_vlogvar_assign_value(t29, t6, 0, 0, 8);
    goto LAB31;

LAB21:    xsi_set_current_line(19, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1208U);
    t7 = *((char **)t4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t7);
    t11 = (t9 & t10);
    *((unsigned int *)t6) = t11;
    t4 = (t5 + 4);
    t8 = (t7 + 4);
    t21 = (t6 + 4);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t8);
    t14 = (t12 | t13);
    *((unsigned int *)t21) = t14;
    t15 = *((unsigned int *)t21);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB35;

LAB36:
LAB37:    t29 = (t0 + 2088);
    xsi_vlogvar_assign_value(t29, t6, 0, 0, 8);
    goto LAB31;

LAB23:    xsi_set_current_line(20, ng0);
    t4 = ((char*)((ng2)));
    t5 = (t0 + 1048U);
    t7 = *((char **)t5);
    memset(t31, 0, 8);
    t5 = (t31 + 4);
    t8 = (t7 + 4);
    t9 = *((unsigned int *)t7);
    t10 = (t9 >> 0);
    *((unsigned int *)t31) = t10;
    t11 = *((unsigned int *)t8);
    t12 = (t11 >> 0);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t13 & 127U);
    t14 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t14 & 127U);
    xsi_vlogtype_concat(t6, 8, 8, 2U, t31, 7, t4, 1);
    t21 = (t0 + 2088);
    xsi_vlogvar_assign_value(t21, t6, 0, 0, 8);
    goto LAB31;

LAB25:    xsi_set_current_line(21, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t31, 0, 8);
    t4 = (t31 + 4);
    t7 = (t5 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (t9 >> 1);
    *((unsigned int *)t31) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 1);
    *((unsigned int *)t4) = t12;
    t13 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t13 & 127U);
    t14 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t14 & 127U);
    t8 = ((char*)((ng2)));
    xsi_vlogtype_concat(t6, 8, 8, 2U, t8, 1, t31, 7);
    t21 = (t0 + 2088);
    xsi_vlogvar_assign_value(t21, t6, 0, 0, 8);
    goto LAB31;

LAB27:    xsi_set_current_line(22, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t31, 0, 8);
    t4 = (t31 + 4);
    t7 = (t5 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (t9 >> 7);
    t11 = (t10 & 1);
    *((unsigned int *)t31) = t11;
    t12 = *((unsigned int *)t7);
    t13 = (t12 >> 7);
    t14 = (t13 & 1);
    *((unsigned int *)t4) = t14;
    t8 = (t0 + 1048U);
    t21 = *((char **)t8);
    memset(t41, 0, 8);
    t8 = (t41 + 4);
    t22 = (t21 + 4);
    t15 = *((unsigned int *)t21);
    t16 = (t15 >> 0);
    *((unsigned int *)t41) = t16;
    t17 = *((unsigned int *)t22);
    t18 = (t17 >> 0);
    *((unsigned int *)t8) = t18;
    t19 = *((unsigned int *)t41);
    *((unsigned int *)t41) = (t19 & 127U);
    t20 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t20 & 127U);
    xsi_vlogtype_concat(t6, 8, 8, 2U, t41, 7, t31, 1);
    t28 = (t0 + 2088);
    xsi_vlogvar_assign_value(t28, t6, 0, 0, 8);
    goto LAB31;

LAB29:    xsi_set_current_line(23, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    memset(t31, 0, 8);
    t4 = (t31 + 4);
    t7 = (t5 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (t9 >> 1);
    *((unsigned int *)t31) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 1);
    *((unsigned int *)t4) = t12;
    t13 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t13 & 127U);
    t14 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t14 & 127U);
    t8 = (t0 + 1048U);
    t21 = *((char **)t8);
    memset(t41, 0, 8);
    t8 = (t41 + 4);
    t22 = (t21 + 4);
    t15 = *((unsigned int *)t21);
    t16 = (t15 >> 0);
    t17 = (t16 & 1);
    *((unsigned int *)t41) = t17;
    t18 = *((unsigned int *)t22);
    t19 = (t18 >> 0);
    t20 = (t19 & 1);
    *((unsigned int *)t8) = t20;
    xsi_vlogtype_concat(t6, 8, 8, 2U, t41, 1, t31, 7);
    t28 = (t0 + 2088);
    xsi_vlogvar_assign_value(t28, t6, 0, 0, 8);
    goto LAB31;

LAB32:    t17 = *((unsigned int *)t6);
    t18 = *((unsigned int *)t21);
    *((unsigned int *)t6) = (t17 | t18);
    t22 = (t5 + 4);
    t28 = (t7 + 4);
    t19 = *((unsigned int *)t22);
    t20 = (~(t19));
    t23 = *((unsigned int *)t5);
    t32 = (t23 & t20);
    t24 = *((unsigned int *)t28);
    t25 = (~(t24));
    t26 = *((unsigned int *)t7);
    t33 = (t26 & t25);
    t27 = (~(t32));
    t34 = (~(t33));
    t35 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t35 & t27);
    t36 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t36 & t34);
    goto LAB34;

LAB35:    t17 = *((unsigned int *)t6);
    t18 = *((unsigned int *)t21);
    *((unsigned int *)t6) = (t17 | t18);
    t22 = (t5 + 4);
    t28 = (t7 + 4);
    t19 = *((unsigned int *)t5);
    t20 = (~(t19));
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t7);
    t26 = (~(t25));
    t27 = *((unsigned int *)t28);
    t34 = (~(t27));
    t32 = (t20 & t24);
    t33 = (t26 & t34);
    t35 = (~(t32));
    t36 = (~(t33));
    t37 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t37 & t35);
    t38 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t38 & t36);
    t39 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t39 & t35);
    t40 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t40 & t36);
    goto LAB37;

}


extern void work_m_15912895016269551841_0886308060_init()
{
	static char *pe[] = {(void *)Always_11_0};
	xsi_register_didat("work_m_15912895016269551841_0886308060", "isim/test1_isim_beh.exe.sim/work/m_15912895016269551841_0886308060.didat");
	xsi_register_executes(pe);
}
