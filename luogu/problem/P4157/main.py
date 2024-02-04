import math
def check(t):
    return t-(1+math.log(t))*n <0

n=int(input())
l=2
r=0x3f3f3f3f
while (l+0.1 < r):
    mid=(l+r)/2
    if (check(mid)):
        l = mid
    else:
        r = mid
t=l
print(t)
