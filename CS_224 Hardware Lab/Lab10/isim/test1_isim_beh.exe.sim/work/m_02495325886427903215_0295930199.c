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
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab10/mem_module.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {11U, 0U};
static unsigned int ng4[] = {1U, 0U};
static unsigned int ng5[] = {2U, 0U};
static unsigned int ng6[] = {3U, 0U};
static unsigned int ng7[] = {4U, 0U};
static unsigned int ng8[] = {5U, 0U};
static unsigned int ng9[] = {6U, 0U};
static unsigned int ng10[] = {7U, 0U};
static unsigned int ng11[] = {8U, 0U};
static unsigned int ng12[] = {9U, 0U};
static unsigned int ng13[] = {10U, 0U};
static unsigned int ng14[] = {12U, 0U};
static unsigned int ng15[] = {13U, 0U};
static unsigned int ng16[] = {14U, 0U};
static unsigned int ng17[] = {15U, 0U};
static unsigned int ng18[] = {16U, 0U};
static unsigned int ng19[] = {17U, 0U};
static unsigned int ng20[] = {18U, 0U};
static int ng21[] = {6, 0};
static int ng22[] = {3, 0};
static int ng23[] = {0, 0};
static unsigned int ng24[] = {2305U, 0U};
static unsigned int ng25[] = {6691U, 0U};
static unsigned int ng26[] = {47941U, 0U};
static const char *ng27 = "";
static const char *ng28 = ",  curr=%d,  ss_add=%d,  ss_in=%d,  ss_out=%d,  rf_id=%d,  rf_in=%d,  rf_out=%d,  alu_out=%d, tmp=%d, op=%d, tmp1=%d, tmp2=%d, is_direct=%d";



static void Always_63_0(char *t0)
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

LAB0:    t1 = (t0 + 10712U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 11776);
    *((int *)t2) = 1;
    t3 = (t0 + 10744);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(64, ng0);

LAB5:    xsi_set_current_line(65, ng0);
    t4 = (t0 + 5560U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(66, ng0);
    t2 = (t0 + 9000);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 8840);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 5);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(65, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 8840);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 5);
    goto LAB8;

}

static void Always_70_1(char *t0)
{
    char t9[8];
    char t10[8];
    char t15[8];
    char t47[8];
    char t48[8];
    char t51[8];
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
    char *t13;
    char *t14;
    char *t16;
    char *t17;
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
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    char *t49;
    char *t50;
    char *t52;
    char *t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    char *t66;
    char *t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    char *t73;
    char *t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    char *t83;
    char *t84;

LAB0:    t1 = (t0 + 10960U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(70, ng0);
    t2 = (t0 + 11792);
    *((int *)t2) = 1;
    t3 = (t0 + 10992);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(71, ng0);

LAB5:    xsi_set_current_line(72, ng0);
    t4 = (t0 + 8840);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);

LAB6:    t7 = ((char*)((ng1)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t7, 5);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng8)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng10)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng11)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng12)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng13)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng3)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng14)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng15)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng16)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng17)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng18)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng19)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng20)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB43;

LAB44:
LAB45:    goto LAB2;

LAB7:    xsi_set_current_line(73, ng0);
    t11 = (t0 + 9160);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t14 = ((char*)((ng2)));
    memset(t15, 0, 8);
    t16 = (t13 + 4);
    t17 = (t14 + 4);
    t18 = *((unsigned int *)t13);
    t19 = *((unsigned int *)t14);
    t20 = (t18 ^ t19);
    t21 = *((unsigned int *)t16);
    t22 = *((unsigned int *)t17);
    t23 = (t21 ^ t22);
    t24 = (t20 | t23);
    t25 = *((unsigned int *)t16);
    t26 = *((unsigned int *)t17);
    t27 = (t25 | t26);
    t28 = (~(t27));
    t29 = (t24 & t28);
    if (t29 != 0)
        goto LAB49;

LAB46:    if (t27 != 0)
        goto LAB48;

LAB47:    *((unsigned int *)t15) = 1;

LAB49:    memset(t10, 0, 8);
    t31 = (t15 + 4);
    t32 = *((unsigned int *)t31);
    t33 = (~(t32));
    t34 = *((unsigned int *)t15);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB50;

LAB51:    if (*((unsigned int *)t31) != 0)
        goto LAB52;

