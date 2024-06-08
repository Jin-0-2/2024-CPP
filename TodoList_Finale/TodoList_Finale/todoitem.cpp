#include "todo.h"


wstring TodoItem::get_task() const
{
    return wstring(task);
}

bool TodoItem::get_completed() const
{
    return completed;
}

void TodoItem::set_task(const wstring& _task)
{
    wcsncpy_s(task, _task.c_str(), sizeof(task) / sizeof(task[0]) - 1); // 문자열 복사
    task[sizeof(task) / sizeof(task[0]) - 1] = L'\0'; // 문자열 끝에 NULL 문자 추가
}

void TodoItem::set_completed(bool a)
{
    completed = a;
}

void TodoItem::writeBinary(ofstream& file) const
{
    file.write(reinterpret_cast<const char*>(task), sizeof(task)); // 문자열 쓰기  // wchar_t를 char*로 변환
    file.write(reinterpret_cast<const char*>(&completed), sizeof(completed)); // bool 쓰기
}

void TodoItem::readBinary(ifstream& file)
{
    file.read(reinterpret_cast<char*>(task), sizeof(task)); // 문자열 읽기
    file.read(reinterpret_cast<char*>(&completed), sizeof(completed)); // bool 읽기
}