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
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab7/asm_2.v";
static unsigned int ng1[] = {4U, 0U};
static int ng2[] = {1, 0};
static int ng3[] = {0, 0};
static unsigned int ng4[] = {7U, 0U};
static unsigned int ng5[] = {0U, 0U};
static unsigned int ng6[] = {1U, 0U};
static unsigned int ng7[] = {2U, 0U};
static unsigned int ng8[] = {3U, 0U};
static unsigned int ng9[] = {5U, 0U};
static unsigned int ng10[] = {6U, 0U};



static void Always_14_0(char *t0)
{
    char t4[8];
    char t5[8];
    char t10[8];
    char *t1;
    char *t2;
    char *t3;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
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
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t43;

LAB0:    t1 = (t0 + 3800U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(14, ng0);
    t2 = (t0 + 4864);
    *((int *)t2) = 1;
    t3 = (t0 + 3832);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(15, ng0);

LAB5:    xsi_set_current_line(16, ng0);
    t6 = (t0 + 2568);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = ((char*)((ng1)));
    memset(t10, 0, 8);
    t11 = (t8 + 4);
    t12 = (t9 + 4);
    t13 = *((unsigned int *)t8);
    t14 = *((unsigned int *)t9);
    t15 = (t13 ^ t14);
    t16 = *((unsigned int *)t11);
    t17 = *((unsigned int *)t12);
    t18 = (t16 ^ t17);
    t19 = (t15 | t18);
    t20 = *((unsigned int *)t11);
    t21 = *((unsigned int *)t12);
    t22 = (t20 | t21);
    t23 = (~(t22));
    t24 = (t19 & t23);
    if (t24 != 0)
        goto LAB9;

LAB6:    if (t22 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t10) = 1;

LAB9:    memset(t5, 0, 8);
    t26 = (t10 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (~(t27));
    t29 = *((unsigned int *)t10);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t26) != 0)
        goto LAB12;

LAB13:    t33 = (t5 + 4);
    t34 = *((unsigned int *)t5);
    t35 = *((unsigned int *)t33);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB14;

LAB15:    t38 = *((unsigned int *)t5);
    t39 = (~(t38));
    t40 = *((unsigned int *)t33);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB16;

LAB17:    if (*((unsigned int *)t33) > 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t5) > 0)
        goto LAB20;

LAB21:    memcpy(t4, t42, 8);

LAB22:    t43 = (t0 + 2888);
    xsi_vlogvar_assign_value(t43, t4, 0, 0, 1);
    xsi_set_current_line(17, ng0);
    t2 = (t0 + 2408);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);
    t7 = ((char*)((ng4)));
    memset(t10, 0, 8);
    t8 = (t6 + 4);
    t9 = (t7 + 4);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t7);
    t15 = (t13 ^ t14);
    t16 = *((unsigned int *)t8);
    t17 = *((unsigned int *)t9);
    t18 = (t16 ^ t17);
    t19 = (t15 | t18);
    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t9);
    t22 = (t20 | t21);
    t23 = (~(t22));
    t24 = (t19 & t23);
    if (t24 != 0)
        goto LAB26;

LAB23:    if (t22 != 0)
        goto LAB25;

LAB24:    *((unsigned int *)t10) = 1;

LAB26:    memset(t5, 0, 8);
    t12 = (t10 + 4);
    t27 = *((unsigned int *)t12);
    t28 = (~(t27));
    t29 = *((unsigned int *)t10);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB27;

LAB28:    if (*((unsigned int *)t12) != 0)
        goto LAB29;

LAB30:    t26 = (t5 + 4);
    t34 = *((unsigned int *)t5);
    t35 = *((unsigned int *)t26);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB31;

LAB32:    t38 = *((unsigned int *)t5);
    t39 = (~(t38));
    t40 = *((unsigned int *)t26);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB33;

LAB34:    if (*((unsigned int *)t26) > 0)
        goto LAB35;

LAB36:    if (*((unsigned int *)t5) > 0)
        goto LAB37;

LAB38:    memcpy(t4, t33, 8);

LAB39:    t37 = (t0 + 2248);
    xsi_vlogvar_assign_value(t37, t4, 0, 0, 1);
    goto LAB2;

LAB8:    t25 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t25) = 1;
    goto LAB9;

LAB10:    *((unsigned int *)t5) = 1;
    goto LAB13;

LAB12:    t32 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB13;

LAB14:    t37 = ((char*)((ng2)));
    goto LAB15;

LAB16:    t42 = ((char*)((ng3)));
    goto LAB17;

LAB18:    xsi_vlog_unsigned_bit_combine(t4, 32, t37, 32, t42, 32);
    goto LAB22;