LAB53:    t38 = (t10 + 4);
    t39 = *((unsigned int *)t10);
    t40 = *((unsigned int *)t38);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB54;

LAB55:    t43 = *((unsigned int *)t10);
    t44 = (~(t43));
    t45 = *((unsigned int *)t38);
    t46 = (t44 || t45);
    if (t46 > 0)
        goto LAB56;

LAB57:    if (*((unsigned int *)t38) > 0)
        goto LAB58;

LAB59:    if (*((unsigned int *)t10) > 0)
        goto LAB60;

LAB61:    memcpy(t9, t47, 8);

LAB62:    t84 = (t0 + 9000);
    xsi_vlogvar_assign_value(t84, t9, 0, 0, 5);
    goto LAB45;

LAB9:    xsi_set_current_line(74, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB11:    xsi_set_current_line(75, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB13:    xsi_set_current_line(76, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB15:    xsi_set_current_line(77, ng0);
    t3 = (t0 + 9320);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng1)));
    memset(t15, 0, 8);
    t11 = (t5 + 4);
    t12 = (t7 + 4);
    t18 = *((unsigned int *)t5);
    t19 = *((unsigned int *)t7);
    t20 = (t18 ^ t19);
    t21 = *((unsigned int *)t11);
    t22 = *((unsigned int *)t12);
    t23 = (t21 ^ t22);
    t24 = (t20 | t23);
    t25 = *((unsigned int *)t11);
    t26 = *((unsigned int *)t12);
    t27 = (t25 | t26);
    t28 = (~(t27));
    t29 = (t24 & t28);
    if (t29 != 0)
        goto LAB83;

LAB80:    if (t27 != 0)
        goto LAB82;

LAB81:    *((unsigned int *)t15) = 1;

LAB83:    memset(t10, 0, 8);
    t14 = (t15 + 4);
    t32 = *((unsigned int *)t14);
    t33 = (~(t32));
    t34 = *((unsigned int *)t15);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB84;

LAB85:    if (*((unsigned int *)t14) != 0)
        goto LAB86;

LAB87:    t17 = (t10 + 4);
    t39 = *((unsigned int *)t10);
    t40 = *((unsigned int *)t17);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB88;

LAB89:    t43 = *((unsigned int *)t10);
    t44 = (~(t43));
    t45 = *((unsigned int *)t17);
    t46 = (t44 || t45);
    if (t46 > 0)
        goto LAB90;

LAB91:    if (*((unsigned int *)t17) > 0)
        goto LAB92;

LAB93:    if (*((unsigned int *)t10) > 0)
        goto LAB94;

LAB95:    memcpy(t9, t31, 8);

LAB96:    t37 = (t0 + 9000);
    xsi_vlogvar_assign_value(t37, t9, 0, 0, 5);
    goto LAB45;

