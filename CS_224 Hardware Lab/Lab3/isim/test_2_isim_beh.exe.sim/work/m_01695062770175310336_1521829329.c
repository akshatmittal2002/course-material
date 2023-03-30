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
static const char *ng0 = "/home/ise/Desktop/CS_224/Lab3/mux_2.v";



static void Always_7_0(char *t0)
{
    char t4[8];
    char t5[8];
    char t6[8];
    char t25[8];
    char t44[8];
    char t93[8];
    char t94[8];
    char t96[8];
    char t114[8];
    char t163[8];
    char t164[8];
    char t165[8];
    char t185[8];
    char *t1;
    char *t2;
    char *t3;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    char *t48;
    char *t49;
    char *t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    char *t58;
    char *t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    int t68;
    int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    char *t82;
    char *t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    char *t87;
    char *t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    char *t95;
    char *t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    char *t103;
    char *t104;
    char *t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    char *t118;
    char *t119;
    char *t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    char *t128;
    char *t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    unsigned int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    int t138;
    int t139;
    unsigned int t140;
    unsigned int t141;
    unsigned int t142;
    unsigned int t143;
    unsigned int t144;
    unsigned int t145;
    char *t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    unsigned int t150;
    unsigned int t151;
    char *t152;
    char *t153;
    unsigned int t154;
    unsigned int t155;
    unsigned int t156;
    char *t157;
    char *t158;
    unsigned int t159;
    unsigned int t160;
    unsigned int t161;
    unsigned int t162;
    char *t166;
    unsigned int t167;
    unsigned int t168;
    unsigned int t169;
    unsigned int t170;
    unsigned int t171;
    char *t172;
    char *t173;
    char *t174;
    unsigned int t175;
    unsigned int t176;
    unsigned int t177;
    unsigned int t178;
    unsigned int t179;
    unsigned int t180;
    unsigned int t181;
    unsigned int t182;
    char *t183;
    char *t184;
    unsigned int t186;
    unsigned int t187;
    unsigned int t188;
    char *t189;
    char *t190;
    unsigned int t191;
    unsigned int t192;
    unsigned int t193;
    unsigned int t194;
    unsigned int t195;
    unsigned int t196;
    unsigned int t197;
    char *t198;
    char *t199;
    unsigned int t200;
    unsigned int t201;
    unsigned int t202;
    unsigned int t203;
    unsigned int t204;
    unsigned int t205;
    unsigned int t206;
    unsigned int t207;
    int t208;
    int t209;
    unsigned int t210;
    unsigned int t211;
    unsigned int t212;
    unsigned int t213;
    unsigned int t214;
    unsigned int t215;
    char *t216;
    unsigned int t217;
    unsigned int t218;
    unsigned int t219;
    unsigned int t220;
    unsigned int t221;
    char *t222;
    char *t223;
    unsigned int t224;
    unsigned int t225;
    unsigned int t226;
    char *t227;
    char *t228;
    unsigned int t229;
    unsigned int t230;
    unsigned int t231;
    unsigned int t232;
    char *t233;

LAB0:    t1 = (t0 + 3160U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(7, ng0);
    t2 = (t0 + 3480);
    *((int *)t2) = 1;
    t3 = (t0 + 3192);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(8, ng0);

LAB5:    xsi_set_current_line(9, ng0);
    t7 = (t0 + 1688U);
    t8 = *((char **)t7);
    memset(t6, 0, 8);
    t7 = (t8 + 4);
    t9 = *((unsigned int *)t7);
    t10 = (~(t9));
    t11 = *((unsigned int *)t8);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t7) == 0)
        goto LAB6;

LAB8:    t14 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t14) = 1;

LAB9:    t15 = (t6 + 4);
    t16 = (t8 + 4);
    t17 = *((unsigned int *)t8);
    t18 = (~(t17));
    *((unsigned int *)t6) = t18;
    *((unsigned int *)t15) = 0;
    if (*((unsigned int *)t16) != 0)
        goto LAB11;

