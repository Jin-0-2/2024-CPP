#include"todo.h"

int main() {
    TodoList todoList;

    setlocale(LC_ALL, "korean");    // �ѱ��� ��ġ

    todoList.loadFromBinaryFile("todolist.bin");

    // ���α׷� ���� �� ��ü ����Ʈ ���

    while (true) {
        system("cls");
        // TodoList ��� ��� ���� �߰��� �� ����
        todoList.displayAllList();
        wcout << L"-------------------------" << endl;
        wcout << L"[1] �� �� �߰�\n[2] �� �� ����\n[3] �� �� ����" << endl;
        wcout << L"[4] �� �� �Ϸ�� ǥ��\n[5] Ư�� ��¥�� ����Ʈ ���\n[6] �����ϰ� ����\n";
        int choice;
        wcout << L"��ȣ �Է� : ";
        cin >> choice;
        wcout << L"-------------------------" << endl;

        switch (choice) {
        case 1: {
            system("cls");
            wcout << L"�߰��� �� ���� �Է��ϼ���: ";
            wstring task;
            wcin.ignore(); // ���� �Է� ���۸� ���� ���� ���
            getline(wcin, task);
            wcout << L"��¥�� �Է��ϼ��� (��: 2024-04-01): ";
            wstring date;
            wcin >> date;
            todoList.addItem(task, date);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            todoList.displayAllList();
            wcout << L"������ �� ���� ��¥�� �Է��ϼ��� (��: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"������ �� ���� �ε����� �Է��ϼ���: ";
            int index;
            wcin >> index;
            wcout << L"������ ������ �Է��ϼ���: ";
            wstring task;
            wcin.ignore(); // ���� �Է� ���۸� ���� ���� ���
            getline(wcin, task);
            todoList.updateItem(date, index - 1, task); // �ε����� 1���� �������� �ʵ��� ����
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            todoList.displayAllList();
            wcout << L"������ �� ���� ��¥�� �Է��ϼ��� (��: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"������ �� ���� �ε����� �Է��ϼ���: ";
            int index;
            wcin >> index;
            todoList.deleteItem(date, index - 1); // �ε����� 1���� �������� �ʵ��� ����
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            todoList.displayAllList();
            wcout << L"�� �� �Ϸ�� ǥ���� ��¥�� �Է��ϼ��� (��: 2024-04-01): ";
            wstring date;
            wcin >> date;
            wcout << L"�� �� �Ϸ�� ǥ���� �ε����� �Է��ϼ���: ";
            int index;
            wcin >> index;
            todoList.markAsCompleted(date, index - 1); // �ε����� 1���� �������� �ʵ��� ����
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            wcout << L"����Ʈ�� ����� ��¥�� �Է��ϼ��� (��: 2024-04-01): ";
            wstring date;
            wcin >> date;
            todoList.displayListByDate(date);
            system("pause");
            break;
        }
        case 6: {
            todoList.saveToBinaryFile("todolist.bin");
            wcout << L"����Ǿ����ϴ�." << endl;
            wcout << L"���α׷��� �����մϴ�." << endl;
            return 0;
        }
        default:
            wcout << L"�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0;
}
