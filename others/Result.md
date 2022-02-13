$$
\Delta v_n=v_{n+1}-v_n=(n+1)u_{n+1}\\
s_n=nu_n
$$

$$
\begin{align*}
\Phi(s)_n&=(n+2)u_{n+2}-a(n+1)u_{n+1}-bnu_n\\
&=2u_{n+2}-au_{n+1}\\
\Phi^2(s)_n&=0\\
\implies \Phi^2(\Delta v)&=0 \\
\Phi^2(\Delta w)_n&=\Phi(\Delta w)_{n+2}-a\Phi(\Delta w)_{n+1}-b\Phi(\Delta w)_{n}\\
&=\Delta w_{n+4}-a\Delta w_{n+3}-b\Delta w_{n+2}-a\Delta w_{n+3}+a^2\Delta w_{n+2}+ab\Delta w_{n+1}\\
& \quad -b\Delta w_{n+2}+ab\Delta w_{n+1}+b^2\Delta w_{n}\\
&=\Delta w_{n+4}-2a\Delta w_{n+3}+ (a^2-2b)\Delta w_{n+2} +2ab\Delta w_{n+1}+b^2\Delta w_n\\
&=w_{n+5}-(1+2a)w_{n+4}+(a^2-2b+2a)\Delta w_{n+3}+(2ab-a^2+2b)w_{n+2}\\
&\quad +(b^2-2ab)w_{n+1}-b^2w_n
\end{align*}
$$

