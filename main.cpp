#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int extraction (int s); // returns the hash location using the extraction method (in this case 3, 5, 7, 8 digits)
int quadProbe (int hashtable[], int s, int max, int quadkey); // function to probe and if collision occurs do quadratic
void writeHash (int hashtable[], string filepath, int max); // function to write out the hash table

int main()
{
    int array_size = 100000;
    int array_of_numbers[array_size]; // creates an array of size 100000 for all the numbers
    string filename;
    cout << "What is the name of the file: ";
    cin >> filename;
    ifstream in;
    in.open(filename);
    while(!in.is_open()) // makes sure the file opens
    {
        cout << "I cannot find the file.\n";
        cout << "What is the name of the file: ";
        cin >> filename;
        in.open(filename);
    }
    int i = 0;
    char linedata[10];
    while (in.peek() != EOF) // writes the file to the array of ints
    {
        in.getline(linedata,10,',');
        array_of_numbers[i] = atoi(linedata);
        i++;
    }
    in.clear(); in.close();
    
    int quadkey; // variable to be used as key for quad function
    cout << "Enter a number between 1 and 450,000,000 for the offset key: ";
    cin >> quadkey;
    while (quadkey > 450000000 || quadkey < 1)
    {
        cout << "Number not in range." << endl;
        cout << "Enter a number between 1 and 450,000,000 for the key: ";
        cin >> quadkey;
    }
    
    int max; // int for the size of the hash table
    cout << "How big do you want the hash table to be: ";
    cin >> max;
    int Hashtable[max];
    for (int i = 0; i < max; i++) // add because my complier would create an array but it would not always be empty
    {
        Hashtable[i] = 0;
    }
    
    cout << "Let the hashing begin!" << endl;
    for (int i = 0; i < array_size; i++)
    {
        if (array_of_numbers[i] != 0)
        {
            quadProbe(Hashtable, array_of_numbers[i], max, quadkey);
        }
        else
            break;
    }
    
    writeHash(Hashtable, "test.txt", max);
}

int extraction (int s) // just adds on each int to the end of the string until the final is reached
{
    string i = to_string(s);
    string final;
    final = i[2];
    final = final + i[4];
    final = final + i[6];
    final = final + i[7];
    int fin = stoi(final); // convert string to int
    return fin;
}

int quadProbe (int hashtable[], int s, int max, int quadkey)
{
    int pos, i;
    pos = extraction(s); // get the position using extraction method
    if (hashtable[pos] == 0) // if the inital position is empty
    {
        hashtable[pos] = s;
        return pos;
    }
    else // if the inital position is not empty
    {
        for (i = quadkey; i%max != pos; i++)
        {
            pos = (pos + i * i) % max;
            if (hashtable[i] == 0)
            {
                hashtable[i] = s;
                return pos;
            }
        }
    }
    return -1; // the table is full
}

void writeHash (int hashtable[], string filepath, int max)
{
    ofstream out;
    out.open(filepath);
    for (int i = 0; i < max; i++)
        out << hashtable[i] << ","; // writes out the hash table in a comma separ
        //out << i << "\t" << hashtable[i] << endl; //for testing purposes only
        out.clear();
        out.close();
}