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
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab4/register_4bit_inc.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};



static void Always_8_0(char *t0)
{
    char t4[8];
    char t5[8];
    char t23[8];
    char t24[8];
    char t39[8];
    char t44[8];
    char t45[8];
    char t61[8];
    char t69[8];
    char *t1;
    char *t2;
    char *t3;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    char *t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    char *t38;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    char *t52;
    char *t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    char *t57;
    char *t58;
    char *t59;
    char *t60;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    char *t66;
    char *t67;
    char *t68;
    char *t70;

LAB0:    t1 = (t0 + 3000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(8, ng0);
    t2 = (t0 + 3320);
    *((int *)t2) = 1;
    t3 = (t0 + 3032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(9, ng0);

LAB5:    xsi_set_current_line(10, ng0);
    t6 = (t0 + 1368U);
    t7 = *((char **)t6);
    memset(t5, 0, 8);
    t6 = (t7 + 4);
    t8 = *((unsigned int *)t6);
    t9 = (~(t8));
    t10 = *((unsigned int *)t7);
    t11 = (t10 & t9);
    t12 = (t11 & 1U);
    if (t12 != 0)
        goto LAB6;

LAB7:    if (*((unsigned int *)t6) != 0)
        goto LAB8;

LAB9:    t14 = (t5 + 4);
    t15 = *((unsigned int *)t5);
    t16 = *((unsigned int *)t14);
    t17 = (t15 || t16);
    if (t17 > 0)
        goto LAB10;

LAB11:    t19 = *((unsigned int *)t5);
    t20 = (~(t19));
    t21 = *((unsigned int *)t14);
    t22 = (t20 || t21);
    if (t22 > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t14) > 0)
        goto LAB14;

LAB15:    if (*((unsigned int *)t5) > 0)
        goto LAB16;

LAB17:    memcpy(t4, t23, 8);

LAB18:    t70 = (t0 + 2088);
    xsi_vlogvar_assign_value(t70, t4, 0, 0, 4);
    goto LAB2;

LAB6:    *((unsigned int *)t5) = 1;
    goto LAB9;

LAB8:    t13 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t13) = 1;
    goto LAB9;

LAB10:    t18 = ((char*)((ng1)));
    goto LAB11;

LAB12:    t25 = (t0 + 1208U);
    t26 = *((char **)t25);
    memset(t24, 0, 8);
    t25 = (t26 + 4);
    t27 = *((unsigned int *)t25);
    t28 = (~(t27));
    t29 = *((unsigned int *)t26);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB19;

LAB20:    if (*((unsigned int *)t25) != 0)
        goto LAB21;

LAB22:    t33 = (t24 + 4);
    t34 = *((unsigned int *)t24);
    t35 = *((unsigned int *)t33);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB23;

LAB24:    t40 = *((unsigned int *)t24);
    t41 = (~(t40));
    t42 = *((unsigned int *)t33);
    t43 = (t41 || t42);
    if (t43 > 0)
        goto LAB25;

LAB26:    if (*((unsigned int *)t33) > 0)
        goto LAB27;

LAB28:    if (*((unsigned int *)t24) > 0)
        goto LAB29;

LAB30:    memcpy(t23, t44, 8);

LAB31:    goto LAB13;

LAB14:    xsi_vlog_unsigned_bit_combine(t4, 32, t18, 32, t23, 32);
    goto LAB18;

LAB16:    memcpy(t4, t18, 8);
    goto LAB18;

LAB19:    *((unsigned int *)t24) = 1;
    goto LAB22;

LAB21:    t32 = (t24 + 4);
    *((unsigned int *)t24) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB22;

LAB23:    t37 = (t0 + 1688U);
    t38 = *((char **)t37);
    memcpy(t39, t38, 8);
    goto LAB24;

LAB25:    t37 = (t0 + 1528U);
    t46 = *((char **)t37);
    memset(t45, 0, 8);
    t37 = (t46 + 4);
    t47 = *((unsigned int *)t37);
    t48 = (~(t47));
    t49 = *((unsigned int *)t46);
    t50 = (t49 & t48);
    t51 = (t50 & 1U);
    if (t51 != 0)
        goto LAB32;

LAB33:    if (*((unsigned int *)t37) != 0)
        goto LAB34;

LAB35:    t53 = (t45 + 4);
    t54 = *((unsigned int *)t45);
    t55 = *((unsigned int *)t53);
    t56 = (t54 || t55);
    if (t56 > 0)
        goto LAB36;

LAB37:    t62 = *((unsigned int *)t45);
    t63 = (~(t62));
    t64 = *((unsigned int *)t53);
    t65 = (t63 || t64);
    if (t65 > 0)
        goto LAB38;

LAB39:    if (*((unsigned int *)t53) > 0)
        goto LAB40;

LAB41:    if (*((unsigned int *)t45) > 0)
        goto LAB42;

LAB43:    memcpy(t44, t69, 8);

LAB44:    goto LAB26;

LAB27:    xsi_vlog_unsigned_bit_combine(t23, 32, t39, 32, t44, 32);
    goto LAB31;

LAB29:    memcpy(t23, t39, 8);
    goto LAB31;

LAB32:    *((unsigned int *)t45) = 1;
    goto LAB35;

LAB34:    t52 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t52) = 1;
    goto LAB35;

LAB36:    t57 = (t0 + 2088);
    t58 = (t57 + 56U);
    t59 = *((char **)t58);
    t60 = ((char*)((ng2)));
    memset(t61, 0, 8);
    xsi_vlog_unsigned_add(t61, 32, t59, 4, t60, 32);
    goto LAB37;

LAB38:    t66 = (t0 + 2088);
    t67 = (t66 + 56U);
    t68 = *((char **)t67);
    memcpy(t69, t68, 8);
    goto LAB39;

LAB40:    xsi_vlog_unsigned_bit_combine(t44, 32, t61, 32, t69, 32);
    goto LAB44;

LAB42:    memcpy(t44, t61, 8);
    goto LAB44;

}


extern void work_m_12627006756583135726_0064990324_init()
{
	static char *pe[] = {(void *)Always_8_0};
	xsi_register_didat("work_m_12627006756583135726_0064990324", "isim/test3_isim_beh.exe.sim/work/m_12627006756583135726_0064990324.didat");
	xsi_register_executes(pe);
}