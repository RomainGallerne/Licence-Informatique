#include <iostream>

int main()
{
    int i,s;
    s=0;
    for (i=1;i<10;i++)
    {
        s+=i;
    }
    std::cout<<"r�sultat : "<<s<<std::endl;

    // deuxi�me programme
    s=0;
    for (i=0;i<10;s+=i)
    {
        i=i+1;
    }
  std::cout<<"r�sultat : "<<s<<std::endl;

  // avec un while
    s=0;i=0;
    while(i<10)
    {
        i=i+1;s+=i;
    }
  std::cout<<"r�sultat : "<<s<<std::endl;

    return 0;
}