LAB20:    memcpy(t4, t37, 8);
    goto LAB22;

LAB25:    t11 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB26;

LAB27:    *((unsigned int *)t5) = 1;
    goto LAB30;

LAB29:    t25 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t25) = 1;
    goto LAB30;

LAB31:    t32 = ((char*)((ng2)));
    goto LAB32;

LAB33:    t33 = ((char*)((ng3)));
    goto LAB34;

LAB35:    xsi_vlog_unsigned_bit_combine(t4, 32, t32, 32, t33, 32);
    goto LAB39;

LAB37:    memcpy(t4, t32, 8);
    goto LAB39;

}

static void Always_20_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;

LAB0:    t1 = (t0 + 4048U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(20, ng0);
    t2 = (t0 + 4880);
    *((int *)t2) = 1;
    t3 = (t0 + 4080);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(21, ng0);

LAB5:    xsi_set_current_line(22, ng0);
    t4 = (t0 + 1528U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(23, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2408);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 3);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(22, ng0);
    t11 = ((char*)((ng5)));
    t12 = (t0 + 2408);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 3);
    goto LAB8;

}

static void Always_26_2(char *t0)
{
    char t9[8];
    char t10[8];
    char t13[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    char *t11;
    char *t12;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t45;
    char *t46;

LAB0:    t1 = (t0 + 4296U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 4896);
    *((int *)t2) = 1;
    t3 = (t0 + 4328);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(27, ng0);

LAB5:    xsi_set_current_line(28, ng0);
    t4 = (t0 + 2408);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);

LAB6:    t7 = ((char*)((ng5)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t7, 3);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng8)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng1)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng10)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB21;

LAB22:
LAB23:    goto LAB2;

LAB7:    xsi_set_current_line(29, ng0);
    t11 = (t0 + 1688U);
    t12 = *((char **)t11);
    t11 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t14 = (t12 + 4);
    t15 = (t11 + 4);
    t16 = *((unsigned int *)t12);
    t17 = *((unsigned int *)t11);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t14);
    t24 = *((unsigned int *)t15);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB27;

LAB24:    if (t25 != 0)
        goto LAB26;

LAB25:    *((unsigned int *)t13) = 1;

LAB27:    memset(t10, 0, 8);
    t29 = (t13 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB28;

LAB29:    if (*((unsigned int *)t29) != 0)
        goto LAB30;

LAB31:    t36 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t36);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB32;

LAB33:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t36);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB34;

LAB35:    if (*((unsigned int *)t36) > 0)
        goto LAB36;

LAB37:    if (*((unsigned int *)t10) > 0)
        goto LAB38;

LAB39:    memcpy(t9, t45, 8);

LAB40:    t46 = (t0 + 2728);
    xsi_vlogvar_assign_value(t46, t9, 0, 0, 3);
    goto LAB23;

LAB9:    xsi_set_current_line(30, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB23;

LAB11:    xsi_set_current_line(31, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB23;

LAB13:    xsi_set_current_line(32, ng0);
    t3 = (t0 + 2888);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng3)));
    memset(t13, 0, 8);
    t11 = (t5 + 4);
    t12 = (t7 + 4);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t7);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t11);
    t20 = *((unsigned int *)t12);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t11);
    t24 = *((unsigned int *)t12);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB44;

LAB41:    if (t25 != 0)
        goto LAB43;

LAB42:    *((unsigned int *)t13) = 1;

LAB44:    memset(t10, 0, 8);
    t15 = (t13 + 4);
    t30 = *((unsigned int *)t15);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB45;

LAB46:    if (*((unsigned int *)t15) != 0)
        goto LAB47;

LAB48:    t29 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t29);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB49;

LAB50:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t29);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB51;

LAB52:    if (*((unsigned int *)t29) > 0)
        goto LAB53;

LAB54:    if (*((unsigned int *)t10) > 0)
        goto LAB55;

LAB56:    memcpy(t9, t36, 8);

LAB57:    t40 = (t0 + 2728);
    xsi_vlogvar_assign_value(t40, t9, 0, 0, 3);
    goto LAB23;

LAB15:    xsi_set_current_line(33, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB23;

LAB17:    xsi_set_current_line(34, ng0);
    t3 = (t0 + 2888);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng3)));
    memset(t13, 0, 8);
    t11 = (t5 + 4);
    t12 = (t7 + 4);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t7);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t11);
    t20 = *((unsigned int *)t12);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t11);
    t24 = *((unsigned int *)t12);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB61;

LAB58:    if (t25 != 0)
        goto LAB60;

LAB59:    *((unsigned int *)t13) = 1;

LAB61:    memset(t10, 0, 8);
    t15 = (t13 + 4);
    t30 = *((unsigned int *)t15);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB62;

