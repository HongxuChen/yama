int main() {
    int i;
    int j;

    i = 0;//1
    j = 10;//2
    while (i <= j) //3
    {
        while (j >= 5) //4
        {
            if (i == 2)//5
                i = 3;//6 //7 //8
            if (i == 5)//9
                i = 4;//10 //11 //12
            j = -1 + j;//13
        }//14
        i = i + 1;//15
    }//16
}