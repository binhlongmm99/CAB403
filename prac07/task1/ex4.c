/* C program to illustrate function prototype.
* REF:  https://www.geeksforgeeks.org/difference-int-main-int-mainvoid/
*/
void fun() {  }
void fun(void) { }

int main(void)
{
    fun(10, "Haha", "Halo");

    return (0);
}
