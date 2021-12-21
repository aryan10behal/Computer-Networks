import matplotlib.pyplot as plt
f = open("tcp-example_Q4.tr", 'r')
lines = f.readlines()


x_list = []
y_list = []
queue = []


for line in lines:
    tokens = line.split(" ")
    x = tokens[2]
    y = x.split("/")
    z = y[2]
    # checking if listnode is N0
    if z == '1':
        if tokens[0] == '+':
            queue.append(float(tokens[1]))
        if tokens[0] == '-':
            x_list.append(float(tokens[1]))
            y_list.append(float(tokens[1]) - queue.pop(0))

plt.plot(x_list, y_list)
plt.title("Q4")
plt.xlabel("Time(sec)")
plt.ylabel("Queuing Delay(sec)")
plt.show()