LAB10:    t23 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t23 & 1U);
    t24 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t24 & 1U);
    t26 = (t0 + 1848U);
    t27 = *((char **)t26);
    memset(t25, 0, 8);
    t26 = (t27 + 4);
    t28 = *((unsigned int *)t26);
    t29 = (~(t28));
    t30 = *((unsigned int *)t27);
    t31 = (t30 & t29);
    t32 = (t31 & 1U);
    if (t32 != 0)
        goto LAB15;

LAB13:    if (*((unsigned int *)t26) == 0)
        goto LAB12;

LAB14:    t33 = (t25 + 4);
    *((unsigned int *)t25) = 1;
    *((unsigned int *)t33) = 1;

LAB15:    t34 = (t25 + 4);
    t35 = (t27 + 4);
    t36 = *((unsigned int *)t27);
    t37 = (~(t36));
    *((unsigned int *)t25) = t37;
    *((unsigned int *)t34) = 0;
    if (*((unsigned int *)t35) != 0)
        goto LAB17;

LAB16:    t42 = *((unsigned int *)t25);
    *((unsigned int *)t25) = (t42 & 1U);
    t43 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t43 & 1U);
    t45 = *((unsigned int *)t6);
    t46 = *((unsigned int *)t25);
    t47 = (t45 & t46);
    *((unsigned int *)t44) = t47;
    t48 = (t6 + 4);
    t49 = (t25 + 4);
    t50 = (t44 + 4);
    t51 = *((unsigned int *)t48);
    t52 = *((unsigned int *)t49);
    t53 = (t51 | t52);
    *((unsigned int *)t50) = t53;
    t54 = *((unsigned int *)t50);
    t55 = (t54 != 0);
    if (t55 == 1)
        goto LAB18;

LAB19:
LAB20:    memset(t5, 0, 8);
    t76 = (t44 + 4);
    t77 = *((unsigned int *)t76);
    t78 = (~(t77));
    t79 = *((unsigned int *)t44);
    t80 = (t79 & t78);
    t81 = (t80 & 1U);
    if (t81 != 0)
        goto LAB21;

LAB22:    if (*((unsigned int *)t76) != 0)
        goto LAB23;

LAB24:    t83 = (t5 + 4);
    t84 = *((unsigned int *)t5);
    t85 = *((unsigned int *)t83);
    t86 = (t84 || t85);
    if (t86 > 0)
        goto LAB25;

LAB26:    t89 = *((unsigned int *)t5);
    t90 = (~(t89));
    t91 = *((unsigned int *)t83);
    t92 = (t90 || t91);
    if (t92 > 0)
        goto LAB27;

LAB28:    if (*((unsigned int *)t83) > 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t5) > 0)
        goto LAB31;

LAB32:    memcpy(t4, t93, 8);

LAB33:    t227 = (t0 + 2248);
    xsi_vlogvar_assign_value(t227, t4, 0, 0, 1);
    goto LAB2;

LAB6:    *((unsigned int *)t6) = 1;
    goto LAB9;

LAB11:    t19 = *((unsigned int *)t6);
    t20 = *((unsigned int *)t16);
    *((unsigned int *)t6) = (t19 | t20);
    t21 = *((unsigned int *)t15);
    t22 = *((unsigned int *)t16);
    *((unsigned int *)t15) = (t21 | t22);
    goto LAB10;

LAB12:    *((unsigned int *)t25) = 1;
    goto LAB15;

LAB17:    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t35);
    *((unsigned int *)t25) = (t38 | t39);
    t40 = *((unsigned int *)t34);
    t41 = *((unsigned int *)t35);
    *((unsigned int *)t34) = (t40 | t41);
    goto LAB16;

