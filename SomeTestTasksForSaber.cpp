#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <sstream>

void IntToBinary(size_t number, std::ostream &out = std::cout) {
  if (number == 0) {
    out << 0;
    return;
  }
  std::vector<int> binary_form;
  while (number != 0) {
    if (number % 2) {
      binary_form.push_back(1);
    } else {
      binary_form.push_back(0);
    }
    number /= 2;
  }
  for (int i = int(binary_form.size()) - 1; i >= 0; --i) {
    out << binary_form[i];
  }
}

void RemoveDups(char *str) {
  if (str[0] == '\0' || str[1] == '\0') {
    return;
  }
  int i = 0, j = 1;
  for (; str[j] != '\0';) {
    if (str[i] != str[j]) {
      ++i;
      str[i] = str[j];
    }
    ++j;
  }
  ++i;
  str[i] = '\0';
}

// структуру ListNode модифицировать нельзя
struct ListNode {
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
  std::string data; // произвольные пользовательские данные
};

class List {
public:

  List(std::initializer_list<std::string> strings) {
    if (empty(strings)) {
      return;
    }
    head = new ListNode();
    tail = head;
    head->data = *strings.begin();
    for (int i = 1; i < strings.size(); ++i) {
      auto *node = new ListNode();
      node->data = *(strings.begin() + i);

      tail->next = node;
      node->prev = tail;

      tail = node;
    }
    count = strings.size();
  }

  void Serialize(FILE *file) { // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
    if (std::fwrite((const char *) &count, sizeof(count), 1, file) != 1) {
      std::cerr << "count write failed!\n";
    }
    if (count < 1) {
      return;
    }

    ListNode *node = head;
    while (node) {
      WriteStr(node->data, file);

      node = node->next;
    }
  }

  static void WriteStr(std::string &str, FILE *file) {
    size_t str_size = str.size();
    if (std::fwrite((const char *) &str_size, sizeof(str_size), 1, file) != 1) {
      std::cerr << "str_size write failed!\n";
    }

    for (int i = 0; i < str_size; ++i) {
      if (std::fwrite(&str[i], sizeof(char), 1, file) != 1) {
        std::cerr << "string character write failed!\n";
      }
    }
  }

  static void ReadStr(std::string &str, FILE *file) {
    size_t str_size;
    if (std::fread((char *) &str_size, sizeof(str_size), 1, file) != 1) {
      std::cerr << "str_size read failed!\n";
    }
    str.resize(str_size);
    for (int j = 0; j < str_size; ++j) {
      if (std::fread(&str[j], sizeof(char), 1, file) != 1) {
        std::cerr << "string character read failed!\n";
      }
    }
  }

  void Deserialize(FILE *file) { // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
    DeleteExtraNodes(head);

    if (std::fread((char *) &count, sizeof(count), 1, file) != 1) {
      std::cerr << "count read failed!\n";
    }
    if (count < 1) {
      return;
    }

    head = new ListNode();
    tail = head;
    ReadStr(head->data, file);
    for (int i = 1; i < count; ++i) {
      auto *node = new ListNode();
      ReadStr(node->data, file);

      tail->next = node;
      node->prev = tail;

      tail = node;
    }
  }

  static void DeleteExtraNodes(ListNode *node) {
    while (node) {
      ListNode *tmp_node = node;
      node = node->next;
      delete tmp_node;
    }
  }

  std::string ToString() {
    std::string str;
    ListNode *node = head;
    while (node) {
      str += node->data;
      node = node->next;
    }
    return str;
  }

  ~List() {
    DeleteExtraNodes(head);
  }

  // ... ваши методы для заполнения списка
private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  size_t count = 0;
};

void TestIntToBinary(int i, const std::string &answer) {
  std::stringstream ss;
  IntToBinary(i, ss);
  std::cout << "Test IntToBinary with " << i;
  if (ss.str() == answer) {
    std::cout << " OK" << std::endl;
  } else {
    std::cout << " Failed. " << ss.str() << "!=" << answer << std::endl;
  }
}

void TestRemoveDups(std::string input_str, const std::string &answer) {
  RemoveDups(input_str.data());

  input_str.resize(answer.size());
  std::cout << "Test RemoveDups with " << input_str;
  if (input_str == answer) {
    std::cout << " OK" << std::endl;
  } else {
    std::cout << " Failed. " << input_str << "!=" << answer << std::endl;
  }
}

void TestSerialization(List list, const std::string &answer) {
  FILE *f = fopen("bbb", "wb");
  list.Serialize(f);
  fclose(f);

  List l2{"1", "1", "1", "1", "1"};
  f = fopen("bbb", "rb");
  l2.Deserialize(f);
  fclose(f);

  ;
  std::cout << "Test Serialization with " << answer;
  if (l2.ToString() == answer) {
    std::cout << " OK" << std::endl;
  } else {
    std::cout << " Failed. " << l2.ToString() << "!=" << answer << std::endl;
  }
}

int main() {
  TestIntToBinary(0, "0");
  TestIntToBinary(1, "1");
  TestIntToBinary(6, "110");
  TestIntToBinary(11, "1011");
  TestIntToBinary(15, "1111");
  TestIntToBinary(241, "11110001");
  TestIntToBinary(1000, "1111101000");
  std::cout << "----------------------------------" << std::endl;
  TestRemoveDups("", "");
  TestRemoveDups("AAA   BBB   CCC", "A B C");
  TestRemoveDups("AaaAaaa", "AaA");
  TestRemoveDups("  A B     C", " A B C");
  TestRemoveDups("A", "A");
  TestRemoveDups(" ", " ");
  TestRemoveDups("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", "C");
  TestRemoveDups("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC+", "C+");
  TestRemoveDups("+CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC+", "+C+");
  TestRemoveDups("abcdegg", "abcdeg");
  std::cout << "----------------------------------" << std::endl;
  TestSerialization({"4444", "22", "333"}, "444422333");
  TestSerialization({"1"}, "1");
  TestSerialization({"1", "1", "1", "1", "1", "1", "1"}, "1111111");
  TestSerialization({"1", "1", "1", "1", "1"}, "11111");
  TestSerialization({"10000000000000000000000000000000", "1", "1", "1", "1"}, "100000000000000000000000000000001111");

  return 0;
}
