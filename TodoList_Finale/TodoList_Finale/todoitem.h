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

    // ���� ���� ����� �Լ� �߰�
    void writeBinary(ofstream& file) const;
    void readBinary(ifstream& file);
};