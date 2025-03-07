a_1 = int(input())
a_2 = int(input())
c = 0
l = []
f = []
for n in range(a_1, a_2 + 1):
    for d in range(1, a_2 + 1):
        if n % d == 0:
            c = c+1
    if c == 2:
        l.append(n)
    c = 0
for i in range(len(l)):
  e = l[i]
  if e >= 100:
    c = e //100
    d = e % 100 // 10
    u = e % 10
    f.append(c+d+u)
  elif e >= 10:
    d = e // 10
    u = e % 10
    f.append(d+u)
  elif e >= 1000:
    dm = e //1000
    c = e % 1000 // 100
    d = e % 100 //10
    u = e % 10
    f.append(dm+c+d+u)
  else:
    f.append(e)
for j in range(len(f)):
    print(f[j])