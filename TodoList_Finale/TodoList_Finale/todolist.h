#pragma once
// To-Do 리스트 관리 클래스
class TodoList {
private:
    map<wstring, vector<TodoItem>> dateToItems; // 날짜별 할 일 목록 저장용 맵

public:
    // 새로운 할 일 추가
    void addItem(const wstring& task, const wstring& date);
    // 할 일 수정
    void updateItem(const wstring& date, int index, const wstring& task);
    // 할 일 삭제
    void deleteItem(const wstring& date, int index);
    // 할 일 완료로 표시
    void markAsCompleted(const wstring& date, int index);
    // 특정 날짜의 To-Do 리스트 출력
    void displayListByDate(const wstring& date);
    // 전체 To-Do 리스트 출력
    void displayAllList();
    // 이진 파일로 저장
    void saveToBinaryFile(const string& filename);
    // 이진 파일에서 읽기
    void loadFromBinaryFile(const string& filename);
};