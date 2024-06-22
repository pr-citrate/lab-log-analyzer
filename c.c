#include <stdbool.h>
#include <stdio.h>

int main() {
  int n, cnt = 0;
  bool student[20] = {false};
  bool problem[20] = {false};
  int startTime = 0, endTime = 0;

  scanf("%d", &n);
  scanf(" [");

  for (int i = 0; i < n; i++) {
    bool isEnter, isApproved;
    char enter[6], approved[6];
    int time, id;

    // parse
    scanf(
        " { \"isEnter\": %5[^,], \"time\": %d, \"id\": %d, \"isApproved\": "
        "%5[^}] }",
        enter, &time, &id, approved);

    if (i < n - 1) {
      scanf(" ,");
    }

    isEnter = (enter[0] == 't');
    isApproved = (approved[0] == 't');

    // logic
    if (isEnter) {
      cnt += 1;
      if (!isApproved) {
        student[id] = true;
        problem[id] = true;
      }
      if (cnt == 11) {
        startTime = time;
      }
    } else {
      if (student[id]) {
        student[id] = false;
      }
      cnt -= 1;
      if (cnt == 10 && startTime != 0) {
        endTime = time;
        printf("%d %d ", startTime, endTime);

        // print problematic students
        bool first = true;
        for (int j = 0; j < 20; j++) {
          if (problem[j]) {
            if (!first) {
              printf(",");
            }
            printf("%d", j);
            first = false;
          }
        }
        printf("\n");

        // reset problem array
        for (int j = 0; j < 20; j++) {
          problem[j] = student[j];
        }
        startTime = 0;
        endTime = 0;
      }
    }
  }

  scanf(" ]");

  return 0;
}
