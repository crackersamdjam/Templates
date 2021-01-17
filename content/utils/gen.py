# Just run this program in the same directory as solution, judge (slow/correct one), and gen (to make data)

import subprocess as sub
import sys
from string import ascii_letters, ascii_lowercase, ascii_uppercase, digits
from random import *

TIMEOUT = 2  # Timeout in seconds
T = 1000

# Checker
def tokens_check(inp, sol_out, judge_out):
	return sol_out.split() == judge_out.split()

check = tokens_check


def compile_all():
	sol_p = 'mcco17p3.cpp'
	judge_p = 'main.cpp'
	gen_p = 'gen.cpp'
	def comp(path, alias, out_path):
		print(f'Compiling {alias} ({path})')
		sub.run(['g++', path, '--std=c++14', '-O2', '-o', out_path])
		# sub.run(['g++', path, '-H', '--std=c++14', '-O2', '-DLOCAL', '-DSTRESS', '-o', out_path])
	comp(sol_p, 'Solution', 'sol.out')
	comp(judge_p, 'Judge', 'judge.out')
	comp(gen_p, 'Gen', 'gen.out')

compile_all()


for test_no in range(T):
	inp = ''

	# Generate Input
	# inp = f'{randint(1, 10)} {randint(1, 10)}\n'
	inp = sub.run(['./gen.out'], capture_output=True, text=True, input=inp, timeout=TIMEOUT).stdout

# Running code
	with open('tmpin', 'w') as f:
		f.write(inp)
	
	judge_p = sub.run(['./judge.out'], capture_output=True, text=True, input=inp, timeout=TIMEOUT)
	sol_p = sub.run(['./sol.out'], capture_output=True, text=True, input=inp, timeout=TIMEOUT)

	# RE
	def check_return(out, alias):
		bad = False
		if out.returncode:
			print(f'Case {test_no} ERROR:')
			print(f'{alias} got non-zero return code {out.returncode}')
			bad = True
		if out.stderr:
			print(f'Case {test_no} ERROR:')
			print(f'{alias} got stderr:', out.stderr, sep='\n')
			bad = True
		if bad:
			print('', 'Input:', inp, sep='\n')
			sys.exit(-1)
	check_return(judge_p, 'Judge')
	check_return(sol_p, 'Solution')

	# WA
	out = sol_p.stdout
	expected = judge_p.stdout
	if not check(inp, out, expected):
		print(f'Got case {test_no} wrong! Expected:', expected, 'Got:', out, 'Input:', inp, sep='\n')
	else:
		clipped_in = inp[:10].split('\n')[0]
		# clipped_in = ''
		print(f'Case {test_no} correct! (Inp: {clipped_in}...)')
