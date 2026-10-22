# Struct pointer

## 1. Definition - why use it 
- 2 Parts: struct - which means structure & pointer is just a pointer
    + So a struct pointer is a pointer that points to a structure and we can access variables inside that structure 

## 2. Struct - Structure & a bit of structure pointer
- a struct is what used to store variables of different types (related or not) under one structure name, usually called: User-defined data type
- the function is simple:
    Struct StructureName {
        Datatype Element1;
        Datatype Element2;
    }
- to access the variable of a structure you can use 2 methods 
    StructureName.ElementX   // Access through the structure variable
    pointerY->ElementX      // Access through a pointer to that structure

    Minh.Tuoi     // Minh is a structure variable
    p1->Tuoi      // p1 is a pointer to a structure, more info bellow 

    + Example
    ```c
    #include <stdio.h>

    struct Hoc_sinh {
        int Tuoi;
        char Truong_Dai_hoc[100]; //character array of 100 letters
    };
    int main(void){
        struct Hoc_sinh Minh = {20,"HUST"};
        struct Hoc_sinh Chi = {20,"NEU"};

        printf("Tuoi: %d\n", Minh.Tuoi);
        printf("Truong dai hoc: %s\n", Chi.Truong_Dai_hoc);
        return 0;
    }
    ```

    + if you want to use pointers, it would be like this 
    ```c
    #include <stdio.h>

    struct Hoc_sinh {
        int Tuoi;
        char Truong_Dai_hoc[100]; //character array of 100 letters
    };
    int main(void){
        struct Hoc_sinh Minh = {20,"HUST"};
        struct Hoc_sinh Chi = {20,"NEU"};

        struct Hoc_sinh *p1 = &Minh;
        struct Hoc_sinh *p2 = &Chi;

        printf("Tuoi: %d\n", p1->Tuoi);//ouput Minh's Tuoi
        printf("Truong dai hoc: %s\n", p2->Truong_Dai_hoc);//output Chi's uni 
        return 0;
    }

- A variable inside of a structure can be edit/update using a "struct pointer" which is similar to a normal pointer *p
    + it goes lie this
     ```c   void update(struct Hoc_sinh *p) // Datatype update(Struct StructureName *PointerName)
        {
        p->Tuoi = 25;// this part update the variable Tuoi to 25 at which ever address that the pointer p point to
    }

    int main(void) {
        struct Hoc_sinh Minh = {20, "HUST"};

        update(&Minh); // basically update(&ElementX), at address

        printf("Tuoi: %d\n", Minh.Tuoi);// the output will be 25, the original value changed from 20 ->25

        return 0;
    }

## 3. How it all works

- The process is:
1. At the structure Hoc_sinh: 
    Element1-Minh is created and initialized with age 20 and uni "HUST". 

2. &Minh is the address of Minh.

3. p1 stores that address.

4. p1->Tuoi follows the pointer to Minh and accesses its Tuoi Element.
5. printf p1->Tuoi The program prints 20 which is the value of tuoi

- the process is very simple and straight forward


- For the update() Function, the program follow the pointer p1 -> Tuoi to alter the value store there (at &Minh)

    + p1 points to Element Minh of the structure Hoc_sinh and the pointer follow the &Minh and can access the variable Tuoi and Truong_Dai_Hoc to edit them
    
    ```c
    struct Hoc_sinh Minh = {20, "HUST"};    //Creates the original structure

    update(&Minh);   //Passes the address of Minh

    struct Hoc_sinh *p;     //The local pointer p receives that address

    p->Tuoi = 25;    //Modifies Minh.Tuoi directly