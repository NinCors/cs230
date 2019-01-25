import matplotlib.pyplot as plt


processors = [2,4,8,16,32,64]

x = []
for i in range(1,2049):
    x.append(i)
print x

for p in processors:
    fileName = "Datafor"+str(p)
    time = []
    tmp = ''
    with open(fileName)as f:
        tmp = f.readlines()
    
    for t in tmp:
        t = t.replace("\n",'')
        time.append(float(t)) 
    
    plt.plot(x,time)
    plt.xlabel("Memory")
    plt.ylabel("Average wait time")

    plt.title("Graph for processor " + str(p))
    plt.show()