LAB17:    xsi_set_current_line(78, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB19:    xsi_set_current_line(79, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB21:    xsi_set_current_line(80, ng0);
    t3 = ((char*)((ng11)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB23:    xsi_set_current_line(81, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB25:    xsi_set_current_line(82, ng0);
    t3 = ((char*)((ng13)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB27:    xsi_set_current_line(83, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB29:    xsi_set_current_line(84, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB31:    xsi_set_current_line(85, ng0);
    t3 = ((char*)((ng15)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB33:    xsi_set_current_line(86, ng0);
    t3 = ((char*)((ng16)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB35:    xsi_set_current_line(87, ng0);
    t3 = ((char*)((ng17)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB37:    xsi_set_current_line(88, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB39:    xsi_set_current_line(89, ng0);
    t3 = ((char*)((ng19)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB41:    xsi_set_current_line(90, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 9000);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 5);
    goto LAB45;

LAB43:    xsi_set_current_line(91, ng0);
    t3 = (t0 + 9480);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng1)));
    memset(t15, 0, 8);
    t11 = (t5 + 4);
    t12 = (t7 + 4);
    t18 = *((unsigned int *)t5);
    t19 = *((unsigned int *)t7);
    t20 = (t18 ^ t19);
    t21 = *((unsigned int *)t11);
    t22 = *((unsigned int *)t12);
    t23 = (t21 ^ t22);
    t24 = (t20 | t23);
    t25 = *((unsigned int *)t11);
    t26 = *((unsigned int *)t12);
    t27 = (t25 | t26);
    t28 = (~(t27));
    t29 = (t24 & t28);
    if (t29 != 0)
        goto LAB100;

LAB97:    if (t27 != 0)
        goto LAB99;

LAB98:    *((unsigned int *)t15) = 1;

LAB100:    memset(t10, 0, 8);
    t14 = (t15 + 4);
    t32 = *((unsigned int *)t14);
    t33 = (~(t32));
    t34 = *((unsigned int *)t15);
    t35 = (t34 & t33);
    t36 = (t35 & 1U);
    if (t36 != 0)
        goto LAB101;

LAB102:    if (*((unsigned int *)t14) != 0)
        goto LAB103;

LAB104:    t17 = (t10 + 4);
    t39 = *((unsigned int *)t10);
    t40 = *((unsigned int *)t17);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB105;

LAB106:    t43 = *((unsigned int *)t10);
    t44 = (~(t43));
    t45 = *((unsigned int *)t17);
    t46 = (t44 || t45);
    if (t46 > 0)
        goto LAB107;

LAB108:    if (*((unsigned int *)t17) > 0)
        goto LAB109;

LAB110:    if (*((unsigned int *)t10) > 0)
        goto LAB111;

LAB112:    memcpy(t9, t31, 8);

LAB113:    t37 = (t0 + 9000);
    xsi_vlogvar_assign_value(t37, t9, 0, 0, 5);
    goto LAB45;

LAB48:    t30 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t30) = 1;
    goto LAB49;

LAB50:    *((unsigned int *)t10) = 1;
    goto LAB53;

LAB52:    t37 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB53;

LAB54:    t42 = ((char*)((ng3)));
    goto LAB55;

LAB56:    t49 = (t0 + 5400U);
    t50 = *((char **)t49);
    t49 = ((char*)((ng2)));
    memset(t51, 0, 8);
    t52 = (t50 + 4);
    t53 = (t49 + 4);
    t54 = *((unsigned int *)t50);
    t55 = *((unsigned int *)t49);
    t56 = (t54 ^ t55);
    t57 = *((unsigned int *)t52);
    t58 = *((unsigned int *)t53);
    t59 = (t57 ^ t58);
    t60 = (t56 | t59);
    t61 = *((unsigned int *)t52);
    t62 = *((unsigned int *)t53);
    t63 = (t61 | t62);
    t64 = (~(t63));
    t65 = (t60 & t64);
    if (t65 != 0)
        goto LAB66;

LAB63:    if (t63 != 0)
        goto LAB65;

LAB64:    *((unsigned int *)t51) = 1;

LAB66:    memset(t48, 0, 8);
    t67 = (t51 + 4);
    t68 = *((unsigned int *)t67);
    t69 = (~(t68));
    t70 = *((unsigned int *)t51);
    t71 = (t70 & t69);
    t72 = (t71 & 1U);
    if (t72 != 0)
        goto LAB67;

LAB68:    if (*((unsigned int *)t67) != 0)
        goto LAB69;

LAB70:    t74 = (t48 + 4);
    t75 = *((unsigned int *)t48);
    t76 = *((unsigned int *)t74);
    t77 = (t75 || t76);
    if (t77 > 0)
        goto LAB71;

LAB72:    t79 = *((unsigned int *)t48);
    t80 = (~(t79));
    t81 = *((unsigned int *)t74);
    t82 = (t80 || t81);
    if (t82 > 0)
        goto LAB73;

LAB74:    if (*((unsigned int *)t74) > 0)
        goto LAB75;

LAB76:    if (*((unsigned int *)t48) > 0)
        goto LAB77;

LAB78:    memcpy(t47, t83, 8);

LAB79:    goto LAB57;

LAB58:    xsi_vlog_unsigned_bit_combine(t9, 5, t42, 5, t47, 5);
    goto LAB62;

LAB60:    memcpy(t9, t42, 8);
    goto LAB62;

LAB65:    t66 = (t51 + 4);
    *((unsigned int *)t51) = 1;
    *((unsigned int *)t66) = 1;
    goto LAB66;

LAB67:    *((unsigned int *)t48) = 1;
    goto LAB70;

LAB69:    t73 = (t48 + 4);
    *((unsigned int *)t48) = 1;
    *((unsigned int *)t73) = 1;
    goto LAB70;

LAB71:    t78 = ((char*)((ng4)));
    goto LAB72;

LAB73:    t83 = ((char*)((ng1)));
    goto LAB74;

LAB75:    xsi_vlog_unsigned_bit_combine(t47, 5, t78, 5, t83, 5);
    goto LAB79;

LAB77:    memcpy(t47, t78, 8);
    goto LAB79;

LAB82:    t13 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t13) = 1;
    goto LAB83;

LAB84:    *((unsigned int *)t10) = 1;
    goto LAB87;

LAB86:    t16 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t16) = 1;
    goto LAB87;

LAB88:    t30 = ((char*)((ng8)));
    goto LAB89;

LAB90:    t31 = ((char*)((ng4)));
    goto LAB91;

LAB92:    xsi_vlog_unsigned_bit_combine(t9, 5, t30, 5, t31, 5);
    goto LAB96;

LAB94:    memcpy(t9, t30, 8);
    goto LAB96;

LAB99:    t13 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t13) = 1;
    goto LAB100;

LAB101:    *((unsigned int *)t10) = 1;
    goto LAB104;

LAB103:    t16 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t16) = 1;
    goto LAB104;

LAB105:    t30 = ((char*)((ng1)));
    goto LAB106;

LAB107:    t31 = ((char*)((ng3)));
    goto LAB108;

LAB109:    xsi_vlog_unsigned_bit_combine(t9, 5, t30, 5, t31, 5);
    goto LAB113;

LAB111:    memcpy(t9, t30, 8);
    goto LAB113;

}

static void Always_96_2(char *t0)
{
    char t11[8];
    char t12[8];
    char t13[8];
    char t44[8];
    char t45[8];
    char t57[16];
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
    unsigned int t25;
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
    char *t46;
    char *t47;
    char *t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    char *t55;
    char *t56;
    char *t58;
    char *t59;
    char *t60;
    char *t61;
    char *t62;
    char *t63;
    char *t64;
    char *t65;
    char *t66;
    char *t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    char *t72;
    char *t73;

LAB0:    t1 = (t0 + 11208U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(96, ng0);
    t2 = (t0 + 11808);
    *((int *)t2) = 1;
    t3 = (t0 + 11240);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(97, ng0);

LAB5:    xsi_set_current_line(98, ng0);
    t4 = (t0 + 8840);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);

LAB6:    t7 = ((char*)((ng1)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t7, 5);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng4)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng7)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng8)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng9)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng10)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng11)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng12)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng13)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng3)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng14)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng15)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng16)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng17)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng18)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng19)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng20)));
    t8 = xsi_vlog_unsigned_case_compare(t6, 5, t2, 5);
    if (t8 == 1)
        goto LAB43;

