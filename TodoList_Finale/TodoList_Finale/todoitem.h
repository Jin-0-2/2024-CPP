#pragma once
class TodoItem {
private:
    wchar_t task[256];
    bool completed;

public:
    wstring get_task() const;
    bool get_completed() const;
    void set_task(const wstring& _task);
    void set_completed(bool a);

    // 이진 파일 입출력 함수 추가
    void writeBinary(ofstream& file) const;
    void readBinary(ifstream& file);
};