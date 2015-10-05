function b = b_brachia_bot(in1,in2,in3)
%B_BRACHIA_BOT
%    B = B_BRACHIA_BOT(IN1,IN2,IN3)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Oct-2015 13:43:29

c1 = in3(5,:);
c2 = in3(6,:);
c3 = in3(7,:);
c4 = in3(8,:);
dth1 = in1(5,:);
dth2 = in1(6,:);
dth3 = in1(7,:);
dth4 = in1(8,:);
g = in3(17,:);
l1 = in3(1,:);
l2 = in3(2,:);
l3 = in3(3,:);
m1 = in3(9,:);
m2 = in3(10,:);
m3 = in3(11,:);
m4 = in3(12,:);
tau1 = in2(1,:);
tau2 = in2(2,:);
tau3 = in2(3,:);
tau4 = in2(4,:);
th1 = in1(1,:);
th2 = in1(2,:);
th3 = in1(3,:);
th4 = in1(4,:);
t2 = th1+th2+th3;
t3 = cos(t2);
t4 = th1+th2;
t5 = sin(t2);
t6 = cos(t4);
t7 = l2.*t6;
t8 = cos(th1);
t9 = l1.*t8;
t10 = c3.*t3;
t11 = t7+t9+t10;
t12 = c3.*dth3.*t3;
t13 = sin(t4);
t14 = l2.*t13;
t15 = sin(th1);
t16 = l1.*t15;
t17 = c3.*t5;
t18 = t14+t16+t17;
t19 = c3.*dth3.*t5;
t20 = th1+th2+th3+th4;
t21 = sin(t20);
t22 = c4.*t21;
t23 = l3.*t5;
t24 = cos(t20);
t25 = c4.*t24;
t26 = l3.*t3;
t27 = t25+t26;
t28 = t14+t16+t22+t23;
t29 = t22+t23;
t30 = dth3.*t29;
t31 = c4.*dth4.*t21;
t32 = dth3.*t27;
t33 = t7+t9+t25+t26;
t34 = c4.*dth4.*t24;
t35 = t14+t22+t23;
t36 = dth1.*t33;
t37 = t7+t25+t26;
t38 = dth2.*t37;
t39 = t32+t34+t36+t38;
t40 = dth2.*t35;
t41 = dth1.*t28;
t42 = t30+t31+t40+t41;
t43 = t14+t17;
t44 = dth1.*t11;
t45 = t7+t10;
t46 = dth2.*t45;
t47 = t12+t44+t46;
t48 = dth2.*t43;
t49 = dth1.*t18;
t50 = t19+t48+t49;
t51 = c2.*t13;
t52 = t16+t51;
t53 = c2.*dth2.*t13;
t54 = c2.*t6;
t55 = t9+t54;
t56 = c2.*dth2.*t6;
t57 = c2.*dth1.*t13;
t58 = t53+t57;
t59 = dth1.*t55;
t60 = t56+t59;
t61 = c2.*dth1.*t6;
t62 = t56+t61;
t63 = dth1.*t52;
t64 = t53+t63;
t65 = dth1.*t35;
t66 = t30+t31+t40+t65;
t67 = dth1.*t37;
t68 = t32+t34+t38+t67;
t69 = c2.*t13.*t60.*2.0;
t70 = dth1.*t43;
t71 = t19+t48+t70;
t72 = t43.*t47.*2.0;
t73 = dth1.*t45;
t74 = t12+t46+t73;
t75 = t35.*t39.*2.0;
t76 = c3.*dth1.*t3;
t77 = c3.*dth2.*t3;
t78 = t12+t76+t77;
t79 = c3.*dth1.*t5;
t80 = c3.*dth2.*t5;
t81 = t19+t79+t80;
t82 = c3.*t5.*t47.*2.0;
t83 = dth1.*t29;
t84 = dth2.*t29;
t85 = t30+t31+t83+t84;
t86 = dth1.*t27;
t87 = dth2.*t27;
t88 = t32+t34+t86+t87;
t89 = t29.*t39.*2.0;
t90 = c4.*dth1.*t21;
t91 = c4.*dth2.*t21;
t92 = c4.*dth3.*t21;
t93 = t31+t90+t91+t92;
t94 = c4.*dth1.*t24;
t95 = c4.*dth2.*t24;
t96 = c4.*dth3.*t24;
t97 = t34+t94+t95+t96;
t98 = c4.*t24.*t42.*2.0;
b = [tau1+dth3.*(m4.*(t89-t27.*t42.*2.0-t28.*t88.*2.0+t33.*t85.*2.0).*(1.0./2.0)+m3.*(t82+t11.*t81.*2.0-t18.*t78.*2.0-c3.*t3.*t50.*2.0).*(1.0./2.0))+dth2.*(m3.*(t72+t11.*t71.*2.0-t18.*t74.*2.0-t45.*t50.*2.0).*(1.0./2.0)+m4.*(t75-t37.*t42.*2.0-t28.*t68.*2.0+t33.*t66.*2.0).*(1.0./2.0)+m2.*(t69+t55.*t58.*2.0-t52.*t62.*2.0-c2.*t6.*t64.*2.0).*(1.0./2.0))-dth4.*m4.*(t98+t28.*t97.*2.0-t33.*t93.*2.0-c4.*t21.*t39.*2.0).*(1.0./2.0)-g.*m3.*t18-g.*m4.*t28-g.*m2.*t52-c1.*g.*m1.*t15;tau2+dth3.*(m4.*(t89-t27.*t42.*2.0+t37.*t85.*2.0-t35.*t88.*2.0).*(1.0./2.0)+m3.*(t82-t43.*t78.*2.0+t45.*t81.*2.0-c3.*t3.*t50.*2.0).*(1.0./2.0))+dth2.*(m4.*(t75-t37.*t42.*2.0-t35.*t68.*2.0+t37.*t66.*2.0).*(1.0./2.0)+m3.*(t72-t45.*t50.*2.0+t45.*t71.*2.0-t43.*t74.*2.0).*(1.0./2.0)+m2.*(t69+c2.*t6.*t58.*2.0-c2.*t6.*t64.*2.0-c2.*t13.*t62.*2.0).*(1.0./2.0))-m4.*(t39.*t66.*2.0-t42.*t68.*2.0).*(1.0./2.0)-m3.*(t47.*t71.*2.0-t50.*t74.*2.0).*(1.0./2.0)-m2.*(t58.*t60.*2.0-t62.*t64.*2.0).*(1.0./2.0)-dth4.*m4.*(t98-t37.*t93.*2.0+t35.*t97.*2.0-c4.*t21.*t39.*2.0).*(1.0./2.0)-g.*m4.*t35-g.*m3.*t43-c2.*g.*m2.*t13;tau3+dth2.*(m4.*(t89-t27.*t42.*2.0+t27.*t66.*2.0-t29.*t68.*2.0).*(1.0./2.0)+m3.*(t82-c3.*t3.*t50.*2.0+c3.*t3.*t71.*2.0-c3.*t5.*t74.*2.0).*(1.0./2.0))+dth3.*(m4.*(t89-t27.*t42.*2.0+t27.*t85.*2.0-t29.*t88.*2.0).*(1.0./2.0)+m3.*(t82-c3.*t3.*t50.*2.0-c3.*t5.*t78.*2.0+c3.*t3.*t81.*2.0).*(1.0./2.0))-m4.*(t39.*t85.*2.0-t42.*t88.*2.0).*(1.0./2.0)-m3.*(t47.*t81.*2.0-t50.*t78.*2.0).*(1.0./2.0)-dth4.*m4.*(t98-t27.*t93.*2.0+t29.*t97.*2.0-c4.*t21.*t39.*2.0).*(1.0./2.0)-g.*m4.*t29-c3.*g.*m3.*t5;tau4-m4.*(t39.*t93.*2.0-t42.*t97.*2.0).*(1.0./2.0)-dth2.*m4.*(t98-c4.*t21.*t39.*2.0+c4.*t21.*t68.*2.0-c4.*t24.*t66.*2.0).*(1.0./2.0)-dth3.*m4.*(t98-c4.*t21.*t39.*2.0+c4.*t21.*t88.*2.0-c4.*t24.*t85.*2.0).*(1.0./2.0)-dth4.*m4.*(t98-c4.*t21.*t39.*2.0-c4.*t24.*t93.*2.0+c4.*t21.*t97.*2.0).*(1.0./2.0)-c4.*g.*m4.*t21];