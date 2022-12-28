#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<cmath>
using namespace std;
const int inputSize = 20;
int smallest = 32;
int largest = -1;

int* binaryToDecimal(int arr[][5])
{
    int static decimalValue[inputSize];

    for (int i = 0; i < inputSize; i++)
        decimalValue[i] = 0;

    int temp = 1;
    int i = 0;
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        for (int loop2 = 4; loop2 >= 0; loop2--)
        {
            if (arr[loop1][loop2] == 1)
            {
                decimalValue[loop1] += temp;
            }
            temp = temp * 2;
        }
        if (decimalValue[loop1] < smallest)
        {
            smallest = decimalValue[loop1];
        }
        if (decimalValue[loop1] > largest)
        {
            largest = decimalValue[loop1];
        }

        temp = 1;
    }
    return decimalValue;
}

int* fitness(int* val)
{
    string fitnessFunction = "2x^2+5x";
    int static fValue[inputSize];
    for (int i = 0; i < inputSize; i++)
        fValue[i] = (2 * (val[i] * val[i])) + (5 * val[i]);
    return fValue;
}


float* expectedCount(float* p)
{
    float static ec[inputSize];
    for (int i = 0; i < inputSize; i++)
        ec[i] = p[i] * inputSize;
    return ec;
}


float* Pi(int* FV, float FS)  //probability of string being selected
{
    float static prob[inputSize] = { 0.00 };
    for (int i = 0; i < inputSize; i++)
        prob[i] = (FV[i] / FS);
    return prob;
}




