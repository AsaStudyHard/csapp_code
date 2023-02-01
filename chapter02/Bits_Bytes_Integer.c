#include <stdio.h>
#include <stdlib.h>

void getBinaryByDecimal(int x)
{
    // get binary by a decimal number
    unsigned site = 0x80000000;
    unsigned offset = 0;
    while(offset < 32)
    {
        // & operator， get a bit of x
        printf("%d", x & (site >> offset) && 1);
        offset++;
    }
    printf("\n");

}

unsigned leastBitPos(unsigned x)
{
    // get least 1 
    /*
    For example:
        x = 6  =>  0110
        x       0000 0110   => (1)
        ~x      1111 1001
        ~x+1    1111 1010   => (2)
        (1)&(2) 0000 0010
        
        Thinking: 取反 所有的bit与原值相反，则&操作全为0，之后 + 1获取到了最近一位的1
                  例如最后一位是1，则取反最后一位0，+ 1 后为1，如果最后一位不是1，则取反后后几位全为1，然后 + 1进行了进位
    */
    return x & ((~x) + 1); 
}

// uint64_t hexAllLetters(uint64_t x) {
//     // 判断这个数字是不是全为字母
//     uint64_t x1 = (x & 0x2222222222222222) >> 1;
//     uint64_t x2 = (x & 0x4444444444444444) >> 2;
//     uint64_t x3 = (x & 0x8888888888888888) >> 3;

//     x = x3 & (x1 | x2);  // 布尔代数得到的结论
//     x = x & (x >> 32);  // 判断
//     x = x & (x >> 16);
//     x = x & (x >>  8);
//     x = x & (x >>  4);
//     return x;
// }

unsigned isHexAllLetters(unsigned x)
{
    // 判断一个数的十六进制是不是全为字母, unsigned 是32bit, 但是我们需要对齐位置。
    /*
    我们直接进行&操作获取的x1, x2, x3是这样的
    x1：0010
    x2：0100
    x3：1000
    很明显，这样并不能进行位运算，我们需要将他们对齐位置
    x1：0010  >>1    x1：0001
    x2：0100  >>2    x2：0001
    x3：1000  >>3    x3：0001
    
    */
    unsigned x1 = (x & 0x22222222) >> 1;
    unsigned x2 = (x & 0x44444444) >> 2;
    unsigned x3 = (x & 0x88888888) >> 3;

    // 获取数据的十六进制的字母分布状况
    unsigned res = x3 & (x1 | x2);
    printf("hex letter res: %#x\n", res);

    // 如果想要直接获取一个答案，可以进行一次移位操作
    res = res & (res >> 16);  // 这是一种归约的调用，移动16位，我们比较判断是32位，只要这32位有不为1的，就留下了0，有着详细的数学证明，但是我不会。。。
    res = res & (res >> 8);
    res = res & (res >> 4);
    return res;

}



int main()
{
    // int x = -2147483648;
    // getBinaryByDecimal(x);

    // printf("获取最低位的1：");
    // getBinaryByDecimal(leastBitPos(x));
    printf("%#x is hex all letter: %u\n", 0xa0a0a0a0, isHexAllLetters(0xa0a0a0a0));
    printf("%#x is hex all letter: %u\n", 0xaaaaaaaa, isHexAllLetters(0xaaaaaaaa));
    printf("%#x is hex all letter: %u\n", 0x11111111, isHexAllLetters(0x11111111));
    printf("%#x is hex all letter: %u\n", 0xabaaaaa1, isHexAllLetters(0xabaaaaa1));
    printf("%#x is hex all letter: %u\n", 0x1baaaaaa, isHexAllLetters(0x1baaaaaa));

    return 0;
}