LAB44:
LAB45:    xsi_set_current_line(214, ng0);
    t2 = xsi_vlog_time(t57, 1000.0000000000000, 1000.0000000000000);
    xsi_vlogfile_write(0, 0, 0, ng27, 2, t0, (char)118, t57, 64);
    t3 = (t0 + 8840);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = (t0 + 8040);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    t26 = (t0 + 7560);
    t32 = (t26 + 56U);
    t33 = *((char **)t32);
    t37 = (t0 + 5880U);
    t42 = *((char **)t37);
    t37 = (t0 + 8200);
    t43 = (t37 + 56U);
    t46 = *((char **)t43);
    t47 = (t0 + 7720);
    t48 = (t47 + 56U);
    t55 = *((char **)t48);
    t56 = (t0 + 6040U);
    t58 = *((char **)t56);
    t56 = (t0 + 6360U);
    t59 = *((char **)t56);
    t56 = (t0 + 7880);
    t60 = (t56 + 56U);
    t61 = *((char **)t60);
    t62 = (t0 + 8680);
    t63 = (t62 + 56U);
    t64 = *((char **)t63);
    t65 = (t0 + 8360);
    t66 = (t65 + 56U);
    t67 = *((char **)t66);
    t68 = (t0 + 8520);
    t69 = (t68 + 56U);
    t70 = *((char **)t69);
    t71 = (t0 + 9800);
    t72 = (t71 + 56U);
    t73 = *((char **)t72);
    xsi_vlogfile_write(1, 0, 0, ng28, 14, t0, (char)118, t5, 5, (char)118, t10, 5, (char)118, t33, 16, (char)118, t42, 16, (char)118, t46, 4, (char)118, t55, 16, (char)118, t58, 16, (char)118, t59, 16, (char)118, t61, 16, (char)118, t64, 4, (char)118, t67, 16, (char)118, t70, 16, (char)118, t73, 1);
    goto LAB2;