LAB18:    t56 = *((unsigned int *)t44);
    t57 = *((unsigned int *)t50);
    *((unsigned int *)t44) = (t56 | t57);
    t58 = (t6 + 4);
    t59 = (t25 + 4);
    t60 = *((unsigned int *)t6);
    t61 = (~(t60));
    t62 = *((unsigned int *)t58);
    t63 = (~(t62));
    t64 = *((unsigned int *)t25);
    t65 = (~(t64));
    t66 = *((unsigned int *)t59);
    t67 = (~(t66));
    t68 = (t61 & t63);
    t69 = (t65 & t67);
    t70 = (~(t68));
    t71 = (~(t69));
    t72 = *((unsigned int *)t50);
    *((unsigned int *)t50) = (t72 & t70);
    t73 = *((unsigned int *)t50);
    *((unsigned int *)t50) = (t73 & t71);
    t74 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t74 & t70);
    t75 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t75 & t71);
    goto LAB20;

LAB21:    *((unsigned int *)t5) = 1;
    goto LAB24;

LAB23:    t82 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t82) = 1;
    goto LAB24;

LAB25:    t87 = (t0 + 1048U);
    t88 = *((char **)t87);
    goto LAB26;

LAB27:    t87 = (t0 + 1688U);
    t95 = *((char **)t87);
    t87 = (t0 + 1848U);
    t97 = *((char **)t87);
    memset(t96, 0, 8);
    t87 = (t97 + 4);
    t98 = *((unsigned int *)t87);
    t99 = (~(t98));
    t100 = *((unsigned int *)t97);
    t101 = (t100 & t99);
    t102 = (t101 & 1U);
    if (t102 != 0)
        goto LAB37;

LAB35:    if (*((unsigned int *)t87) == 0)
        goto LAB34;

LAB36:    t103 = (t96 + 4);
    *((unsigned int *)t96) = 1;
    *((unsigned int *)t103) = 1;

LAB37:    t104 = (t96 + 4);
    t105 = (t97 + 4);
    t106 = *((unsigned int *)t97);
    t107 = (~(t106));
    *((unsigned int *)t96) = t107;
    *((unsigned int *)t104) = 0;
    if (*((unsigned int *)t105) != 0)
        goto LAB39;

LAB38:    t112 = *((unsigned int *)t96);
    *((unsigned int *)t96) = (t112 & 1U);
    t113 = *((unsigned int *)t104);
    *((unsigned int *)t104) = (t113 & 1U);
    t115 = *((unsigned int *)t95);
    t116 = *((unsigned int *)t96);
    t117 = (t115 & t116);
    *((unsigned int *)t114) = t117;
    t118 = (t95 + 4);
    t119 = (t96 + 4);
    t120 = (t114 + 4);
    t121 = *((unsigned int *)t118);
    t122 = *((unsigned int *)t119);
    t123 = (t121 | t122);
    *((unsigned int *)t120) = t123;
    t124 = *((unsigned int *)t120);
    t125 = (t124 != 0);
    if (t125 == 1)
        goto LAB40;

LAB41:
LAB42:    memset(t94, 0, 8);
    t146 = (t114 + 4);
    t147 = *((unsigned int *)t146);
    t148 = (~(t147));
    t149 = *((unsigned int *)t114);
    t150 = (t149 & t148);
    t151 = (t150 & 1U);
    if (t151 != 0)
        goto LAB43;

LAB44:    if (*((unsigned int *)t146) != 0)
        goto LAB45;

LAB46:    t153 = (t94 + 4);
    t154 = *((unsigned int *)t94);
    t155 = *((unsigned int *)t153);
    t156 = (t154 || t155);
    if (t156 > 0)
        goto LAB47;

LAB48:    t159 = *((unsigned int *)t94);
    t160 = (~(t159));
    t161 = *((unsigned int *)t153);
    t162 = (t160 || t161);
    if (t162 > 0)
        goto LAB49;

LAB50:    if (*((unsigned int *)t153) > 0)
        goto LAB51;

