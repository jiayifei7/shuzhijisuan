import math
x=float(input())
x=math.fmod(x, 2*math.pi)
def solve(x):
    i=1;
    sum=0;
    term=x;
    while(abs(term)>1e-3):
        sum+=term
        term*=-x*x/(2*i)/(2*i+1)
        i+=1
    sum+=term
    return round(sum,8)
print(solve(x))
