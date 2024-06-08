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
    wcsncpy_s(task, _task.c_str(), sizeof(task) / sizeof(task[0]) - 1); // ���ڿ� ����
    task[sizeof(task) / sizeof(task[0]) - 1] = L'\0'; // ���ڿ� ���� NULL ���� �߰�
}

void TodoItem::set_completed(bool a)
{
    completed = a;
}

void TodoItem::writeBinary(ofstream& file) const
{
    file.write(reinterpret_cast<const char*>(task), sizeof(task)); // ���ڿ� ����  // wchar_t�� char*�� ��ȯ
    file.write(reinterpret_cast<const char*>(&completed), sizeof(completed)); // bool ����
}

void TodoItem::readBinary(ifstream& file)
{
    file.read(reinterpret_cast<char*>(task), sizeof(task)); // ���ڿ� �б�
    file.read(reinterpret_cast<char*>(&completed), sizeof(completed)); // bool �б�
}