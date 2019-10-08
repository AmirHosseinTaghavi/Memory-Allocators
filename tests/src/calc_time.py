import sys

number_of_threads = int(sys.argv[1])


with open('src/result.txt') as f:
    all_threads_times = f.read().splitlines()

if not (len(all_threads_times) / number_of_threads).is_integer():
	print('error')
	exit()

counter = 0
programs_times = list()
max_time_of_program = 0
for thread_time in all_threads_times:
	thread_time = float(thread_time)
	counter += 1
	if thread_time > max_time_of_program:
		max_time_of_program = thread_time
	if counter == number_of_threads:
		programs_times.append(max_time_of_program)
		counter = 0
		max_time_of_program = 0

print('number of execs: ', len(programs_times))

average_exec_time = sum(programs_times) / float(len(programs_times))

print('average exec time: ', average_exec_time)
		
		



