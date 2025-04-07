import os
import EquGrader
from os import path

def run_binary():
    os.system(f"{os.path.dirname(__file__)}/../4_ThreadCalc/bin/threadcalc ./threadcalc_tests/unsolved ./threadcalc_tests/solved")


def main():
    result = 0
    tests_base =  "./threadcalc_tests/"
    num_files = 16
    num_equ = 64

    EquGrader.setup(tests_base, num_files, num_equ)
    run_binary()
    result = EquGrader.grade_dirs(tests_base)
    EquGrader.cleanup(tests_base)

    return result

if __name__ == "__main__":
    result = main()
    exit(abs(result))
