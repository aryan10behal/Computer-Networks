# Import the necessary modules
import matplotlib.pyplot as plt
import csv

# opening the CSV file
Throughput = []
Time = []
i = 2
h = 126
while i <= h:
    with open('data_file.csv', mode='r')as file:
        # reading the CSV file
        csvFile = csv.reader(file)
        next(csvFile)
        Time.append(i)
        length = 0
        for lines in csvFile:
            if i > float(lines[1]) >= i-2:
                length = length + float(lines[5])
        Throughput.append(length/2)
        i = i+2

print(Throughput)
print(Time)

plt.plot(Time, Throughput)
plt.xlabel('Time')
# naming the y axis
plt.ylabel('Throughput')

# giving a title to my graph
plt.title('Graph')
# Show the plot
plt.show()
