import sys
import random

input_type = int(sys.argv[1])
input_size = int(sys.argv[2])
allocations_count = int(sys.argv[3])
input_size_end = int(sys.argv[4])

input_sizes = list()
if input_type == 1:
	for i in range(allocations_count):
		input_sizes.append(input_size)
elif input_type == 2:
	for i in range(allocations_count):
		input_sizes.append(random.randint(input_size, input_size_end))

with open('src/input_sizes.txt', 'w') as f:
	for item in input_sizes:
		f.write("%s " % item)
