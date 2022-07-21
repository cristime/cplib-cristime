import os
import platform
import filecmp
import shutil
import time

test_num = 10
prop = [
    (100, 100, 50),
    (1000, 1000, 50),
    (10000, 10000, 100),
    (50000, 10000, 100),
    (50000, 50000, 100),
    (75000, 75000, 100),
    (75000, 75000, 200),
    (75000, 75000, 300),
    (100000, 100000, 200),
    (100000, 100000, 300)
]


def Compile():
    print("### Compile the codes ###")

    # Compile the code
    print("g++ gen.cpp -o gen -std=c++14 -O2")
    os.system("g++ gen.cpp -o gen -std=c++14 -O2")
    print("g++ std.cpp -o std -std=c++14 -O2")
    os.system("g++ std.cpp -o std -std=c++14 -O2")
    print("g++ test.cpp -o test -std=c++14 -O2")
    os.system("g++ test.cpp -o test -std=c++14 -O2")


def GenTest(plat: str):
    # Generating the test cases
    print()
    print("### Generating the test cases ###")
    if os.path.isdir("in") == False:
        os.mkdir("in")
    for i in range(1, 5 + 1):
        print("Generating test case {}......".format(i), end="")
        if plat == "Windows":
            command = "gen.exe {} {} {} in\\input{}.txt".format(
                prop[i-1][0], prop[i-1][1], prop[i-1][2], i)
        else:
            command = "./gen {} {} {} in/input{}.txt".format(
                prop[i-1][0], prop[i-1][1], prop[i-1][2], i)
        startTime = time.perf_counter()
        os.system(command)
        endTime = time.perf_counter()
        print("Succeeded!", end="\t")
        print("Time used: {}ms".format(int((endTime - startTime) * 1000)))


def RunStd(plat: str):
    # Run std code
    print()
    print("### Run std code ###")
    if os.path.isdir("out") == False:
        os.mkdir("out")
    for i in range(1, test_num + 1):
        print("Running test case {}......".format(i), end="")
        if plat == "Windows":
            command = "std.exe in\\input{}.txt out\\output{}.txt".format(i, i)
        else:
            command = "./std in/input{}.txt out/output{}.txt".format(i, i)
        startTime = time.perf_counter()
        os.system(command)
        endTime = time.perf_counter()
        print("Succeeded!", end="\t")
        print("Time used: {}ms".format(int((endTime - startTime) * 1000)))


def RunTest():
    # Run the test
    print("\n### Running test ###")

    if os.path.isdir("test_out") == False:
        os.mkdir("test_out")

    for i in range(1, test_num + 1):
        print("Running test case {}......".format(i), end="")
        if platform.system() == "Windows":
            command = "test.exe in\\input{}.txt test_out\\output{}.txt".format(
                i, i)
        else:
            command = "test in/input{}.txt test_out/output{}.txt".format(i, i)
        startTime = time.perf_counter()
        os.system(command)
        endTime = time.perf_counter()
        print("Succeeded!", end="\t")
        print("Time used: {}ms".format(int((endTime - startTime) * 1000)))


def DiffFile():
    # Diff the output file
    print("\n### Diff the output file ###")

    for i in range(1, test_num + 1):
        print("Diffing test case {}......".format(i), end="")
        if filecmp.cmp("out/output{}.txt".format(i), "test_out/output{}.txt".format(i)) == False:
            print("\n\nTest case {} failed!".format(i))
            return False
        print("Succeeded!")

    return True


def CleanUp(plat: str):
    # Clean up the test output file
    shutil.rmtree("test_out")
    shutil.rmtree("in")
    shutil.rmtree("out")
    if os.path.isdir("__pycache__"):
        shutil.rmtree("__pycache__")
    if plat == "Windows":
        os.remove("gen.exe")
        os.remove("std.exe")
        os.remove("test.exe")
    else:
        os.remove("gen")
        os.remove("std")
        os.reamove("test")


if __name__ == "__main__":
    plat = platform.system()
    Compile()
    GenTest(plat)
    RunStd(plat)
    RunTest()
    if DiffFile() == True:
        print("\nAll test passed!")
    CleanUp(plat)
