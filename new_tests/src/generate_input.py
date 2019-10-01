import sys

input_type = int(sys.argv[1])
input_size = int(sys.argv[2])
allocations_count = int(sys.argv[3])

input_sizes = list()
if input_type == 1:
	for i in range(allocations_count):
		input_sizes.append(input_size)

with open('src/input_sizes.txt', 'w') as f:
	for item in input_sizes:
		f.write("%s " % item)