LAB7:    xsi_set_current_line(101, ng0);

LAB46:    xsi_set_current_line(102, ng0);
    t9 = ((char*)((ng21)));
    t10 = (t0 + 9320);
    xsi_vlogvar_assign_value(t10, t9, 0, 0, 5);
    xsi_set_current_line(103, ng0);
    t2 = ((char*)((ng22)));
    t3 = (t0 + 9480);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    xsi_set_current_line(105, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 8040);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 5);
    xsi_set_current_line(106, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 6920);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(107, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(108, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 8200);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);
    xsi_set_current_line(109, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7720);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    xsi_set_current_line(110, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 8360);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    xsi_set_current_line(111, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 8520);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    goto LAB45;

LAB9:    xsi_set_current_line(116, ng0);

LAB47:    xsi_set_current_line(117, ng0);
    t3 = (t0 + 9320);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_minus(t11, 32, t5, 5, t7, 32);
    t9 = (t0 + 9320);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 5);
    xsi_set_current_line(118, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 6920);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(119, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 7080);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(120, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7240);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(121, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB45;

LAB11:    xsi_set_current_line(124, ng0);

LAB48:    xsi_set_current_line(125, ng0);
    t3 = (t0 + 5880U);
    t4 = *((char **)t3);
    t3 = (t0 + 7880);
    xsi_vlogvar_assign_value(t3, t4, 0, 0, 16);
    xsi_set_current_line(126, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(127, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 7720);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 16);
    goto LAB45;

LAB13:    xsi_set_current_line(130, ng0);

LAB49:    xsi_set_current_line(131, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 6920);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(132, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB45;

LAB15:    xsi_set_current_line(135, ng0);

LAB50:    xsi_set_current_line(136, ng0);
    t3 = (t0 + 8040);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 32, t5, 5, t7, 32);
    t9 = (t0 + 8040);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 5);
    xsi_set_current_line(137, ng0);
    t2 = (t0 + 8200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 32, t4, 4, t5, 32);
    t7 = (t0 + 8200);
    xsi_vlogvar_assign_value(t7, t11, 0, 0, 4);
    xsi_set_current_line(138, ng0);
    t2 = (t0 + 9320);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng23)));
    memset(t13, 0, 8);
    t7 = (t4 + 4);
    t9 = (t5 + 4);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 ^ t15);
    t17 = *((unsigned int *)t7);
    t18 = *((unsigned int *)t9);
    t19 = (t17 ^ t18);
    t20 = (t16 | t19);
    t21 = *((unsigned int *)t7);
    t22 = *((unsigned int *)t9);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB54;

LAB51:    if (t23 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t13) = 1;

