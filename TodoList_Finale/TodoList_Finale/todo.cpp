#include"todo.h"

int main() {
    TodoList todoList;

    setlocale(LC_ALL, "korean");    // 한국어 패치

    todoList.loadFromBinaryFile("todolist.bin");

    // 프로그램 실행 시 전체 리스트 출력

    while (true) {
        system("cls");
        // TodoList 출력 기능 등을 추가할 수 있음
        todoList.displayAllList();
        wcout << L"-------------------------" << endl;
        wcout << L"[1] 할 일 추가\n[2] 할 일 수정\n[3] 할 일 삭제" << endl;
        wcout << L"[4] 할 일 완료로 표시\n[5] 특정 날짜의 리스트 출력\n[6] 저장하고 종료\n";
        int choice;
        wcout << L"번호 입력 : ";
        cin >> choice;
        wcout << L"-------------------------" << endl;

        switch (choice) {
        case 1: {
            system("cls");
            wcout << L"추가할 할 일을 입력하세요: ";
            wstring task;
            wcin.ignore(); // 이전 입력 버퍼를 비우기 위해 사용
            getline(wcin, task);
            wcout << L"날짜를 입력하세요 (예: 2024-04-01): ";
            wstring date;
            wcin >> date;
            todoList.addItem(task, date);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            todoList.displayAllList();
            wcout << L"수정할 할 일의 날짜를 입력하세요 (예: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"수정할 할 일의 인덱스를 입력하세요: ";
            int index;
            wcin >> index;
            wcout << L"수정할 내용을 입력하세요: ";
            wstring task;
            wcin.ignore(); // 이전 입력 버퍼를 비우기 위해 사용
            getline(wcin, task);
            todoList.updateItem(date, index - 1, task); // 인덱스는 1부터 시작하지 않도록 주의
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            todoList.displayAllList();
            wcout << L"삭제할 할 일의 날짜를 입력하세요 (예: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"삭제할 할 일의 인덱스를 입력하세요: ";
            int index;
            wcin >> index;
            todoList.deleteItem(date, index - 1); // 인덱스는 1부터 시작하지 않도록 주의
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            todoList.displayAllList();
            wcout << L"할 일 완료로 표시할 날짜를 입력하세요 (예: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"할 일 완료로 표시할 인덱스를 입력하세요: ";
            int index;
            wcin >> index;
            todoList.markAsCompleted(date, index - 1); // 인덱스는 1부터 시작하지 않도록 주의
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            wcout << L"리스트를 출력할 날짜를 입력하세요 (예: 2024-04-01): ";
            wstring date;
            wcin >> date;
            todoList.displayListByDate(date);
            system("pause");
            break;
        }
        case 6: {
            todoList.saveToBinaryFile("todolist.bin");
            wcout << L"저장되었습니다." << endl;
            wcout << L"프로그램을 종료합니다." << endl;
            return 0;
        }
        default:
            wcout << L"잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}
