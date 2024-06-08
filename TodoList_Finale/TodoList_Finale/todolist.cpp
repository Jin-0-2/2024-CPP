#include "todo.h"

void TodoList::addItem(const wstring& task, const wstring& date) {
    TodoItem newItem;
    newItem.set_task(task);
    newItem.set_completed(false);
    dateToItems[date].push_back(newItem);
    wcout << L"할 일이 추가되었습니다." << endl;
}

void TodoList::updateItem(const wstring& date, int index, const wstring& task) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date][index].set_task(task);
        wcout << L"할 일이 수정되었습니다." << endl;
    }
    else {
        wcout << L"잘못된 날짜 또는 인덱스입니다." << endl;
    }
}

// 할 일 삭제
void TodoList::deleteItem(const wstring& date, int index) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date].erase(dateToItems[date].begin() + index);
        wcout << L"할 일이 삭제되었습니다." << endl;

        if (dateToItems[date].empty()) {
            dateToItems.erase(date);
        }
    }
    else {
        wcout << L"잘못된 날짜 또는 인덱스입니다." << endl;
    }
}

// 할 일 완료로 표시
void TodoList::markAsCompleted(const wstring& date, int index) {
    if (dateToItems.find(date) != dateToItems.end() && index >= 0 && index < dateToItems[date].size()) {
        dateToItems[date][index].set_completed(true);
        wcout << L"할 일이 완료로 표시되었습니다." << endl;
    }
    else {
        wcout << L"잘못된 날짜 또는 인덱스입니다." << endl;
    }
}

// 특정 날짜의 To-Do 리스트 출력
void TodoList::displayListByDate(const wstring& date) {
    wcout << date << L"의 To-Do 리스트:" << endl;
    if (dateToItems.find(date) != dateToItems.end()) {
        for (size_t i = 0; i < dateToItems[date].size(); ++i) {
            wcout << i + 1 << L". ";
            if (dateToItems[date][i].get_completed()) {
                wcout << L"[완료] ";
            }
            wcout << dateToItems[date][i].get_task() << endl;
        }
    }
    else {
        wcout << L"해당 날짜의 할 일이 없습니다." << endl;
    }
}

// 전체 To-Do 리스트 출력
void TodoList::displayAllList() {
    if (dateToItems.empty()) {
        wcout << L"리스트가 비었습니다." << endl;
        return;
    }

    wcout << L"전체 To-Do 리스트:" << endl;
    for (auto& pair : dateToItems) {
        wcout << pair.first << L":" << endl;
        for (size_t i = 0; i < pair.second.size(); ++i) {
            wcout << i + 1 << L". ";
            if (pair.second[i].get_completed()) {
                wcout << L"[완료] ";
            }
            wcout << pair.second[i].get_task() << endl;
        }
        wcout << endl;
    }
}

// 이진 파일로 저장
void TodoList::saveToBinaryFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        wcout << L"파일을 열 수 없습니다." << endl;
        return;
    }

    for (const auto& pair : dateToItems) {
        // 날짜 쓰기
        wstring date = pair.first;
        int dateLength = date.size();
        file.write(reinterpret_cast<const char*>(&dateLength), sizeof(int));
        file.write(reinterpret_cast<const char*>(date.c_str()), dateLength * sizeof(wchar_t));

        // 아이템 개수 쓰기
        int itemCount = pair.second.size();
        file.write(reinterpret_cast<const char*>(&itemCount), sizeof(int));

        for (const auto& item : pair.second) {
            // 할 일 쓰기
            item.writeBinary(file);
        }
    }
    char endMarker = 'X';
    file.write(&endMarker, sizeof(char));

    file.close();
    wcout << L"리스트가 이진 파일에 저장되었습니다." << endl;
}

// 이진 파일에서 읽기
void TodoList::loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        wcout << L"파일을 열 수 없습니다." << endl;
        return;
    }
    dateToItems.clear(); // 기존 데이터 초기화
    while (!file.eof()) { // 파일의 끝까지 읽기
        int dateLength;
        file.read(reinterpret_cast<char*>(&dateLength), sizeof(int)); // 날짜의 길이 읽기
        if (dateLength <= 0)
            break; // 날짜 길이가 0 이하이면 파일 끝으로 간주하여 종료
        // 날짜 읽기
        wchar_t* dateBuffer = new (std::nothrow) wchar_t[dateLength + 1]; // 동적 할당 시 예외 처리
        if (!dateBuffer) {
            wcerr << L"메모리 할당 오류: 날짜" << endl;
            break;
        }
        file.read(reinterpret_cast<char*>(dateBuffer), sizeof(wchar_t) * dateLength);
        dateBuffer[dateLength] = L'\0'; // 문자열 끝에 NULL 문자 추가
        wstring date(dateBuffer);
        delete[] dateBuffer;
        int itemCount;
        file.read(reinterpret_cast<char*>(&itemCount), sizeof(int)); // 아이템 개수 읽기
        if (itemCount <= 0) {
            wcerr << L"잘못된 아이템 개수입니다." << endl;
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
    wcout << L"이진 파일에서 리스트를 읽어들였습니다." << endl;
}