int main()
{

    srand(time(NULL));

    cout << "//------------------------------------------- SELECTION --------------------------------------------------//" << endl;
    cout << "//--------------------------------------------------------------------------------------------------------//" << endl;
    cout << endl;
    int* ptrDecimal;
    int* ptrFitness;
    float* ptrProb;
    float* ptrExpCount;
    float expSum = 0.00;
    float fitnessSum = 0.00;

    cout << "//------------------------------------ INITIAL POPULATION ----------------------------------------//" << endl;
    int array[inputSize][5];
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            array[loop1][loop2] = rand() % 2;
        }
    }
    cout << "Initial Population" << endl;
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << array[loop1][loop2];
        }
        cout << endl;
    }
    //-----------------------------------------------------------------------------------------------//


    cout << "//------------------------------------------ X VALUE --------------------------------------------//" << endl;
    ptrDecimal = binaryToDecimal(array); //converts binary numbers to decimal
    int max1, max2, store;
    max1 = -1;
    max2 = -1;
    cout << endl;

    cout << "X Value" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrDecimal + i) << endl;
        if (*(ptrDecimal + i) >= max1)
        {
            max2 = max1;
            max1 = *(ptrDecimal + i);
        }
        if (*(ptrDecimal + i) < max1 && *(ptrDecimal + i) > max2)
        {
            max2 = *(ptrDecimal + i);
        }


    }
    store = max1;
    cout << endl;
    cout << "Largest value: " << max1 << endl;
    cout << "Second largest value: " << max2 << endl;

    cout << endl;

    //-----------------------------------------------------------------------------------------------//


    cout << "//------------------------------------------ FITNESS --------------------------------------------//" << endl;

    ptrFitness = fitness(ptrDecimal);

    cout << "Fitness Value" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrFitness + i) << endl;
        fitnessSum += *(ptrFitness + i);
        
    }

    cout << endl;
    cout << "Fitness Sum: " << fitnessSum << endl;
    cout << endl;

    //-----------------------------------------------------------------------------------------------//


    cout << "//---------------------------------------- PROBABILITY ------------------------------------------//" << endl;

    ptrProb = Pi(ptrFitness, fitnessSum);

    cout << "Probability of being selected" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrProb + i) << endl;
    }

    cout << endl;

    //-----------------------------------------------------------------------------------------------//


    cout << "//-------------------------------------- EXPECTED COUNT -----------------------------------------//" << endl;

    ptrExpCount = expectedCount(ptrProb);

    cout << "Expected Count" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrExpCount + i) << endl;
        expSum += *(ptrExpCount + i);
    }

    cout << endl;
    cout << "Expected Sum: " << expSum;
    cout << endl;

    //-----------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    cout << "//---------------------------------------------- CROSSOVER -----------------------------------------------//" << endl;
    cout << "//--------------------------------------------------------------------------------------------------------//" << endl;
    cout << endl;
    int j = 0;

    cout << "//-------------------------------------MATING POOL---------------------------------------------//" << endl;


    int binary[2][5];
    for (int loop1 = 0; loop1 < 1; loop1++)
    {
        for (int loop2 = 4; loop2 >= 0; loop2--)
        {
            if (max1 % 2 == 1)
            {
                binary[loop1][loop2] = 1;
            }
            else
                binary[loop1][loop2] = 0;
            max1 /= 2;
        }
    }

    for (int loop1 = 1; loop1 < 2; loop1++)
    {
        for (int loop2 = 4; loop2 >= 0; loop2--)
        {
            if (max2 % 2 == 1)
            {
                binary[loop1][loop2] = 1;
            }
            else
                binary[loop1][loop2] = 0;
            max2 /= 2;
        }
    }

    for (int loop1 = 0; loop1 < 2; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << binary[loop1][loop2];
        }
        cout << endl;
    }

    int crossoverPoint[inputSize] = { 0 };
    int temp = 0;
    int crossoverArr[inputSize][5];
    int i;
    for (int loop1 = 0 ; loop1 < inputSize ; loop1++)
    {
        i = 0;
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            crossoverArr[loop1][loop2]=binary[i][loop2];
        }
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            if (loop1 == inputSize-1)
                break;
            else
                crossoverArr[loop1 + 1][loop2] = binary[i + 1][loop2];
            
        }
        loop1++;

    }

    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << crossoverArr[loop1][loop2];
        }
        cout << endl;
    }



    //--------------------------------------------------------------------------------------------//

    cout << "//------------------------------------CROSSOVER POINTS----------------------------------------//" << endl;

    for (int i = 0, m = 0, k = 0; i < inputSize; i++, k++)
    {
        crossoverPoint[i] = rand() % 4 + 1;
        cout << "Crossover point " << k + 1 << ": " << crossoverPoint[i] << endl;
        if (crossoverPoint[i] == 1)
        {
            for (int j = 1; j < 5; j++)
            {
                temp = crossoverArr[i][j];
                crossoverArr[i][j] = crossoverArr[i + 1][j];
                crossoverArr[i + 1][j] = temp;
            }

        }
        else if (crossoverPoint[i] == 2)
        {
            for (int j = 2; j < 5; j++)
            {
                temp = crossoverArr[i][j];
                crossoverArr[i][j] = crossoverArr[i + 1][j];
                crossoverArr[i + 1][j] = temp;
            }

        }
        else if (crossoverPoint[i] == 3)
        {
            for (int j = 3; j < 5; j++)
            {
                temp = crossoverArr[i][j];
                crossoverArr[i][j] = crossoverArr[i + 1][j];
                crossoverArr[i + 1][j] = temp;
            }

        }
        else if (crossoverPoint[i] == 4)
        {
            for (int j = 4; j < 5; j++)
            {
                temp = crossoverArr[i][j];
                crossoverArr[i][j] = crossoverArr[i + 1][j];
                crossoverArr[i + 1][j] = temp;
            }

        }
        i++;

    }

    cout << "//---------------------------------OFFSPRING AFTER CROSSOVER----------------------------------//" << endl;

    cout << endl;
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << crossoverArr[loop1][loop2];
        }
        cout << endl;
    }

    //--------------------------------------------------------------------------------------------//

    cout << "//------------------------------------------ X VALUE --------------------------------------------//" << endl;
    int* ptrDecimal1;

    ptrDecimal1 = binaryToDecimal(crossoverArr); //converts binary numbers to decimal

    cout << endl;

    cout << "X Value" << endl;
    int lower[inputSize] = { -1 };
    int count = 0;
    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrDecimal1 + i) << endl;
        if (*(ptrDecimal1 + i) < store)
        {
            lower[count] = i;
            count++;
        }
        else
        {
            lower[count] = -1;
            count++;
        }
    }

    cout << endl;
    


    //-----------------------------------------------------------------------------------------------//

    cout << "//------------------------------------------ FITNESS --------------------------------------------//" << endl;

    int fitnessSum1 = 0;
    ptrFitness = fitness(ptrDecimal1);

    cout << "Fitness Value" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrFitness + i) << endl;
        fitnessSum1 += *(ptrFitness + i);
    }

    cout << endl;
    cout << "Fitness Sum: " << fitnessSum1 << endl;
    cout << endl;

    //-----------------------------------------------------------------------------------------------------------------//
    cout << "//------------------------------------------------- MUTATION-----------------------------------------------//" << endl;
    cout << "//---------------------------------------------------------------------------------------------------------//" << endl;

    /*
    for (int i = 0; i < inputSize; i++)
    {
        cout << lower[i] << endl;
    }
    cout << endl;
    */

    cout << "Before Mutation" << endl;
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << crossoverArr[loop1][loop2];
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < inputSize; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == lower[i])
            {
                if (crossoverArr[i][j] == 0)
                {
                    crossoverArr[i][j] = 1;
                    break;
                }
            }
        }
    }

    cout << endl;
    cout << "After Mutation" << endl;
    for (int loop1 = 0; loop1 < inputSize; loop1++)
    {
        cout << loop1 + 1 << ") ";
        for (int loop2 = 0; loop2 < 5; loop2++)
        {
            cout << crossoverArr[loop1][loop2];
        }
        cout << endl;
    }
    cout << endl;


    //--------------------------------------------------------------------------------------------//

    cout << "//------------------------------------------ X VALUE --------------------------------------------//" << endl;

    int* ptrDecimal2 = binaryToDecimal(crossoverArr); //converts binary numbers to decimal

    cout << endl;

    cout << "X Value" << endl;
    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrDecimal2 + i) << endl;
    }

    cout << endl;

    //-----------------------------------------------------------------------------------------------//

    cout << "//------------------------------------------ FITNESS --------------------------------------------//" << endl;

    int fitnessSum2 = 0;
    ptrFitness = fitness(ptrDecimal2);

    cout << "Fitness Value" << endl;

    for (int i = 0; i < inputSize; i++)
    {
        cout << i + 1 << ") " << *(ptrFitness + i) << endl;
        fitnessSum2 += *(ptrFitness + i);
    }

    cout << endl;
    cout << "Fitness Sum: " << fitnessSum2 << endl;
    cout << endl;

    cout << "//----------------------------------------FITNESS COMPARISON------------------------------------//" << endl;
    cout << endl;
    cout << "Fitness Sum after Selection: " << fitnessSum << endl;
    cout << "Fitness Sum after Selection: " << fitnessSum1 << endl;
    cout << "Fitness Sum after Selection: " << fitnessSum2 << endl;
}
