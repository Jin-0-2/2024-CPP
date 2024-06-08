#include "todo.h"

void TodoList::addItem(const wstring& task, const wstring& date) {
    TodoItem newItem;
    newItem.set_task(task);
    newItem.set_completed(false);
    dateToItems[date].push_back(newItem);
    wcout << L"�� ���� �߰��Ǿ����ϴ�." << endl;
}

void TodoList::updateItem(const wstring& date, int index, const wstring& task) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date][index].set_task(task);
        wcout << L"�� ���� �����Ǿ����ϴ�." << endl;
    }
    else {
        wcout << L"�߸��� ��¥ �Ǵ� �ε����Դϴ�." << endl;
    }
}

// �� �� ����
void TodoList::deleteItem(const wstring& date, int index) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date].erase(dateToItems[date].begin() + index);
        wcout << L"�� ���� �����Ǿ����ϴ�." << endl;

        if (dateToItems[date].empty()) {
            dateToItems.erase(date);
        }
    }
    else {
        wcout << L"�߸��� ��¥ �Ǵ� �ε����Դϴ�." << endl;
    }
}

// �� �� �Ϸ�� ǥ��
void TodoList::markAsCompleted(const wstring& date, int index) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date][index].set_completed(true);
        wcout << L"�� ���� �Ϸ�� ǥ�õǾ����ϴ�." << endl;
    }
    else {
        wcout << L"�߸��� ��¥ �Ǵ� �ε����Դϴ�." << endl;
    }
}

// Ư�� ��¥�� To-Do ����Ʈ ���
void TodoList::displayListByDate(const wstring& date) {
    wcout << date << L"�� To-Do ����Ʈ:" << endl;
    if (dateToItems.find(date) != dateToItems.end()) {
        for (size_t i = 0; i < dateToItems[date].size(); ++i) {
            wcout << i + 1 << L". ";
            if (dateToItems[date][i].get_completed()) {
                wcout << L"[�Ϸ�] ";
            }
            wcout << dateToItems[date][i].get_task() << endl;
        }
    }
    else {
        wcout << L"�ش� ��¥�� �� ���� �����ϴ�." << endl;
    }
}

// ��ü To-Do ����Ʈ ���
void TodoList::displayAllList() {
    if (dateToItems.empty()) {
        wcout << L"����Ʈ�� ������ϴ�." << endl;
        return;
    }

    wcout << L"��ü To-Do ����Ʈ:" << endl;
    for (auto& pair : dateToItems) {
        wcout << pair.first << L":" << endl;
        for (size_t i = 0; i < pair.second.size(); ++i) {
            wcout << i + 1 << L". ";
            if (pair.second[i].get_completed()) {
                wcout << L"[�Ϸ�] ";
            }
            wcout << pair.second[i].get_task() << endl;
        }
        wcout << endl;
    }
}

// ���� ���Ϸ� ����
void TodoList::saveToBinaryFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        wcout << L"������ �� �� �����ϴ�." << endl;
        return;
    }

    for (const auto& pair : dateToItems) {
        // ��¥ ����
        wstring date = pair.first;
        int dateLength = date.size();
        file.write(reinterpret_cast<const char*>(&dateLength), sizeof(int));
        file.write(reinterpret_cast<const char*>(date.c_str()), dateLength * sizeof(wchar_t));

        // ������ ���� ����
        int itemCount = pair.second.size();
        file.write(reinterpret_cast<const char*>(&itemCount), sizeof(int));

        for (const auto& item : pair.second) {
            // �� �� ����
            item.writeBinary(file);
        }
    }
    char endMarker = 'X';
    file.write(&endMarker, sizeof(char));

    file.close();
    wcout << L"����Ʈ�� ���� ���Ͽ� ����Ǿ����ϴ�." << endl;
}

// ���� ���Ͽ��� �б�
void TodoList::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        wcout << L"������ �� �� �����ϴ�." << endl;
        return;
    }
    dateToItems.clear(); // ���� ������ �ʱ�ȭ
    while (!file.eof()) { // ������ ������ �б�
        int dateLength;
        file.read(reinterpret_cast<char*>(&dateLength), sizeof(int)); // ��¥�� ���� �б�
        if (dateLength <= 0)
            break; // ��¥ ���̰� 0 �����̸� ���� ������ �����Ͽ� ����
        // ��¥ �б�
        wchar_t* dateBuffer = new (std::nothrow) wchar_t[dateLength + 1]; // ���� �Ҵ� �� ���� ó��
        if (!dateBuffer) {
            wcerr << L"�޸� �Ҵ� ����: ��¥" << endl;
            break;
        }
        file.read(reinterpret_cast<char*>(dateBuffer), sizeof(wchar_t) * dateLength);
        dateBuffer[dateLength] = L'\0'; // ���ڿ� ���� NULL ���� �߰�
        wstring date(dateBuffer);
        delete[] dateBuffer;
        int itemCount;
        file.read(reinterpret_cast<char*>(&itemCount), sizeof(int)); // ������ ���� �б�
        if (itemCount <= 0) {
            wcerr << L"�߸��� ������ �����Դϴ�." << endl;
            break;
        }
        vector<TodoItem> items;
        for (int i = 0; i < itemCount; i++) {
            TodoItem newItem;
            newItem.readBinary(file);
            items.push_back(newItem);
        }
        dateToItems[date] = items;
        char marker;
        file.read(&marker, sizeof(char));
        if (marker == 'X')
            break;
    }
    file.close();
    wcout << L"���� ���Ͽ��� ����Ʈ�� �о�鿴���ϴ�." << endl;
}