LAB52:    if (*((unsigned int *)t94) > 0)
        goto LAB53;

LAB54:    memcpy(t93, t163, 8);

LAB55:    goto LAB28;

LAB29:    xsi_vlog_unsigned_bit_combine(t4, 1, t88, 1, t93, 1);
    goto LAB33;

LAB31:    memcpy(t4, t88, 8);
    goto LAB33;

LAB34:    *((unsigned int *)t96) = 1;
    goto LAB37;

LAB39:    t108 = *((unsigned int *)t96);
    t109 = *((unsigned int *)t105);
    *((unsigned int *)t96) = (t108 | t109);
    t110 = *((unsigned int *)t104);
    t111 = *((unsigned int *)t105);
    *((unsigned int *)t104) = (t110 | t111);
    goto LAB38;

LAB40:    t126 = *((unsigned int *)t114);
    t127 = *((unsigned int *)t120);
    *((unsigned int *)t114) = (t126 | t127);
    t128 = (t95 + 4);
    t129 = (t96 + 4);
    t130 = *((unsigned int *)t95);
    t131 = (~(t130));
    t132 = *((unsigned int *)t128);
    t133 = (~(t132));
    t134 = *((unsigned int *)t96);
    t135 = (~(t134));
    t136 = *((unsigned int *)t129);
    t137 = (~(t136));
    t138 = (t131 & t133);
    t139 = (t135 & t137);
    t140 = (~(t138));
    t141 = (~(t139));
    t142 = *((unsigned int *)t120);
    *((unsigned int *)t120) = (t142 & t140);
    t143 = *((unsigned int *)t120);
    *((unsigned int *)t120) = (t143 & t141);
    t144 = *((unsigned int *)t114);
    *((unsigned int *)t114) = (t144 & t140);
    t145 = *((unsigned int *)t114);
    *((unsigned int *)t114) = (t145 & t141);
    goto LAB42;

LAB43:    *((unsigned int *)t94) = 1;
    goto LAB46;

LAB45:    t152 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t152) = 1;
    goto LAB46;

LAB47:    t157 = (t0 + 1208U);
    t158 = *((char **)t157);
    goto LAB48;

LAB49:    t157 = (t0 + 1688U);
    t166 = *((char **)t157);
    memset(t165, 0, 8);
    t157 = (t166 + 4);
    t167 = *((unsigned int *)t157);
    t168 = (~(t167));
    t169 = *((unsigned int *)t166);
    t170 = (t169 & t168);
    t171 = (t170 & 1U);
    if (t171 != 0)
        goto LAB59;

LAB57:    if (*((unsigned int *)t157) == 0)
        goto LAB56;

LAB58:    t172 = (t165 + 4);
    *((unsigned int *)t165) = 1;
    *((unsigned int *)t172) = 1;

LAB59:    t173 = (t165 + 4);
    t174 = (t166 + 4);
    t175 = *((unsigned int *)t166);
    t176 = (~(t175));
    *((unsigned int *)t165) = t176;
    *((unsigned int *)t173) = 0;
    if (*((unsigned int *)t174) != 0)
        goto LAB61;

LAB60:    t181 = *((unsigned int *)t165);
    *((unsigned int *)t165) = (t181 & 1U);
    t182 = *((unsigned int *)t173);
    *((unsigned int *)t173) = (t182 & 1U);
    t183 = (t0 + 1848U);
    t184 = *((char **)t183);
    t186 = *((unsigned int *)t165);
    t187 = *((unsigned int *)t184);
    t188 = (t186 & t187);
    *((unsigned int *)t185) = t188;
    t183 = (t165 + 4);
    t189 = (t184 + 4);
    t190 = (t185 + 4);
    t191 = *((unsigned int *)t183);
    t192 = *((unsigned int *)t189);
    t193 = (t191 | t192);
    *((unsigned int *)t190) = t193;
    t194 = *((unsigned int *)t190);
    t195 = (t194 != 0);
    if (t195 == 1)
        goto LAB62;

