1. 使用memset初始化int数组时，要全初始化为0/-1，则中间数为0/-1;要初始化为一个很大的值中间数选择***<u>0x7f</u>***
2. 对一个string对象循环元素时，可以像这样（x为一个string ）
   ```c_cpp
    for (char c : x)
       {
           ret += static_cast<int>(c);
           ret %= n;
       }
   ```

	3.在C++中，class和struct并太大区别。对于默认的继承访问权，class默认的是private,struct默认的是public。