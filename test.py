import subprocess

# 프로젝트 폴더와 테스트 폴더 경로
project_folder = "."
test_folder = "./test"

# 테스트 케이스 파일 목록과 결과 파일 목록
test_files = [
    "case1.txt",
    "case2.txt",
    "case3.txt",
    "case4.txt",
    "case5.txt",
]

result_files = [
    "result1.txt",
    "result2.txt",
    "result3.txt",
    "result4.txt",
    "result5.txt",
]

# C 프로그램 실행 파일 경로
c_program = f"{project_folder}/c.exe"


def run_test(test_file, result_file):
    # 테스트 케이스 파일 읽기
    with open(f"{test_folder}/{test_file}", "r") as f:
        test_input = f.read()

    # 예상 결과 파일 읽기
    with open(f"{test_folder}/{result_file}", "r") as f:
        expected_output = f.read().strip()

    # C 프로그램 실행
    process = subprocess.Popen(
        c_program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    stdout, stderr = process.communicate(input=test_input.encode())

    # 프로그램 출력
    output = stdout.decode().strip()

    # 결과 비교
    if output == expected_output:
        print(f"\033[32m{test_file} PASSED\033[39m")
        print()
        return True
    else:
        print(f"\033[31m{test_file} FAILED\033[39m")
        print("\033[33mExpected:\033[39m")
        print(expected_output)
        print("\033[33mGot:\033[39m")
        print(output)
        print()
        return False


cnt = 0
passed = 0

# 모든 테스트 케이스 실행
for test_file, result_file in zip(test_files, result_files):
    passed += run_test(test_file, result_file)
    cnt += 1

print(f"\033[36m{passed}/{cnt} test cases passed.\033[39m")
