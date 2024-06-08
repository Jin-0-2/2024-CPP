#pragma once
// To-Do ����Ʈ ���� Ŭ����
class TodoList {
private:
    map<wstring, vector<TodoItem>> dateToItems; // ��¥�� �� �� ��� ����� ��

public:
    // ���ο� �� �� �߰�
    void addItem(const wstring& task, const wstring& date);
    // �� �� ����
    void updateItem(const wstring& date, int index, const wstring& task);
    // �� �� ����
    void deleteItem(const wstring& date, int index);
    // �� �� �Ϸ�� ǥ��
    void markAsCompleted(const wstring& date, int index);
    // Ư�� ��¥�� To-Do ����Ʈ ���
    void displayListByDate(const wstring& date);
    // ��ü To-Do ����Ʈ ���
    void displayAllList();
    // ���� ���Ϸ� ����
    void saveToBinaryFile(const string& filename);
    // ���� ���Ͽ��� �б�
    void loadFromBinaryFile(const string& filename);
};