LAB63:
LAB64:    memset(t164, 0, 8);
    t216 = (t185 + 4);
    t217 = *((unsigned int *)t216);
    t218 = (~(t217));
    t219 = *((unsigned int *)t185);
    t220 = (t219 & t218);
    t221 = (t220 & 1U);
    if (t221 != 0)
        goto LAB65;

LAB66:    if (*((unsigned int *)t216) != 0)
        goto LAB67;

LAB68:    t223 = (t164 + 4);
    t224 = *((unsigned int *)t164);
    t225 = *((unsigned int *)t223);
    t226 = (t224 || t225);
    if (t226 > 0)
        goto LAB69;

LAB70:    t229 = *((unsigned int *)t164);
    t230 = (~(t229));
    t231 = *((unsigned int *)t223);
    t232 = (t230 || t231);
    if (t232 > 0)
        goto LAB71;

LAB72:    if (*((unsigned int *)t223) > 0)
        goto LAB73;

LAB74:    if (*((unsigned int *)t164) > 0)
        goto LAB75;

LAB76:    memcpy(t163, t233, 8);

LAB77:    goto LAB50;

LAB51:    xsi_vlog_unsigned_bit_combine(t93, 1, t158, 1, t163, 1);
    goto LAB55;

LAB53:    memcpy(t93, t158, 8);
    goto LAB55;

LAB56:    *((unsigned int *)t165) = 1;
    goto LAB59;

LAB61:    t177 = *((unsigned int *)t165);
    t178 = *((unsigned int *)t174);
    *((unsigned int *)t165) = (t177 | t178);
    t179 = *((unsigned int *)t173);
    t180 = *((unsigned int *)t174);
    *((unsigned int *)t173) = (t179 | t180);
    goto LAB60;

LAB62:    t196 = *((unsigned int *)t185);
    t197 = *((unsigned int *)t190);
    *((unsigned int *)t185) = (t196 | t197);
    t198 = (t165 + 4);
    t199 = (t184 + 4);
    t200 = *((unsigned int *)t165);
    t201 = (~(t200));
    t202 = *((unsigned int *)t198);
    t203 = (~(t202));
    t204 = *((unsigned int *)t184);
    t205 = (~(t204));
    t206 = *((unsigned int *)t199);
    t207 = (~(t206));
    t208 = (t201 & t203);
    t209 = (t205 & t207);
    t210 = (~(t208));
    t211 = (~(t209));
    t212 = *((unsigned int *)t190);
    *((unsigned int *)t190) = (t212 & t210);
    t213 = *((unsigned int *)t190);
    *((unsigned int *)t190) = (t213 & t211);
    t214 = *((unsigned int *)t185);
    *((unsigned int *)t185) = (t214 & t210);
    t215 = *((unsigned int *)t185);
    *((unsigned int *)t185) = (t215 & t211);
    goto LAB64;

LAB65:    *((unsigned int *)t164) = 1;
    goto LAB68;

LAB67:    t222 = (t164 + 4);
    *((unsigned int *)t164) = 1;
    *((unsigned int *)t222) = 1;
    goto LAB68;

LAB69:    t227 = (t0 + 1368U);
    t228 = *((char **)t227);
    goto LAB70;

LAB71:    t227 = (t0 + 1528U);
    t233 = *((char **)t227);
    goto LAB72;

LAB73:    xsi_vlog_unsigned_bit_combine(t163, 1, t228, 1, t233, 1);
    goto LAB77;

LAB75:    memcpy(t163, t228, 8);
    goto LAB77;

}


extern void work_m_01695062770175310336_1521829329_init()
{
	static char *pe[] = {(void *)Always_7_0};
	xsi_register_didat("work_m_01695062770175310336_1521829329", "isim/test_2_isim_beh.exe.sim/work/m_01695062770175310336_1521829329.didat");
	xsi_register_executes(pe);
}
