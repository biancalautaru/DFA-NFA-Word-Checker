# Temă laborator limbaje formale și automate

## Cerințe

- Fiind date niște fișiere de configurare de forma regăsită în Appendix, scrieți un script sau o librărie prin care validați dacă automatul descris este un DFA.
- Fiind date niște fișiere de configurare de forma regăsită în Appendix, scrieți un script sau o librărie prin care testați dacă DFA-ul descris în acel fișier de configurare acceptă un string s sau nu.

- Fiind date niște fișiere de configurare de forma regăsită în Appendix, scrieți un script sau o librărie prin care validați dacă automatul descris este un NFA.
- Fiind date niște fișiere de configurare de forma regăsită în Appendix, scrieți un script sau o librărie prin care testați dacă NFA-ul descris în acel fișier de configurare acceptă un string s sau nu.

## Appendix
```
# This is an example of the configuration file and a comment
Sigma:
a
b
c
End
#
#
States:
q0, S
q1
q2
q3
q4, F
q5
End
# another comment
#
Transitions:
q0, a, q1
q0, b, q2
q0, c, q3
q1, b, q2
q2, a, q3
q1, c, q4
q2, b, q4
q3, a, q4
q4, a, q5
q5, a, q4
End
```
