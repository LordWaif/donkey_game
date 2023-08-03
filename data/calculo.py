und = [0.00390625,0.001953125]

s_e = [173,8]
s_d = [226,8]
i_e = [173,54]
i_d = [226,54]

for i in range(0,2):
      s_e[i] *= und[i]
      s_d[i] *= und[i]
      i_e[i] *= und[i]
      i_d[i] *= und[i]

print(i_d)
print(i_e)
print(s_e)
print(s_d)

