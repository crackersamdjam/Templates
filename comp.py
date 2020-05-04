import subprocess as sub

sol_p = 'mcco17p3.cpp'
judge_p = 'main.cpp'
gen_p = 'gen.cpp'

def comp(path, alias, out_path):
    print(f'Compiling {alias} ({path})')
    sub.run(['g++', path, '--std=c++14', '-O2', '-o', out_path])
    # sub.run(['g++', path, '-O2', '-DLOCAL', '-DSTRESS', '-o', out_path])

comp(sol_p, 'Solution', 'sol.out')
comp(judge_p, 'Judge', 'judge.out')
comp(gen_p, 'Gen', 'gen.out')
