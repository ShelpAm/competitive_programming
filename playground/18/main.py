n=int(input())
res=0
for i in range(n):
    m=input().split()
    if m[1]=="pink":
        res+=int(m[0])
print(res)
