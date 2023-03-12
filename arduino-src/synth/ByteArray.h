#ifndef ByteArray_h
#define ByteArray_h

class ByteArray {
  private:
    byte* arr;
    int size;

  public:
    ByteArray() {
      arr = NULL;
      size = 0;
    }

    ~ByteArray() {
      delete[] arr;
    }

    void push(byte b) {
      byte* new_arr = new byte[size + 1];

      for (int i = 0; i < size; i++) {
        new_arr[i] = arr[i];
      }

      new_arr[size] = b;
      delete[] arr;
      arr = new_arr;
      size++;
    }

    byte get(int index) {
      return arr[index];
    }

    byte getLast() {
      if (size > 0) {
        return arr[size - 1];
      } else {
        return 0;
      }
    }

    int length() {
      return size;
    }

    bool exists(byte b) {
      for (int i = 0; i < size; i++) {
        if (arr[i] == b) {
          return true;
        }
      }
      return false;
    }

    int find(byte b) {
      for (int i = 0; i < size; i++) {
        if (arr[i] == b) {
          return i;
        }
      }
      return -1;
    }

    void remove(byte b) {
      int index = find(b);

      if (index != -1) {
        byte* new_arr = new byte[size - 1];

        for (int i = 0; i < index; i++) {
          new_arr[i] = arr[i];
        }

        for (int i = index + 1; i < size; i++) {
          new_arr[i - 1] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        size--;
      }
    }
};

#endif;