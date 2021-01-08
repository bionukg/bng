#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

double* matrix_transposition(double* m);//矩阵转置
double* create_matrix(int line, int row);//新建矩阵
double delete_matrix(double* m);//删除矩阵
void printf_matrix(double* m, int type);//显示矩阵
double* scanf_matrix();//手动输入矩阵
double* add_or_minus_or_multi_matrix(double* a, double* b, double t);//矩阵加减乘法
double average_of_matrix(double* mat);//矩阵元素均值
double* matele(double* m, int l, int r);//矩阵matrix第line行第row列的元素
double* submatrix(double* m,int l0,int l1,int r0,int r1);
double matmax(double* m);
double* normalize_matrix(double* m);
void rand_matrix(double* m);

//矩阵结构
//struct matrix
//{
//    int *matp;
//    int line;//行数
//    int row;//列数
//};

double* matrix_transposition(double* m)
{
    double* n;
    n=create_matrix(*(m + 1), *m);
    int l, r;
    for (l = 0; l < *m; l++)
    {
        for (r = 0; r < *(m+1); r++)
        {
            *(n + (int)(*n) * (r) +  l + 2) = *(m + (int)(*m) * l + r + 2);
        }
    }
    return n;
}
double* create_matrix(int line,int row)
{
    double* m;
    m = (double*)malloc((line*row+2)* sizeof(double));
    if (m == 0) {
        printf("内存不足");
        return 0;
    }
    *m = line;
    *(m + 1) = row;
    return m;
}
double delete_matrix(double* m)
{
    free(m);
    return 0;
}
void printf_matrix(double* m, int type)
{
    if (m == 0)
    {
        printf("\n空指针\n");
        return;
    }
    //type=1矩阵，
//  ┌2 3 4┐
//  │5 6 7│
//  └8 9 1┘
    //type=2 tab对齐模式(最高7位)
    int r = 1, l = 1, i = 0;
    //普通模式
    if (type == 1)
    {
        if (*m == 1)
        {
            printf("[");
            for (; r < *(m+1); r++)
            {
                printf("%.3f ", *(m+2+i));
                i++;
            }
            printf("%.3f]\n", *(m+2+i));
        }
        else
        {
            //第一行
            printf("┌ ");
            for (r = 1; r < *(m+1); r++)
            {
                printf("%.3f ", *(m+2+i));
                i++;
            }
            printf("%.3f┐\n", *(m+2+i));
            i++;
            l++;
            //中间行
            for (l = 1; l < *m-1; l++)
            {
                printf("│ ");
                for (r = 1; r < *(m+1); r++)
                {
                    printf("%.3f ", *(m+2+i));
                    i++;
                }
                printf("%.3f│\n", *(m+2+i));
                i++;
            }
            //最后一行
            printf("└ ");
            for (r = 1; r < *(m+1); r++)
            {
                printf("%.3f ", *(m+2+i));
                i++;
            }
            printf("%.3f┘\n", *(m+2+i));
            i++;
        }
        return;
    }
    //tab对齐模式(最高7位)
    if (type == 2) 
    {
        if (*m == 1)
        {
            printf("[%c",9);
            for (; r < *(m + 1); r++)
            {
                printf("%.3f%c", *(m + 2 + i),9);
                i++;
            }
            printf("%.3f%c]\n", *(m + 2 + i),9);
        }
        else
        {
            //第一行
            printf("┌%c",9);
            for (r = 1; r < *(m + 1); r++)
            {
                printf("%.3f%c", *(m + 2 + i),9);
                i++;
            }
            printf("%.3f%c┐\n", *(m + 2 + i),9);
            i++;
            l++;
            //中间行
            for (l = 1; l < *m - 1; l++)
            {
                printf("│%c",9);
                for (r = 1; r < *(m + 1); r++)
                {
                    printf("%.3f%c", *(m + 2 + i),9);
                    i++;
                }
                printf("%.3f%c│\n", *(m + 2 + i),9);
                i++;
            }
            //最后一行
            printf("└%c",9);
            for (r = 1; r < *(m + 1); r++)
            {
                printf("%.3f%c", *(m + 2 + i),9);
                i++;
            }
            printf("%.3f%c┘\n", *(m + 2 + i),9);
            i++;
        }
        return;
    }
}
double* scanf_matrix()
{
    int line, row,tem;double *m;
    printf("输入行数：");
    if (0 == scanf("%d", &line))
        printf("error");
    printf("输入列数：");
    if (0 == scanf("%d", &row))
        printf("error");
    int ele = line * row;
    m=create_matrix(line, row);
    printf("输入数组元素：\n");
    for (int i = 0; i < ele; i++)
    {
        if (0 == scanf("%d", &tem))
            printf("error");
        *(m + i + 2) = (double)tem;
    }
    printf("输入完毕\n");
    return m;
}
double* add_or_minus_or_multi_matrix(double* a, double* b, double t)//a+b/a-b/a*b
{
    double* result, * res1, * a1, * b1;int line, row;
    if (a != 0 && b != 0)//a、b均有效时为矩阵二元运算
    {
        result = create_matrix(*a, *(b + 1));
        *result = *a; line = *a;
        *(result + 1) = *(b + 1); row = *(b + 1);
        int max = (int)*a * (int)*(b + 1),  i = 0;
        res1 = result + 2;
        a1 = a + 2;
        b1 = b + 2;
        if ((int)t == -1 || (int)t == 1)//-1为减，1为加
        {
            if (*a == *b && *(a + 1) == *(b + 1))//判定行、列相等
            {               
                if ((int)t == 1)
                {
                    for (i = 0; i < max; i++)
                    {
                        *(res1 + i) = *(a1 + i) + *(b1 + i);
                    }
                }
                else if ((int)t == -1)
                {
                    for (i = 0; i < max; i++)
                    {
                        *(res1 + i) = *(a1 + i) - *(b1 + i);
                    }

                }
                else
                {
                    printf("type error,b!=NUUL");
                    return 0;
                }
            }
            else
            {
                printf("矩阵不匹配，请确保两个矩阵行数和列数分别相等");
                return 0;
            }
        }
        else if ((int)t == 0)//0为矩阵乘法
        {
            if (*(a + 1) == *b)//判定a的列等于b的行
            {
                int p = (int)*b;
                int j = 0, k = 0;
                for (i = 1; i <= line; i++)
                {
                    for (j = 1; j <= row; j++)
                    {
                        *matele(result,i,j) = 0;
                        for (k = 1; k <= p; k++)
                        {
                            *matele(result, i, j) += *matele(a,i,k) * *matele(b, k, j);
                        }
                    }
                }
            }
            else
            {
                printf("矩阵不匹配，请确保前一矩阵的列数等于后一矩阵的行数\n");
                return 0;
            }
        }       
        else
        {
            printf("type error;b!=0\n");
        }
    }
    else if (a != 0 && b == 0)//仅a有效时为一元运算[数乘]
    {

        result = create_matrix(*a, *(a + 1));
        res1 = result + 2; a1 = a + 2;
        int max = (int)*a * (int)*(a + 1), i = 0;
        for (i = 0; i < max; i++)
        {
            *(res1 + i) = *(a1 + i)*t;
        }
    }
    else
    {
        printf("NULL pointer a");
        return 0;
    }
    return result;
}
double average_of_matrix(double* mat)
{
    int total = (int)*mat * (int)*(mat + 1);
    double avg= 0; double* mat1 = mat + 2;
    for (int i = 0; i < total; i++)
    {
        avg += (double)(*(mat1 + i))/(double)total;
    }
    return avg;
}
double* matele(double* m, int l, int r)
{
    return (m + 1 + r + (l - 1) * (int)*(m + 1));
}
double matmax(double* m) 
{
    int total = (int)*m * (int)*(m + 1);double *m1 = m + 2;
    int max = (int)*m1;
    for (int i = 0; i < total; i++)
    {
        if (*(m1 + i) > max)
        {
            max = *(m1 + i);
        }
    }
    return max;
}
double* submatrix(double* m, int l0, int l1, int r0, int r1)//l行r列，求子矩阵
{
    int l = (int)*m - l1 + l0 - 1, r = (int)*(m + 1) - r1 + r0 - 1;
    double* sub = create_matrix(l, r);
    double* sub1 = sub + 2;
    int max = l * r,ele;
    int i = 1, j = 1;
    for (int odr = 0; odr < max; odr++)
    {
        //for (i = 1; i <= *m; i++)
        //{
        //    if (i == l0)
        //    {
        //        i += *m - l-1;
        //        continue;
        //    }
        //    for (j = 1; j <= *(m + 1); j++)
        //    {
        //        if (j == r0)
        //        {
        //            j += *(m + 1) - r - 1;
        //            continue;
        //        }
        while ((j >= r0 && j <= r1) || (i >= l0 && i <= l1))
        {
            if (j == *(m + 1))
            {
                j = 1;
                i++;
            }
            else
            {
                j++;
            }
            if (i > *m)
            {
                break;
            }
        }
        *(sub1 + odr) = *matele(m, i, j);
        if (j == *(m + 1))
        {
            j = 1;
            i++;
        }
        else
        {
            j++;
        }
        if (i > *m)
        {
            break;
        }

        //    }
        //}
    }
    return sub;
}
double* normalize_matrix(double* m)
{
    double* norm = add_or_minus_or_multi_matrix(m, 0, (1 / matmax(m)));
    return norm;
}
void rand_matrix(double* m)
{
    int  total = (int)*m * (int)*(m + 1);double *m1 = m + 2;
    for (int i = 0; i < total; i++)
    {
        *(m1 + i) = rand() % 100;
    }
    return;
}
int main(void)
{
    srand((unsigned int)time(0));
    printf("矩阵计算器v1.0by傅俊铭\n");
    int text[10] = { 0 };
    int i = 0, j = 0;double *m[10];
    int option, swc = 1;
    while (swc == 1)
    {

        printf("矩阵函数测试，请选择功能，输入对应的数字：\n");
        printf(" * **************************************************\n");
        printf(" 1：输入一个矩阵，求矩阵均值；\n");
        printf(" 2：产生一个随机数矩阵，求矩阵均值；\n");
        printf(" 3：输入两个矩阵，求矩阵和；\n");
        printf(" 4：输入两个矩阵，求矩阵差；\n");
        printf(" 5：输入两个矩阵，求矩阵积；\n");
        printf(" 6：产生两个随机数矩阵，求矩阵和；\n");
        printf(" 7：产生两个随机数矩阵，求矩阵差；\n");
        printf(" 8：产生两个随机数矩阵，求矩阵积；\n");
        printf(" 9：求矩阵的子阵，如矩阵的2 - 4行，1 - 3列的子阵；\n");
        printf(" 10：输入一个矩阵，求矩阵元素的最大值；\n");
        printf(" 11：产生一个随机数矩阵，求矩阵元素的最大值；\n");
        printf(" 12：输入一个矩阵，求矩阵转置；\n");
        printf(" 13：产生一个随机数矩阵，求矩阵转置；\n");
        printf(" 14：输入一个矩阵，求矩阵归一化；\n");
        printf(" 15：产生一个随机数矩阵，求矩阵归一化；\n");
        printf(" 0：结束！\n");
        scanf("%d", &option);               

        system("cls");
        int l;            
        int r;
        int l1;
        int r1;
        int l2;
        int r2;


        switch (option)
        {
        case 1: 
            m[1] = scanf_matrix();
            system("cls");
            printf_matrix(m[1], 2);
            printf("\n均值=%f\n", average_of_matrix(m[1]));
            delete_matrix(m[1]);
            break;
        case 2:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[2]=create_matrix(l, r);
            rand_matrix(m[2]);
            printf_matrix(m[2], 2);
            printf("\n均值=:%f\n", average_of_matrix(m[2]));
            delete_matrix(m[2]);
            break;
        case 3:
            printf("请输入第一个矩阵\n");
            m[1] = scanf_matrix();
            printf("请输入第二个矩阵\n");
            m[2] = scanf_matrix();
            m[3]=add_or_minus_or_multi_matrix(m[1], m[2], 1);
            printf("矩阵和=\n\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);
            break;
        case 4:
            printf("请输入第一个矩阵\n");
            m[1] = scanf_matrix();
            printf("请输入第二个矩阵\n");
            m[2] = scanf_matrix();
            m[3] = add_or_minus_or_multi_matrix(m[1], m[2], -1);
            printf("矩阵差=\n\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);
            break;
        case 5:
            printf("请输入第一个矩阵\n");
            m[1] = scanf_matrix();
            printf("请输入第二个矩阵\n");
            m[2] = scanf_matrix();
            m[3] = add_or_minus_or_multi_matrix(m[1], m[2], 0);
            printf("矩阵积=\n\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);           
            break;
        case 6:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n矩阵A=\n");
            printf_matrix(m[1], 2);
            m[2] = create_matrix(l, r);
            rand_matrix(m[2]);
            printf("\n矩阵B=\n");
            printf_matrix(m[2], 2);
            m[3] = add_or_minus_or_multi_matrix(m[1], m[2], 1);
            printf("\nA+B=\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);
            break;
        case 7:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n矩阵A=\n");
            printf_matrix(m[1], 2);
            m[2] = create_matrix(l, r);
            rand_matrix(m[2]);
            printf("\n矩阵B=\n");
            printf_matrix(m[2], 2);
            m[3] = add_or_minus_or_multi_matrix(m[1], m[2], -1);
            printf("\nA-B=\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);
            break;
        case 8:
            printf("输入矩阵A行数：");
            scanf("%d", &l1);
            printf("输入矩阵A列数：");
            scanf("%d", &r1);
            printf("输入矩阵B行数：");
            scanf("%d", &l2);
            printf("输入矩阵B列数：");
            scanf("%d", &r2);
            m[1] = create_matrix(l1, r1);
            rand_matrix(m[1]);
            printf("\n矩阵A=\n");
            printf_matrix(m[1], 2);
            m[2] = create_matrix(l2, r2);
            rand_matrix(m[2]);
            printf("\n矩阵B=\n");
            printf_matrix(m[2], 2);
            m[3] = add_or_minus_or_multi_matrix(m[1], m[2], 0);
            printf("\nAB=\n");
            printf_matrix(m[3], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            delete_matrix(m[3]);
            break;
        case 9:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n矩阵A=\n");
            printf_matrix(m[1], 2);
            printf("输入起始行数：\n");
            scanf("%d", &l1);
            printf("输入终止行数：\n");
            scanf("%d", &l2);
            printf("输入起始列数：\n");
            scanf("%d", &r1);
            printf("输入终止列数：\n");
            scanf("%d", &r2);
            printf("\n矩阵A的子式=\n");
            m[2] = submatrix(m[1], l1, l2, r1, r2);
            printf_matrix(m[2],2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            break;
        case 10:
            m[1] = scanf_matrix();
            printf("\n最大值为%d\n", matmax(m[1]));
            delete_matrix(m[1]);
            break;
        case 11:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n矩阵为\n");
            printf_matrix(m[1], 2);
            printf("\n最大值为%d\n", matmax(m[1]));
            delete_matrix(m[1]);
            break;
        case 12:
            m[1] = scanf_matrix();
            m[2] = matrix_transposition(m[1]);
            printf("转置为：\n");
            printf_matrix(m[2], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            break;
        case 13:
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n原矩阵为\n");
            printf_matrix(m[1], 2);
            m[2] = matrix_transposition(m[1]);
            printf("\n转置为：\n");
            printf_matrix(m[2], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);          
            break;
        case 14:
            m[1] = scanf_matrix();
            m[2] = add_or_minus_or_multi_matrix(m[1], 0, 1 / matmax(m[1]));
            printf("\n归一化为：\n");
            printf_matrix(m[2], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            break;
        case 15:   
            printf("输入行数：");
            scanf("%d", &l);
            printf("输入列数：");
            scanf("%d", &r);
            m[1] = create_matrix(l, r);
            rand_matrix(m[1]);
            printf("\n原矩阵为\n");
            printf_matrix(m[1], 2);
            m[2] = add_or_minus_or_multi_matrix(m[1], 0, 1 / matmax(m[1]));
            printf("\n归一化为：\n");
            printf_matrix(m[2], 2);
            delete_matrix(m[1]);
            delete_matrix(m[2]);
            break;
        case 0:
            swc = 0;
            break;
        default:
            printf("请输入0~15的整数");
            break;
        }
        printf("\n按Enter继续\n");
        char enter;
        do
        {
            scanf("%c", &enter);
        } while (enter != '\n');
        scanf("%c", &enter);

        system("cls");
    }
    //m[0] = scanf_matrix();
    //printf_matrix(m[0], 2);
    /*for (i = 0; i < 5; i++)
        j=scanf("%c", &text[i]);
    text[5] = '┌';
    for (i = 0; i < 10; i++)
        printf("'%c'", text[i]);
    for (i = 0; i < 5; i++)
        j = scanf("%c", &text[i+5]);
        */
    return 0;
}