LAB54:    memset(t12, 0, 8);
    t26 = (t13 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (~(t27));
    t29 = *((unsigned int *)t13);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB55;

LAB56:    if (*((unsigned int *)t26) != 0)
        goto LAB57;

LAB58:    t33 = (t12 + 4);
    t34 = *((unsigned int *)t12);
    t35 = *((unsigned int *)t33);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB59;

LAB60:    t38 = *((unsigned int *)t12);
    t39 = (~(t38));
    t40 = *((unsigned int *)t33);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB61;

LAB62:    if (*((unsigned int *)t33) > 0)
        goto LAB63;

LAB64:    if (*((unsigned int *)t12) > 0)
        goto LAB65;

LAB66:    memcpy(t11, t42, 8);

LAB67:    t43 = (t0 + 9160);
    xsi_vlogvar_assign_value(t43, t11, 0, 0, 1);
    goto LAB45;

LAB17:    xsi_set_current_line(142, ng0);

LAB68:    xsi_set_current_line(143, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 7880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    xsi_set_current_line(144, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(145, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 7720);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 16);
    goto LAB45;

LAB19:    xsi_set_current_line(147, ng0);

LAB69:    xsi_set_current_line(148, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 7400);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(149, ng0);
    t2 = (t0 + 8200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 32, t4, 4, t5, 32);
    t7 = (t0 + 8200);
    xsi_vlogvar_assign_value(t7, t11, 0, 0, 4);
    goto LAB45;

LAB21:    xsi_set_current_line(151, ng0);

LAB70:    xsi_set_current_line(152, ng0);
    t3 = ((char*)((ng25)));
    t4 = (t0 + 7880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    xsi_set_current_line(153, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(154, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 7720);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 16);
    goto LAB45;

LAB23:    xsi_set_current_line(156, ng0);

LAB71:    xsi_set_current_line(157, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 7400);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(158, ng0);
    t2 = (t0 + 8200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 32, t4, 4, t5, 32);
    t7 = (t0 + 8200);
    xsi_vlogvar_assign_value(t7, t11, 0, 0, 4);
    goto LAB45;

LAB25:    xsi_set_current_line(160, ng0);

LAB72:    xsi_set_current_line(161, ng0);
    t3 = ((char*)((ng26)));
    t4 = (t0 + 7880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    xsi_set_current_line(162, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(163, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 7720);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 16);
    goto LAB45;

LAB27:    xsi_set_current_line(165, ng0);

LAB73:    xsi_set_current_line(166, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 7400);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(167, ng0);
    t2 = (t0 + 8200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_add(t11, 32, t4, 4, t5, 32);
    t7 = (t0 + 8200);
    xsi_vlogvar_assign_value(t7, t11, 0, 0, 4);
    goto LAB45;

LAB29:    xsi_set_current_line(172, ng0);

LAB74:    xsi_set_current_line(173, ng0);
    t3 = ((char*)((ng23)));
    t4 = (t0 + 8360);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    xsi_set_current_line(174, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 8520);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    xsi_set_current_line(175, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 9640);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB45;

LAB31:    xsi_set_current_line(177, ng0);

LAB75:    xsi_set_current_line(178, ng0);
    t3 = ((char*)((ng21)));
    t4 = ((char*)((ng22)));
    t5 = (t0 + 9480);
    t7 = (t5 + 56U);
    t9 = *((char **)t7);
    memset(t11, 0, 8);
    xsi_vlog_unsigned_minus(t11, 32, t4, 32, t9, 5);
    memset(t12, 0, 8);
    xsi_vlog_unsigned_add(t12, 32, t3, 32, t11, 32);
    t10 = (t0 + 8200);
    xsi_vlogvar_assign_value(t10, t12, 0, 0, 4);
    goto LAB45;

LAB33:    xsi_set_current_line(181, ng0);

LAB76:    xsi_set_current_line(182, ng0);
    t3 = (t0 + 6040U);
    t4 = *((char **)t3);
    t3 = (t0 + 7880);
    xsi_vlogvar_assign_value(t3, t4, 0, 0, 16);
    xsi_set_current_line(183, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t12, 0, 8);
    t5 = (t12 + 4);
    t7 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = (t14 >> 4);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 4);
    *((unsigned int *)t5) = t17;
    t18 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t18 & 15U);
    t19 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t19 & 15U);
    t9 = ((char*)((ng1)));
    xsi_vlogtype_concat(t11, 16, 16, 2U, t9, 12, t12, 4);
    t10 = (t0 + 8200);
    xsi_vlogvar_assign_value(t10, t11, 0, 0, 4);
    goto LAB45;

LAB35:    xsi_set_current_line(186, ng0);

LAB77:    xsi_set_current_line(187, ng0);
    t3 = (t0 + 6040U);
    t4 = *((char **)t3);
    t3 = (t0 + 8360);
    xsi_vlogvar_assign_value(t3, t4, 0, 0, 16);
    xsi_set_current_line(188, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t12, 0, 8);
    t5 = (t12 + 4);
    t7 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = (t14 >> 0);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 0);
    *((unsigned int *)t5) = t17;
    t18 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t18 & 15U);
    t19 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t19 & 15U);
    t9 = ((char*)((ng1)));
    xsi_vlogtype_concat(t11, 16, 16, 2U, t9, 12, t12, 4);
    t10 = (t0 + 8200);
    xsi_vlogvar_assign_value(t10, t11, 0, 0, 4);
    goto LAB45;

LAB37:    xsi_set_current_line(191, ng0);

