#!/usr/bin/python
import os
import subprocess as sub

fast = 'fast.cpp'
slow = 'slow.cpp'
gen = 'gen.cpp'

def comp(path, out_path):
	print(f'Compiling ({path})')
	sub.run(['g++', path, '-DLOCAL', '--std=c++17', '-O2', '-march=native', '-o', out_path])

comp(fast, 'fast')
comp(slow, 'slow')
comp(gen, 'gen')

case = 0
while 1:
	case += 1
	os.system(f'./gen {case} > in')
	os.system('./fast < in > out1')
	os.system('./slow < in > out2')
	if open('out1').read() != open('out2').read():
		print('WA test '+str(case))
		exit(0)
	print("AC test "+str(case))