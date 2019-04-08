# Import PuLP modeller functions
from pulp import *
import math

def prob1():
    pointsList=[(1, 3),(2, 5),(3, 7),(5, 11),(7, 14),(8, 15),(10, 19)]

    a = LpVariable("a")
    b = LpVariable("b")
    max_E=LpVariable("max")

    varArr=[]

    j=0
    for p in pointsList:
        v=LpVariable("E"+str(j))
        varArr.append(v)
        j=j+1

    prob = LpProblem("p1",LpMinimize)

    prob += max_E #obeject

    i=0
    for p in pointsList: #constraints
        prob += a*p[0]+b-p[1] <= varArr[i]
        prob += -a*p[0]-b+p[1] <= varArr[i]
        prob += varArr[i] >=0
        prob += varArr[i] <=max_E
        i=i+1

    status = prob.solve()
    LpStatus[status]
    print(LpStatus[status])
    print("MAX is "+str(value(max_E)))
   
   
    print("a is "+str(value(a)))
    print("b is "+str(value(b)))

def readFile(weather):
    with open("Corvallis.csv","r") as ins:
        i = 0
        for line in ins:
            if(i!=0):
                newline=line.strip('\n')
                tokenlized=newline.split(';') #split text
                temp = tokenlized[7]
                day = tokenlized[8]
                weather.append((int(day),float(temp))) #x is day, y is real temperature

            i+=1

def prob2(weather):
    x0=LpVariable("x0")
    x1=LpVariable("x1")
    x2=LpVariable("x2")
    x3=LpVariable("x3")
    x4=LpVariable("x4")
    x5=LpVariable("x5") #6 variables

    max_E=LpVariable("max")
    varArr=[]

    # j=0
    # for p in weather:
    #     v=LpVariable("E"+str(j))
    #     varArr.append(v)
    #     j=j+1

    prob = LpProblem("p2",LpMinimize)

    prob += max_E #obeject
    i=0
    for p in weather: #constraints
        A=2*math.pi*p[0]/365.25
        B=2*math.pi*p[0]/(365.25*10.7)
        prob += x0 + x1*p[0] +x2*math.cos(A) +x3*math.sin(A) +x4*math.cos(B) +x5*math.sin(B)-p[1]<= max_E
        prob += -(x0 + x1*p[0] +x2*math.cos(A) +x3*math.sin(A) +x4*math.cos(B) +x5*math.sin(B)-p[1])<= max_E
        prob += max_E >=0


    status = prob.solve()
    print(LpStatus[status])
    print("Max is " + str(value(max_E)))
    print("x0 is "+str(value(x0)))
    print("x1 is "+str(value(x1)))
    print("x2 is "+str(value(x2)))
    print("x3 is "+str(value(x3)))
    print("x4 is "+str(value(x4)))
    print("x5 is "+str(value(x5)))
   

def main():
    print("Problem1 ")
    prob1()
    print("Problem2,please wait for 30 seconds")
    weather=[]
    readFile(weather)
    prob2(weather)

main()