LAB78:    xsi_set_current_line(192, ng0);
    t3 = (t0 + 7880);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    memset(t12, 0, 8);
    t7 = (t12 + 4);
    t9 = (t5 + 4);
    t14 = *((unsigned int *)t5);
    t15 = (t14 >> 12);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t9);
    t17 = (t16 >> 12);
    *((unsigned int *)t7) = t17;
    t18 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t18 & 7U);
    t19 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t19 & 7U);
    t10 = ((char*)((ng1)));
    xsi_vlogtype_concat(t11, 15, 15, 2U, t10, 12, t12, 3);
    t26 = (t0 + 8680);
    xsi_vlogvar_assign_value(t26, t11, 0, 0, 4);
    xsi_set_current_line(193, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t11, 0, 8);
    t5 = (t11 + 4);
    t7 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t7);
    t18 = (t17 >> 15);
    t19 = (t18 & 1);
    *((unsigned int *)t5) = t19;
    t9 = (t0 + 9800);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 1);
    xsi_set_current_line(194, ng0);
    t2 = (t0 + 9800);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng23)));
    memset(t13, 0, 8);
    t7 = (t4 + 4);
    t9 = (t5 + 4);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 ^ t15);
    t17 = *((unsigned int *)t7);
    t18 = *((unsigned int *)t9);
    t19 = (t17 ^ t18);
    t20 = (t16 | t19);
    t21 = *((unsigned int *)t7);
    t22 = *((unsigned int *)t9);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB82;

LAB79:    if (t23 != 0)
        goto LAB81;

LAB80:    *((unsigned int *)t13) = 1;

LAB82:    memset(t12, 0, 8);
    t26 = (t13 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (~(t27));
    t29 = *((unsigned int *)t13);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB83;

LAB84:    if (*((unsigned int *)t26) != 0)
        goto LAB85;

LAB86:    t33 = (t12 + 4);
    t34 = *((unsigned int *)t12);
    t35 = *((unsigned int *)t33);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB87;

LAB88:    t38 = *((unsigned int *)t12);
    t39 = (~(t38));
    t40 = *((unsigned int *)t33);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB89;

LAB90:    if (*((unsigned int *)t33) > 0)
        goto LAB91;

LAB92:    if (*((unsigned int *)t12) > 0)
        goto LAB93;

LAB94:    memcpy(t11, t44, 8);

LAB95:    t56 = (t0 + 8520);
    xsi_vlogvar_assign_value(t56, t11, 0, 0, 16);
    xsi_set_current_line(195, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 9640);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB45;

LAB39:    xsi_set_current_line(198, ng0);

LAB96:    xsi_set_current_line(199, ng0);
    t3 = ((char*)((ng23)));
    t4 = (t0 + 7400);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(200, ng0);
    t2 = (t0 + 6360U);
    t3 = *((char **)t2);
    t2 = (t0 + 7720);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 16);
    xsi_set_current_line(201, ng0);
    t2 = (t0 + 7880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t12, 0, 8);
    t5 = (t12 + 4);
    t7 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = (t14 >> 8);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t7);
    t17 = (t16 >> 8);
    *((unsigned int *)t5) = t17;
    t18 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t18 & 15U);
    t19 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t19 & 15U);
    t9 = ((char*)((ng1)));
    xsi_vlogtype_concat(t11, 16, 16, 2U, t9, 12, t12, 4);
    t10 = (t0 + 8200);
    xsi_vlogvar_assign_value(t10, t11, 0, 0, 4);
    goto LAB45;

LAB41:    xsi_set_current_line(204, ng0);

LAB97:    xsi_set_current_line(205, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 9640);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(206, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 7400);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB45;

LAB43:    xsi_set_current_line(209, ng0);

LAB98:    xsi_set_current_line(210, ng0);
    t3 = (t0 + 9480);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = ((char*)((ng2)));
    memset(t11, 0, 8);
    xsi_vlog_unsigned_minus(t11, 32, t5, 5, t7, 32);
    t9 = (t0 + 9480);
    xsi_vlogvar_assign_value(t9, t11, 0, 0, 5);
    xsi_set_current_line(211, ng0);
    t2 = (t0 + 9480);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng23)));
    memset(t13, 0, 8);
    t7 = (t4 + 4);
    t9 = (t5 + 4);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 ^ t15);
    t17 = *((unsigned int *)t7);
    t18 = *((unsigned int *)t9);
    t19 = (t17 ^ t18);
    t20 = (t16 | t19);
    t21 = *((unsigned int *)t7);
    t22 = *((unsigned int *)t9);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB102;