LAB63:    if (*((unsigned int *)t15) != 0)
        goto LAB64;

LAB65:    t29 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t29);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB66;

LAB67:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t29);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB68;

LAB69:    if (*((unsigned int *)t29) > 0)
        goto LAB70;

LAB71:    if (*((unsigned int *)t10) > 0)
        goto LAB72;

LAB73:    memcpy(t9, t36, 8);

LAB74:    t40 = (t0 + 2728);
    xsi_vlogvar_assign_value(t40, t9, 0, 0, 3);
    goto LAB23;

LAB19:    xsi_set_current_line(35, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB23;

LAB21:    xsi_set_current_line(36, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB23;

LAB26:    t28 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB27;

LAB28:    *((unsigned int *)t10) = 1;
    goto LAB31;

LAB30:    t35 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t35) = 1;
    goto LAB31;

LAB32:    t40 = ((char*)((ng6)));
    goto LAB33;

LAB34:    t45 = ((char*)((ng5)));
    goto LAB35;

LAB36:    xsi_vlog_unsigned_bit_combine(t9, 3, t40, 3, t45, 3);
    goto LAB40;

LAB38:    memcpy(t9, t40, 8);
    goto LAB40;

LAB43:    t14 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB44;

LAB45:    *((unsigned int *)t10) = 1;
    goto LAB48;

LAB47:    t28 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB48;

LAB49:    t35 = ((char*)((ng1)));
    goto LAB50;

LAB51:    t36 = ((char*)((ng4)));
    goto LAB52;

LAB53:    xsi_vlog_unsigned_bit_combine(t9, 3, t35, 3, t36, 3);
    goto LAB57;

LAB55:    memcpy(t9, t35, 8);
    goto LAB57;

LAB60:    t14 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB61;

LAB62:    *((unsigned int *)t10) = 1;
    goto LAB65;

LAB64:    t28 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB65;

LAB66:    t35 = ((char*)((ng10)));
    goto LAB67;

LAB68:    t36 = ((char*)((ng4)));
    goto LAB69;

LAB70:    xsi_vlog_unsigned_bit_combine(t9, 3, t35, 3, t36, 3);
    goto LAB74;

LAB72:    memcpy(t9, t35, 8);
    goto LAB74;

}

static void Always_40_3(char *t0)
{
    char t11[8];
    char t15[8];
    char t21[8];
    char t54[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    char *t9;
    char *t10;
    char *t12;
    char *t13;
    char *t14;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    int t45;
    int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t55;
    char *t56;
    char *t57;
    char *t58;
    char *t59;
    char *t60;
    char *t61;
    unsigned int t62;
    int t63;

LAB0:    t1 = (t0 + 4544U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(40, ng0);
    t2 = (t0 + 4912);
    *((int *)t2) = 1;
    t3 = (t0 + 4576);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(41, ng0);

LAB5:    xsi_set_current_line(42, ng0);
    t4 = (t0 + 2408);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);

LAB6:    t7 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t7, 3);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng8)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng1)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t8 == 1)
        goto LAB15;

LAB16:
LAB17:    goto LAB2;

LAB7:    xsi_set_current_line(43, ng0);
    t9 = ((char*)((ng5)));
    t10 = (t0 + 2568);
    xsi_vlogvar_assign_value(t10, t9, 0, 0, 3);
    goto LAB17;

LAB9:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1008U);
    t5 = (t3 + 72U);
    t7 = *((char **)t5);
    t9 = (t0 + 2568);
    t10 = (t9 + 56U);
    t12 = *((char **)t10);
    xsi_vlog_generic_get_index_select_value(t11, 1, t4, t7, 2, t12, 3, 2);
    t13 = (t0 + 1208U);
    t14 = *((char **)t13);
    t13 = (t0 + 1168U);
    t16 = (t13 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 2568);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_index_select_value(t15, 1, t14, t17, 2, t20, 3, 2);
    t22 = *((unsigned int *)t11);
    t23 = *((unsigned int *)t15);
    t24 = (t22 & t23);
    *((unsigned int *)t21) = t24;
    t25 = (t11 + 4);
    t26 = (t15 + 4);
    t27 = (t21 + 4);
    t28 = *((unsigned int *)t25);
    t29 = *((unsigned int *)t26);
    t30 = (t28 | t29);
    *((unsigned int *)t27) = t30;
    t31 = *((unsigned int *)t27);
    t32 = (t31 != 0);
    if (t32 == 1)
        goto LAB18;

