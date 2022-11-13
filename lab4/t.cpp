#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>
using namespace std;

struct word
{
    char str[100];
    int cnt;
};

word words[100];
int word_cnt; // 단어 총 개수

word *sorted;

bool typeCheck(const char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
        return true;
    }
    return false;
}

void merge(word *list, int left, int mid, int right)
{
    int i, j, k;
    i = left;
    j = mid + 1;
    k = left;
    while (i <= mid && j <= right)
    {
        if (list[i].cnt > list[j].cnt) // 빈도수로 정렬
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)
        for (int n = j; n <= right; n++)
            sorted[k++] = list[n];
    else
        for (int n = i; n <= mid; n++)
            sorted[k++] = list[n];

    for (int n = left; n <= right; n++)
        list[n] = sorted[n];
}
void merge_sort(word *list, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);

        merge(list, left, mid, right);
    }
}

void merge2(word *list, int left, int mid, int right)
{
    int i, j, k;
    i = left;
    j = mid + 1;
    k = left;
    while (i <= mid && j <= right)
    {
        if (strcmp(list[i].str, list[j].str) < 0) // ASCII코드 기준으로 정렬
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)
        for (int n = j; n <= right; n++)
            sorted[k++] = list[n];
    else
        for (int n = i; n <= mid; n++)
            sorted[k++] = list[n];

    for (int n = left; n <= right; n++)
        list[n] = sorted[n];
}
void merge_sort2(word *list, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        merge_sort2(list, left, mid);
        merge_sort2(list, mid + 1, right);

        merge2(list, left, mid, right);
    }
}

int findWords(const char *s)
{
    for (int i = 0; i < word_cnt; i++)
    {
        if (!strcmp(s, words[i].str)) // 같은 문자열인경우
        {
            return i;
        }
    }
    return -1;
}

void countWords(const char *s)
{
    int idx = findWords(s);

    if (idx == -1)
    {
        strcpy(words[word_cnt].str, s);
        words[word_cnt].cnt = 1;
        word_cnt++;
    }
    else
    {
        words[idx].cnt++;
    }
}

void showWords()
{
    for (int i = 0; i < word_cnt; i++)
    {
        cout << words[i].str << " : " << words[i].cnt << endl;
    }
}

void make_words(string s)
{
    int j = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (!typeCheck(s[i]))
        {
            countWords(s.substr(j, i).c_str());
            j = i + 1;
        }
    }
    if (!j)
        countWords(s.c_str());
    else if (s.size() - j)
    {
        countWords(s.substr(j, s.size()).c_str());
    }
}

int main()
{
    ifstream file;
    sorted = new word[100];

    file.open("datafile.txt"); // 파일 열기
    if (file.is_open())
    {
        while (!file.eof()) // 파일 끝까지
        {
            string s;
            file >> s;
            const char *str;
            str = s.c_str();
            for (int i = 0; i < strlen(str); i++)
            {
                if (typeCheck(str[i]))
                    cout << str[i] << endl;
            }
        }
        file.close(); // 파일 닫기
    }

    showWords();
    return 0;
}