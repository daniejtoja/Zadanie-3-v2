//
//  main.cpp
//  Zadanie 3 v2
//
//  Created by Daniel on 01/01/2020.
//  Copyright © 2020 Daniel Rumin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int numberOfpeople = 0;

struct birthDate {
    int day;
    int month;
    int year;
};

struct Person {
    string surname;
};

struct node {
    Person student;
    birthDate date;
    node * next_byAge;
    node * next_byAlph;
};

node* NewlyCreated;
node* head_byAge;
node* head_byAlph;
node* tail_byAge;
node* tail_byAlph;

bool loadPpl(string fileName){
    fstream listFile;
    listFile.open(fileName);
    
    if (!listFile.is_open()) {
        cout << "Error. Nie udało się otworzyć pliku.";
        return false;
    }
    
    string line_to_count;
    int number_of_lines = 0;
    int number_of_persons = 0;
    
    while (getline(listFile, line_to_count)) {
        ++number_of_lines;
    }
    
    if (number_of_lines%4 != 0) {
        cout << "Niepełne dane.";
        return false;
    } else {
        number_of_persons = number_of_lines / 4;
        cout << "Linijki w pliku: " << number_of_lines << endl;
        cout << "Liczba osób: " << number_of_persons << endl;
    }
    
    numberOfpeople = number_of_persons;
    
    listFile.clear();               //wracamy do
    listFile.seekg(0, ios::beg);    //początku pliku
    
    
    string line;
    
    for (int i = 0; i < number_of_persons; ++i) {

       
        if (i == 0) {
            NewlyCreated = new node;
            head_byAge = NewlyCreated;
            tail_byAge = NewlyCreated;
            head_byAlph = NewlyCreated;
            tail_byAlph = NewlyCreated;
        }
        
        for (int i = 0; i < 4 && getline(listFile, line); ++i) {
            if (i == 0) {
                NewlyCreated->student.surname = line;
            }
            
            if (i == 1) {
                NewlyCreated->date.day = stoi(line);        //
            }                                               //Stoi pozwala przekształcić string na
                                                            //na wartość
            if (i == 2) {                                   //
                NewlyCreated->date.month = stoi(line);      //
            }                                               //
                                                            //
            if (i == 3) {                                   //
                NewlyCreated->date.year = stoi(line);       //
            }
        }
        
        if (i != (number_of_persons-1)) {
            NewlyCreated = new node;
            tail_byAge->next_byAge = NewlyCreated;
            tail_byAge = NewlyCreated;
            tail_byAlph->next_byAlph = NewlyCreated;
            tail_byAlph = NewlyCreated;
        } else {
            tail_byAge->next_byAge = NULL;
            tail_byAlph->next_byAlph = NULL;
        }
        
    }
    
    return true;
    
}



struct node* swap_byAlph(node* ptr1, node* ptr2)
{
    node* tmp = ptr2->next_byAlph;
    ptr2->next_byAlph = ptr1;
    ptr1->next_byAlph = tmp;
    return ptr2;
}

struct node* swap_byAge(node* ptr1, node* ptr2)
{
    node* tmp = ptr2->next_byAge;
    ptr2->next_byAge = ptr1;
    ptr1->next_byAge = tmp;
    return ptr2;
}

void bubbleSort_byAlph(node** head, int people)
{
    struct node** temp;
    int i, j, swapped;
  
    for (i = 0; i <= people; i++) {
  
        temp = head;
        swapped = 0;
  
        for (j = 0; j < people - i - 1; j++) {
  
            struct node* p1 = *temp;
            struct node* p2 = p1->next_byAlph;
  
            if (p1->student.surname.compare(p2->student.surname) > 0) {
                *temp = swap_byAlph(p1, p2);
                swapped = 1;
            }
  
            temp = &(*temp)->next_byAlph;
        }
  
        if (swapped == 0)
            break;
    }
}


void bubbleSort_byAge(node** head, int people){
                struct node** temp;
                int i, j, swapped;
              
                for (i = 0; i <= people; i++) {
              
                    temp = head;
                    swapped = 0;
              
                    for (j = 0; j < people - i - 1; j++) {
              
                        struct node* p1 = *temp;
                        struct node* p2 = p1->next_byAge;
              
                        if (p1->date.year > p2->date.year) {
                            
                            *temp = swap_byAge(p1, p2);
                            swapped = 1;
                            
                        } else if (p1->date.year == p2->date.year){
                            
                            if (p1->date.month > p2->date.month) {
                                
                                *temp = swap_byAge(p1, p2);
                                swapped = 1;
                                
                            } else if (p1->date.month == p2->date.month){
                                
                                if (p1->date.day > p2->date.day) {
                                    
                                    *temp = swap_byAge(p1, p2);
                                    swapped = 1;
                                    
                                }
                            }
                        }
              
                        temp = &(*temp)->next_byAge;
                    }
              
                    if (swapped == 0)
                        break;
                }
}

                





void displayByAge(node * head){
    
    node* displayPerson;
    displayPerson = head;
    
    while (displayPerson != NULL) {
        cout << displayPerson->student.surname << endl;
        cout << displayPerson->date.day << "/" << displayPerson->date.month << "/" << displayPerson->date.year << endl << endl;
        
        displayPerson = displayPerson->next_byAge;
    }
}

void displayByAlph(node * head){
    
    node* pokazOsobe;
    pokazOsobe = head;
    
    while (pokazOsobe != NULL) {
        cout << pokazOsobe->student.surname << endl;
        cout << pokazOsobe->date.day << "/" << pokazOsobe->date.month << "/" << pokazOsobe->date.year << endl << endl;
        
        pokazOsobe = pokazOsobe->next_byAlph;
    }
}

    
    




int main() {
    
    string plik;
    cout << "Podaj nazwę pliku (włącznie z rozszerzeniem): ";
    cin >> plik;
    
    loadPpl(plik);
    
    cout << endl << endl;
    
    bubbleSort_byAlph(&head_byAlph, numberOfpeople);
    bubbleSort_byAge(&head_byAge, numberOfpeople);
    
    int opcja;
    cout << "Wyświetl listę posortowaną w sposób: 1 - alfabetyczny, 2 - wiek malejąco, 3 - oba sposoby: ";
    cin >> opcja;
    
    switch (opcja) {
        case 1:
            cout << endl;
            displayByAlph(head_byAlph);
            break;
            
        case 2:
            cout << endl;
            displayByAge(head_byAge);
            break;
            
        case 3:
            cout << endl;
            displayByAlph(head_byAlph);
            cout << endl;
            displayByAge(head_byAge);
            break;
            
        default:
            cout << "Zły numer funkcji." << endl;
            break;
    }
    
    return 0;
    
}
                