LAB19:
LAB20:    t53 = (t0 + 2088);
    t55 = (t0 + 2088);
    t56 = (t55 + 72U);
    t57 = *((char **)t56);
    t58 = (t0 + 2568);
    t59 = (t58 + 56U);
    t60 = *((char **)t59);
    xsi_vlog_generic_convert_bit_index(t54, t57, 2, t60, 3, 2);
    t61 = (t54 + 4);
    t62 = *((unsigned int *)t61);
    t63 = (!(t62));
    if (t63 == 1)
        goto LAB21;

LAB22:    goto LAB17;

LAB11:    xsi_set_current_line(45, ng0);
    t3 = (t0 + 2568);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng6)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 3, t5, 3, t7, 3);
    t9 = (t0 + 2568);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 3);
    goto LAB17;

LAB13:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1008U);
    t5 = (t3 + 72U);
    t7 = *((char **)t5);
    t9 = (t0 + 2568);
    t10 = (t9 + 56U);
    t12 = *((char **)t10);
    xsi_vlog_generic_get_index_select_value(t11, 1, t4, t7, 2, t12, 3, 2);
    t13 = (t0 + 1208U);
    t14 = *((char **)t13);
    t13 = (t0 + 1168U);
    t16 = (t13 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 2568);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_index_select_value(t15, 1, t14, t17, 2, t20, 3, 2);
    t22 = *((unsigned int *)t11);
    t23 = *((unsigned int *)t15);
    t24 = (t22 | t23);
    *((unsigned int *)t21) = t24;
    t25 = (t11 + 4);
    t26 = (t15 + 4);
    t27 = (t21 + 4);
    t28 = *((unsigned int *)t25);
    t29 = *((unsigned int *)t26);
    t30 = (t28 | t29);
    *((unsigned int *)t27) = t30;
    t31 = *((unsigned int *)t27);
    t32 = (t31 != 0);
    if (t32 == 1)
        goto LAB23;

LAB24:
LAB25:    t53 = (t0 + 2088);
    t55 = (t0 + 2088);
    t56 = (t55 + 72U);
    t57 = *((char **)t56);
    t58 = (t0 + 2568);
    t59 = (t58 + 56U);
    t60 = *((char **)t59);
    xsi_vlog_generic_convert_bit_index(t54, t57, 2, t60, 3, 2);
    t61 = (t54 + 4);
    t49 = *((unsigned int *)t61);
    t63 = (!(t49));
    if (t63 == 1)
        goto LAB26;

LAB27:    goto LAB17;

LAB15:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 2568);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng6)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 3, t5, 3, t7, 3);
    t9 = (t0 + 2568);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 3);
    goto LAB17;

LAB18:    t33 = *((unsigned int *)t21);
    t34 = *((unsigned int *)t27);
    *((unsigned int *)t21) = (t33 | t34);
    t35 = (t11 + 4);
    t36 = (t15 + 4);
    t37 = *((unsigned int *)t11);
    t38 = (~(t37));
    t39 = *((unsigned int *)t35);
    t40 = (~(t39));
    t41 = *((unsigned int *)t15);
    t42 = (~(t41));
    t43 = *((unsigned int *)t36);
    t44 = (~(t43));
    t45 = (t38 & t40);
    t46 = (t42 & t44);
    t47 = (~(t45));
    t48 = (~(t46));
    t49 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t49 & t47);
    t50 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t50 & t48);
    t51 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t51 & t47);
    t52 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t52 & t48);
    goto LAB20;

LAB21:    xsi_vlogvar_assign_value(t53, t21, 0, *((unsigned int *)t54), 1);
    goto LAB22;

LAB23:    t33 = *((unsigned int *)t21);
    t34 = *((unsigned int *)t27);
    *((unsigned int *)t21) = (t33 | t34);
    t35 = (t11 + 4);
    t36 = (t15 + 4);
    t37 = *((unsigned int *)t35);
    t38 = (~(t37));
    t39 = *((unsigned int *)t11);
    t45 = (t39 & t38);
    t40 = *((unsigned int *)t36);
    t41 = (~(t40));
    t42 = *((unsigned int *)t15);
    t46 = (t42 & t41);
    t43 = (~(t45));
    t44 = (~(t46));
    t47 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t47 & t43);
    t48 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t48 & t44);
    goto LAB25;

LAB26:    xsi_vlogvar_assign_value(t53, t21, 0, *((unsigned int *)t54), 1);
    goto LAB27;

}


extern void work_m_02230111604953533873_2697172631_init()
{
	static char *pe[] = {(void *)Always_14_0,(void *)Always_20_1,(void *)Always_26_2,(void *)Always_40_3};
	xsi_register_didat("work_m_02230111604953533873_2697172631", "isim/test2_isim_beh.exe.sim/work/m_02230111604953533873_2697172631.didat");
	xsi_register_executes(pe);
}
