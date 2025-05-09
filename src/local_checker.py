#!/usr/bin/env python3

import argparse
import subprocess
import os
import sys
import re

#============================== ARGUMENTS ==============================#

argParser = argparse.ArgumentParser(description="Python Checker for PCLP2 Homework 3", prog="python3 checker.py")
group = argParser.add_mutually_exclusive_group()
group.add_argument("-t", "--task", help="Run tests for a certain task.")
group.add_argument("--all", action="store_true", help="Run all tasks.")
group.add_argument("--zip", action="store_true", help="Make zip file for VMChecker.")
group.add_argument("--linter", action="store_true", help="Run only the linter.")
argParser.add_argument("--no_clean", action="store_false", help="Do not clean outputs after run")
args = argParser.parse_args()

if len(sys.argv) == 1:
    argParser.print_help()
    exit(0)

#============================== CONSTANTS ==============================#

tasksNo = 4

runExec = "./"
checker = "checker"
taskDir = "task-"
linterDir = "linter"
readme_path = "README.md"

zipName = "VMChecker_Homework_3"

useShell = True

header = "========================== Tema 3 PCLP2 =========================\n"
#============================== FUNCTIONS ==============================#

def test_task(taskNo):
    global points

    taskString = f"{taskDir}{taskNo}/"
    procString = runExec + taskString + checker
    rc = subprocess.call(f"make -C {taskString}", shell=useShell)

    if rc != 0:
        sys.stderr.write("make failed with status %d\n" % rc)
        return

    if not os.path.exists(procString):
        sys.stderr.write("The file %s is missing and could not be created with \'make\'" % (taskString + checker))
        return

    checkerOutput = str(subprocess.check_output(f"cd {taskString} && ./checker", shell=useShell), encoding='utf-8')

    print(checkerOutput)
    taskScore = re.findall(fr'\d+', re.findall(fr'TASK {taskNo} SCORE: \d+', checkerOutput)[0])[1]

    points += float(taskScore)

    if args.no_clean:
        rc = subprocess.call(f"make -C {taskString} clean", shell=useShell)

def run_linter():
    global linter_weight
    passed_linter = True
    source_list = ['task-1/sortari.asm', 'task-2/operatii.asm', 'task-3/kfib.asm', 'task-4/composite_palindrome.asm']

    print("============================ LINTER =============================\n")

    for source in source_list:
        checkerOutput = str(subprocess.check_output(f"cd {linterDir} && ./linter-script-file ../{source}", shell=useShell), encoding='utf-8')
        if len(checkerOutput) > 0:
            passed_linter = False
            print(f'Linter errors in: {source}')
            print(checkerOutput)

    if passed_linter:
        print(f"PASSED LINTER CHECK")
    else:
        linter_weight = 0
        print("FAILED LINTER CHECK")

def check_readme():
    global readme_weight
    passed_readme = True

    print("============================ README =============================\n")

    if not os.path.isfile(readme_path):
        passed_readme = False

    if passed_readme:
        print(f"PASSED README CHECK")
    else:
        readme_weight = 0
        print("FAILED README CHECK")
#=======================================================================#

if args.zip:
    rc = subprocess.call(f"zip -r {zipName} */*.asm README.md", shell=useShell)
    exit(rc)

points = 0
linter_weight = 1
readme_weight = 1

if args.linter:
    run_linter()
    exit(0)

print("\n" + header)



#================================ TESTS ================================#

if args.task == None and args.all:
    for task in range(1, tasksNo + 1):
        test_task(task)
    run_linter()
    check_readme()
elif args.task != None:
    test_task(re.findall(r'\d', args.task)[0])


print(f"====================== Total: {points * linter_weight * readme_weight} / 100 ========================\n")
