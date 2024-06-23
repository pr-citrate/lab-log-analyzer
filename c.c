#include <stdbool.h>
#include <stdio.h>
#define STUDENTS 60

int main() {
  int n, cnt = 0;
  bool student[STUDENTS + 1] = {
      false};  // 학생 ID는 1부터 60까지이므로 크기를 61로 설정
  bool problem[STUDENTS + 1] = {
      false};  // 허가받지 않은 학생을 추적하기 위한 배열
  int startTime = 0, endTime = 0;  // 시작 시간과 종료 시간을 추적하기 위한 변수

  scanf("%d", &n);  // 로그의 개수를 입력받음
  scanf(" [");

  for (int i = 0; i < n; i++) {
    bool isEnter, isApproved;
    char enter[6], approved[6];
    int time, id;

    // 로그 항목을 파싱함
    scanf(
        " { \"isEnter\": %5[^,], \"time\": %d, \"id\": %d, \"isApproved\": "
        "%5[^}] }",
        enter, &time, &id, approved);

    if (i < n - 1) {
      scanf(" ,");  // 마지막 항목이 아닌 경우 쉼표를 읽음
    }

    isEnter = (enter[0] == 't');  // "true"는 true로, "false"는 false로 변환
    isApproved = (approved[0] == 't');

    // 출입 논리를 처리함
    if (isEnter) {
      cnt += 1;  // 현재 실험실에 있는 학생 수를 증가시킴
      if (!isApproved) {
        student[id] = true;  // 허가받지 않은 학생을 기록
        problem[id] = true;  // 문제 학생으로 설정
      }
      if (cnt == 11) {
        startTime = time;  // 최대 인원을 초과하는 시작 시간을 설정
      }
    } else {
      if (student[id]) {
        student[id] = false;  // 학생이 나갔음을 기록
      }
      cnt -= 1;  // 현재 실험실에 있는 학생 수를 감소시킴
      if (cnt == 10 && startTime != 0) {
        endTime = time;  // 최대 인원을 초과하는 종료 시간을 설정
        printf("%d %d ", startTime, endTime);

        // 문제 학생들을 출력함
        bool first = true;
        for (int j = 1; j <= STUDENTS; j++) {
          if (problem[j]) {
            if (!first) {
              printf(",");
            }
            printf("%d", j);
            first = false;
          }
        }
        printf("\n");

        // 문제 배열을 리셋함
        for (int j = 1; j <= STUDENTS; j++) {
          problem[j] = student[j];  // 현재 실험실에 있는 문제 학생들을 유지함
        }
        startTime = 0;  // 시작 시간을 리셋
        endTime = 0;    // 종료 시간을 리셋
      }
    }
  }

  scanf(" ]");  // 입력의 끝을 읽음

  return 0;  // 프로그램 종료
}
