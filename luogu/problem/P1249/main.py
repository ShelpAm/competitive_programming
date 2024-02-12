n=int(input())

if n==1:
    print("1\n1")
elif n==2:
    print("2\n2")


sum=0
list=[]
for i in range(2,n):
    if sum+i>n:
        break
    sum+=i
    list.append(i)
r=n-sum
l=len(list)
if r>l:
    incre=int(r/l)
    for i,k in enumerate(list):
        list[i]+=incre
    r%=l
for i in range(r):
    list[l-1-i]+=1

print(*list, end='\n')
product=1
for e in list:
    product*=e
print(product)