LAB99:    if (t23 != 0)
        goto LAB101;

LAB100:    *((unsigned int *)t13) = 1;

LAB102:    memset(t12, 0, 8);
    t26 = (t13 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (~(t27));
    t29 = *((unsigned int *)t13);
    t30 = (t29 & t28);
    t31 = (t30 & 1U);
    if (t31 != 0)
        goto LAB103;

LAB104:    if (*((unsigned int *)t26) != 0)
        goto LAB105;

LAB106:    t33 = (t12 + 4);
    t34 = *((unsigned int *)t12);
    t35 = *((unsigned int *)t33);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB107;

LAB108:    t38 = *((unsigned int *)t12);
    t39 = (~(t38));
    t40 = *((unsigned int *)t33);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB109;

LAB110:    if (*((unsigned int *)t33) > 0)
        goto LAB111;

LAB112:    if (*((unsigned int *)t12) > 0)
        goto LAB113;

LAB114:    memcpy(t11, t42, 8);

LAB115:    t43 = (t0 + 9160);
    xsi_vlogvar_assign_value(t43, t11, 0, 0, 1);
    goto LAB45;

LAB53:    t10 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t10) = 1;
    goto LAB54;

LAB55:    *((unsigned int *)t12) = 1;
    goto LAB58;

LAB57:    t32 = (t12 + 4);
    *((unsigned int *)t12) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB58;

LAB59:    t37 = ((char*)((ng2)));
    goto LAB60;

LAB61:    t42 = ((char*)((ng23)));
    goto LAB62;

LAB63:    xsi_vlog_unsigned_bit_combine(t11, 32, t37, 32, t42, 32);
    goto LAB67;

LAB65:    memcpy(t11, t37, 8);
    goto LAB67;

LAB81:    t10 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t10) = 1;
    goto LAB82;

LAB83:    *((unsigned int *)t12) = 1;
    goto LAB86;

LAB85:    t32 = (t12 + 4);
    *((unsigned int *)t12) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB86;

LAB87:    t37 = (t0 + 6040U);
    t42 = *((char **)t37);
    goto LAB88;

LAB89:    t37 = (t0 + 7880);
    t43 = (t37 + 56U);
    t46 = *((char **)t43);
    memset(t45, 0, 8);
    t47 = (t45 + 4);
    t48 = (t46 + 4);
    t49 = *((unsigned int *)t46);
    t50 = (t49 >> 0);
    *((unsigned int *)t45) = t50;
    t51 = *((unsigned int *)t48);
    t52 = (t51 >> 0);
    *((unsigned int *)t47) = t52;
    t53 = *((unsigned int *)t45);
    *((unsigned int *)t45) = (t53 & 15U);
    t54 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t54 & 15U);
    t55 = ((char*)((ng1)));
    xsi_vlogtype_concat(t44, 16, 16, 2U, t55, 12, t45, 4);
    goto LAB90;

LAB91:    xsi_vlog_unsigned_bit_combine(t11, 16, t42, 16, t44, 16);
    goto LAB95;

LAB93:    memcpy(t11, t42, 8);
    goto LAB95;

LAB101:    t10 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t10) = 1;
    goto LAB102;

LAB103:    *((unsigned int *)t12) = 1;
    goto LAB106;

LAB105:    t32 = (t12 + 4);
    *((unsigned int *)t12) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB106;

LAB107:    t37 = ((char*)((ng23)));
    goto LAB108;

LAB109:    t42 = ((char*)((ng2)));
    goto LAB110;

LAB111:    xsi_vlog_unsigned_bit_combine(t11, 32, t37, 32, t42, 32);
    goto LAB115;

LAB113:    memcpy(t11, t37, 8);
    goto LAB115;

}

static void implSig1_execute(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    t1 = (t0 + 11456U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = ((char*)((ng23)));
    t3 = (t0 + 11888);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 8);
    xsi_driver_vfirst_trans(t3, 0, 31);

LAB1:    return;
}


extern void work_m_02495325886427903215_0295930199_init()
{
	static char *pe[] = {(void *)Always_63_0,(void *)Always_70_1,(void *)Always_96_2,(void *)implSig1_execute};
	xsi_register_didat("work_m_02495325886427903215_0295930199", "isim/test1_isim_beh.exe.sim/work/m_02495325886427903215_0295930199.didat");
	xsi_register_executes(pe);
}
