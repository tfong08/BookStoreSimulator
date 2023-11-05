//
//  Class: CMSC226
//  Instructor: Pingwei Tsai
//
//  Created by Tyler Fong on 9/15/23.
//


#include <iostream>
#include <iomanip>
#include <map>
#include <cstring>
#include "mainmenu.h"

using namespace std;

struct BookData{
    char bookTitle[51];
    char isbn[14];
    char author[31];
    char publisher[31];
    char dateAdded[11];
    int qtyOnHand;
    double wholesale;
    double retail;
};

//global arrays to store book inventory information
char bookTitleInv[20][51];
char isbnInv[20][14];
char authorInv[20][31];
char publisherInv[20][31];
char dateAdded[20][11];
int qtyOnHand[20];
double wholesale[20];
double retail[20];
BookData bookInv[20];

int main(){
    
    //main menu of serendipity booksellers
    cout << "Serendipity Booksellers" << endl;
    cout << "\tMain Menu\n\n";
    cout << "1. Cashier Module" << endl;
    cout << "2. Inventory Database Module" << endl;
    cout << "3. Report Module" << endl;
    cout << "4. Exit\n" << endl;
    cout << "Enter Your Choice: ";
    
    int choice;
    cin >> choice;
    
    //verify correct user input
    while (choice < 1 || choice > 4) {
        cout << "\nPlease Enter the number in the range 1 - 4 \n" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    }
    
    //forwards to correct method based on choice
    switch(choice){
        case 1:
            cashier();
        case 2:
            invMenu();
        case 3:
            reports();
        case 4:
            exit(0);
    }
    return 0;
}


void cashier(){
    
    const double SALES_TAX = .06;
    char repeatTransaction = 'y';
    
    //loop cashier if customer wants to repeat transaction
    while(repeatTransaction == 'y'){
        char more = 'y';
        double sumSubtotal=0;
        double tax;
        double total;
        string date;
        string ISBN;
        vector<string> ISBNs;
        string title;
        vector<string> titles;
        int quant;
        vector<int> quants;
        vector<double> prices;
        vector<double> subtotals;
        int numBooks=0;
        
        //prompt user input for date of transaction
        cout << "Serendipity Booksellers\n" << endl;
        cout << "Enter Date: ";
        cin.ignore();
        getline(cin, date);
        while(more == 'y'){
            //ask user how many books they want to checkout
            cout << "Enter Quantity: ";
            cin >> quant;
            
            char repeatISBN='y';
            int ind;
            
            //loop to accept valid ISBN
            while(repeatISBN=='y'){
                cin.ignore();
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                ind = 0;
                while(isbnInv[ind]!=ISBN&&ind<20){
                    ind++;
                }
                if(ind==20){
                    cout << "Invalid ISBN. Would you like to re-enter the ISBN? (y/n)";
                    cin >> repeatISBN;
                }else{
                    repeatISBN='n';
                }
            }
            
            //return to main if no valid ISBN is inputted
            if(ind==20){
                main();
            }
            
            //check if quantity on hand is sufficient
            if(qtyOnHand[ind]<quant){
                if(numBooks>0){
                    cout << "Insufficient quantity of books available, checking out previous books" << endl;
                }else{
                    cout << "Insufficient quantity of books available." << endl;
                }
                more='n';
            }else{
                
                //adds information of requested book to checkout to checkout information vectors
                quants.push_back(quant);
                //removes correct amount of books from inventory to complete transaction
                qtyOnHand[ind]-=quant;
                ISBNs.push_back(ISBN);
                titles.push_back(bookTitleInv[ind]);
                prices.push_back(retail[ind]);
                
                cout << "Are you purchasing any more books? (y/n)";
                cin >> more;
                numBooks++;
            }
        }
        
        //calculate subtotal and total of transaction
        for(int i=0;i<numBooks;i++){
            subtotals.push_back(quants[i]*prices[i]);
            sumSubtotal+=subtotals[i];
        }
        
        tax = sumSubtotal*SALES_TAX;
        total = sumSubtotal+tax;
        
        //output cashier screen showing book information and amount for transaction
        if(numBooks>0){
            cout << "\n" << date << ":\n" << endl;
            cout << setw(4) << left << "Qty" << setw(16) << left << "ISBN" << setw(24) << left << "Title" << setw(12) << left << "Price" << setw(7) << left << "Total" << endl;
            cout << "_______________________________________________________________" << endl;
            for(int i=0;i<numBooks;i++){
                cout << fixed << showpoint << setprecision(2) << left;
                cout << setw(4) << left << quants[i] << setw(16) << left << ISBNs[i] << setw(24)<< left << titles[i] << "$" << setw(6) << right << prices[i] << setw(6) << right << "$" << setw(6) << right << subtotals[i] << endl;
            }
            cout << "\n\n";
            cout << setw(12) << "" << "Subtotal" << setw(37) << right << "$" << setw(6) << right << sumSubtotal << endl;
            cout << setw(12) << "" << "Tax" << setw(42) << right << "$" << setw(6) << right << tax << endl;
            cout << setw(12) << "" << "Total" << setw(40) << right << "$" << setw(6) << right << total << endl;
            cout << "\nThank You for Shopping at Serendipity" << endl;
            cout << "Do you want to repeat another transaction? (y/n) ";
            cin >> repeatTransaction;
            cout << "\n";
        }else{
            main();
        }
    }
    main();
}

void invMenu(){
    bool returnMain = false;
    //inventory menu screen
    while(!returnMain){
        cout << "Serendipity Booksellers" << endl;
        cout << "Inventory Database\n" << endl;
        cout << "1. Look Up a Book" << endl;
        cout << "2. Add a Book" << endl;
        cout << "3. Edit a Book's Record" << endl;
        cout << "4. Delete a Book" << endl;
        cout << "5. Return to the Main Menu\n" << endl;
        cout << "Enter Your Choice: ";
        
        int choice;
        cin >> choice;
        
        //verify correct user input
        while (choice < 1 || choice > 5) {
            cout << "\nPlease Enter the number in the range 1 - 5 \n" << endl;
            cout << "Enter your choice: " ;
            cin >> choice;
        }
        
        //forwards to correct method depending on user input
        switch(choice){
            case 1:
                lookUpBook();
            case 2:
                addBook();
            case 3:
                editBook();
            case 4:
                deleteBook();
            case 5:
                main();
        }
    }
}

void lookUpBook(){
    char lookTitle[51];
    cin.ignore();
    //prompt user for title of book to lookup
    cout << "Title of book: ";
    cin.getline(lookTitle,51);
    strUpper(lookTitle);
    bool found=false;
    int lookInd=0;
    char yn;
    //find index the book information of requested book is stored at
    for(int i=0;i<20;i++){
        if(strstr(bookTitleInv[i],lookTitle)){
            cout << "\nPossible Match: " << bookTitleInv[i] << endl;
            cout << "Is this the correct book? (y/n)";
            cin >> yn;
            //verify correct input
            while(!(yn=='Y'||yn=='y'||yn=='N'||yn=='n')){
                cout << "Please enter a valid input: ";
                cin >> yn;
            }
            //output book informatio
            if(yn == 'Y' || yn == 'y'){
                bookInfo(isbnInv[i], bookTitleInv[i], authorInv[i], publisherInv[i], dateAdded[i], qtyOnHand[i], wholesale[i], retail[i]);
                cout << "\n";
                invMenu();
            }
        }
    }
    
    cout << "Book is not in inventory." << endl;
    cout << "\n";
    invMenu();
}

void addBook(){
    int i=0;
    
    //check for next open index to add book information or if inventory is full
    while(bookTitleInv[i][0]!='\0'){
        i++;
        if(i==20){
            cout << "No more books may be added to the inventory.";
            invMenu();
        }
    }
    
    //prompt user for book information to add to inventory
    cin.ignore();
    cout << "Book Title: ";
    char bookTitle[51];
    cin.getline(bookTitle,51);
    strUpper(bookTitle);
    setTitle(bookTitle,i);
    
    cout << "ISBN: ";
    cin.getline(isbnInv[i],14);
    strUpper(isbnInv[i]);
    
    cout << "Author: ";
    cin.getline(authorInv[i],31);
    strUpper(authorInv[i]);
    
    cout << "Publisher: ";
    cin.getline(publisherInv[i],31);
    strUpper(publisherInv[i]);
    
    cout << "Date (YYYY-MM-DD): ";
    cin.getline(dateAdded[i],11);
    strUpper(dateAdded[i]);
    
    cout << "Quantity: ";
    cin >> qtyOnHand[i];
    
    cout << "Wholesale Cost: ";
    cin >> wholesale[i];
    
    cout << "Retail Price: ";
    cin >> retail[i];
    
    invMenu();
}

void editBook(){
    char lookTitle[51];
    cin.ignore();
    //prompt user for title of book to lookup
    cout << "Title of book to edit: ";
    cin.getline(lookTitle,51);
    strUpper(lookTitle);
    bool found=false;
    int lookInd=0;
    char yn;
    //find index the book information of requested book is stored at
    for(int i=0;i<20;i++){
        if(strstr(bookTitleInv[i],lookTitle)){
            cout << "\nPossible Match: " << bookTitleInv[i] << endl;
            cout << "Is this the correct book? (y/n)";
            cin >> yn;
            //verify correct input
            while(!(yn=='Y'||yn=='y'||yn=='N'||yn=='n')){
                cout << "Please enter a valid input: ";
            }
            if(yn=='Y'||yn=='y'){
                //outputs current book information
                bookInfo(isbnInv[lookInd], bookTitleInv[lookInd], authorInv[lookInd], publisherInv[lookInd], dateAdded[lookInd], qtyOnHand[lookInd], wholesale[lookInd], retail[lookInd]);
                //asks user to choose what information to edit
                cout << "\nWhich of the following would you like to edit?" << endl;
                cout << "1. ISBN" << endl;
                cout << "2. Title" << endl;
                cout << "3. Author" << endl;
                cout << "4. Publisher" << endl;
                cout << "5. Date Added" << endl;
                cout << "6. Quantity-On-Hand" << endl;
                cout << "7. Wholesale Cost" << endl;
                cout << "8. Retail Price" << endl;
                int choice;
                cin >> choice;
                while (choice < 1 || choice > 8) {
                    cout << "\nPlease Enter the number in the range 1 - 8 \n" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                }
                //allows user to change informtion based on decision
                switch (choice){
                    case 1:
                        cin.ignore();
                        cout << "ISBN: ";
                        cin.getline(isbnInv[lookInd],14);
                        strUpper(isbnInv[lookInd]);
                        break;
                    case 2:
                        cin.ignore();
                        cout << "Title: ";
                        cin.getline(bookTitleInv[lookInd],51);
                        strUpper(bookTitleInv[lookInd]);
                        break;
                    case 3:
                        cin.ignore();
                        cout << "Author: ";
                        cin.getline(authorInv[lookInd],31);
                        strUpper(authorInv[lookInd]);
                        break;
                    case 4:
                        cin.ignore();
                        cout << "Publisher: ";
                        cin.getline(publisherInv[lookInd],31);
                        strUpper(publisherInv[lookInd]);
                        break;
                    case 5:
                        cin.ignore();
                        cout << "Date Added: ";
                        cin.getline(dateAdded[lookInd],11);
                        break;
                    case 6:
                        cout << "Quantity-On-Hand: ";
                        cin >> qtyOnHand[lookInd];
                        break;
                    case 7:
                        cout << "Wholesale Cost: ";
                        cin >> wholesale[lookInd];
                        break;
                    case 8:
                        cout << "Retail Price: ";
                        cin >> retail[lookInd];
                }
                cout << "\n";
                invMenu();
            }
        }
    }

    cout << "Book is not in inventory." << endl;
    
    cout << "\n";
    invMenu();
}

void deleteBook(){
    char lookTitle[51];
    cin.ignore();
    //prompt user for title of book to lookup
    cout << "Title of book to edit: ";
    cin.getline(lookTitle,51);
    strUpper(lookTitle);
    bool found=false;
    int lookInd=0;
    char yn;
    //find index the book information of requested book is stored at
    for(int i=0;i<20;i++){
        if(strstr(bookTitleInv[i],lookTitle)){
            cout << "\nPossible Match: " << bookTitleInv[i] << endl;
            cout << "Is this the correct book? (y/n)";
            cin >> yn;
            //verify correct input
            while(!(yn=='Y'||yn=='y'||yn=='N'||yn=='n')){
                cout << "Please enter a valid input: ";
            }
            if(yn=='Y'||yn=='y'){
                
                //show corresponding book information
                bookInfo(isbnInv[lookInd], bookTitleInv[lookInd], authorInv[lookInd], publisherInv[lookInd], dateAdded[lookInd], qtyOnHand[lookInd], wholesale[lookInd], retail[lookInd]);
                
                //verify user wants to delete book
                cout << "Are you sure you want to delete this book? (y/n)" << endl;
                cin >> yn;
                while(!(yn=='Y'||yn=='y'||yn=='N'||yn=='n')){
                    cout << "Please enter a valid input: ";
                }
                if(yn=='Y'||yn=='y'){
                    //set book information to null/default values
                    isbnInv[lookInd][0]='\0';
                    bookTitleInv[lookInd][0]='\0';
                    qtyOnHand[lookInd]=0;
                    retail[lookInd]=0;
                    wholesale[lookInd]=0;
                }
            }
        }
    }
    cout << "\n";
    invMenu();
}

void bookInfo(string isbn, string title, string author, string publisher, string date, int qty, double wholesale, double retail){
    //output book information to screen
    cout << "\t\tSerendipity Booksellers" << endl;
    cout << "\t\t\tBook Information\n" << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date Added: " << date << endl;
    cout << "Quantity-On-Hand: " << qty << endl;
    cout << "Wholesale Cost: " << wholesale << endl;
    cout << "Retail Price: " << retail << endl;
}

void reports(){
    bool returnMain = false;
    
    //shows reports screen list
    while(!returnMain){
        cout << "\tSerendipity Booksellers" << endl;
        cout << "\t\t\tReports\n" << endl;
        cout << "1. Inventory Listing" << endl;
        cout << "2. Inventory Wholesale Value" << endl;
        cout << "3. Inventory Retail Value" << endl;
        cout << "4. Listing by Quantity" << endl;
        cout << "5. Listing by Cost" << endl;
        cout << "6. Listing by Age" << endl;
        cout << "7. Return to Main Menu\n" << endl;
        cout << "Enter Your Choice: ";
        
        int choice;
        cin >> choice;
        
        //verify correct user input
        while (choice < 1 || choice > 7) {
            cout << "\nPlease Enter the number in the range 1 - 7 \n" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }
        
        //forwards user to correct method based on input
        switch (choice){
            case 1:
                repListing();
                break;
            case 2:
                repWholesale();
                break;
            case 3:
                repRetail();
                break;
            case 4:
                repQty();
                break;
            case 5:
                repCost();
                break;
            case 6:
                repAge();
                break;
            case 7:
                main();
                break;
        }
    }
}

void repListing(){
    string date;
    
    //prompt user input for date of this report
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    int i=0;
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\t\tInventory Report\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    
    //print all book info for each book in inventory
    while(bookTitleInv[i][0]!='\0'){
        cout << "ISBN: " << isbnInv[i] << endl;
        cout << "Title: " << bookTitleInv[i] << endl;
        cout << "Author: " << authorInv[i] << endl;
        cout << "Publisher: " << publisherInv[i] << endl;
        cout << "Date Added: " << dateAdded[i] << endl;
        cout << "Quantity-On-Hand: " << qtyOnHand[i] << endl;
        cout << "Wholesale Cost: " << wholesale[i] << endl;
        cout << "Retail Price: " << retail[i] << endl;
        cout << "\n";
        i++;
    }
    
    //pause the screen before moving on
    cout << "Press Enter to Continue";
    cin.ignore();
    reports();
}

void repWholesale(){
    string date;
    
    //prompt user input for date of report
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    int i=0;
    double total = 0;
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\tInventory Wholesale Value\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    
    //print out report with title, isbn, quantity, and wholesale value of each item
    while(bookTitleInv[i][0]!='\0'){
        cout << fixed << showpoint << setprecision(2) << left;
        cout << setw(15) << left << bookTitleInv[i] << setw(16) << left << isbnInv[i] << setw(5)<< left << qtyOnHand[i] << "$" << setw(6) << right << wholesale[i] << endl;
        //calculate total wholesale value of books in inventory
        total+=wholesale[i]*qtyOnHand[i];
        i++;
    }
    cout << setw(36) << left << "\nTotal Wholesale Value: " << "$ " << total << endl;
    
    //pause the screen
    cout << "\nPress Enter to Continue";
    cin.ignore();
    reports();
}

void repRetail(){
    string date;
    
    //prompt user input for date of report
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    int i=0;
    double total = 0;
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\tInventory Retail Value\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    
    //print table with title, isbn, quantity, and retail value of all books in inventory
    while(bookTitleInv[i][0]!='\0'){
        cout << fixed << showpoint << setprecision(2) << left;
        cout << setw(15) << left << bookTitleInv[i] << setw(16) << left << isbnInv[i] << setw(5)<< left << qtyOnHand[i] << "$" << setw(6) << right << retail[i] << endl;
        
        //calculate the total retail value of books in inventory
        total+=retail[i]*qtyOnHand[i];
        i++;
    }
    cout << setw(36) << left << "\nTotal Retail Value: " << "$ " << total << endl;
    
    //pause the screen
    cout << "\nPress Enter to Continue";
    cin.ignore();
    reports();
}

void repQty(){
    vector<int> sortedIndices;
    vector<int> sortedQty;
    
    //loop through array containing quantities to create a sorted array with corresponding indices
    for(int i=0;i<20;i++){
        
        //skip if no value
        if(qtyOnHand[i]==0){
            continue;
        }else{
            
            //add the first element to the sorted vectors
            if(sortedQty.size()==0){
                sortedQty.push_back(qtyOnHand[i]);
                sortedIndices.push_back(i);
            }else{
                bool inserted = false;
                
                //loop through sorted array to see where to insert next quantity
                for(int j=0;j<sortedQty.size();j++){
                    
                    //insert quantity before the first value it finds that is less than it (create descending order vector)
                    if(qtyOnHand[i]>sortedQty[j]){
                        sortedQty.insert(sortedQty.begin()+j, qtyOnHand[i]);
                        sortedIndices.insert(sortedIndices.begin()+j,i);
                        inserted = true;
                        break;
                    }
                }
                
                //if value not found, then it's the smallest value so push to back of vector
                if(inserted==false){
                    sortedQty.push_back(qtyOnHand[i]);
                    sortedIndices.push_back(i);
                }
            }
        }
    }
    
    //prompt user input for date of report
    string date;
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\tInventory Quantity\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    cout << setw(15) << left << "Title" << setw(16) << left << "ISBN" << setw(5)<< left << "Qty" << endl;
    cout << "____________________________________" << endl;
    
    //loop through array of sorted indices based on quanity to output book information in the correct order
    for(int i:sortedIndices){
        cout << fixed << showpoint << setprecision(2) << left;
        cout << setw(15) << left << bookTitleInv[i] << setw(16) << left << isbnInv[i] << setw(5)<< left << qtyOnHand[i] << endl;
    }
    
    //pause screen
    cout << "\nPress Enter to Continue";
    cin.ignore();
    reports();

}

void repCost(){
    vector<int> sortedIndices;
    vector<double> sortedCost;
    
    
    //loop through array containing wholesale value to create a sorted array with corresponding indices
    for(int i=0;i<20;i++){
        
        //skip values if 0
        if(wholesale[i]==0){
            continue;
        }else{
            
            //add first wholesale value to sorted array
            if(sortedCost.size()==0){
                sortedCost.push_back(wholesale[i]);
                sortedIndices.push_back(i);
            }else{
                bool inserted = false;
                
                //loop through sorted array to determine where to insert next element (wholesale value)
                for(int j=0;j<sortedCost.size();j++){
                    
                    //insert element before the first value it finds that is less than it (create descending order vector)
                    if(wholesale[i]>sortedCost[j]){
                        sortedCost.insert(sortedCost.begin()+j, wholesale[i]);
                        sortedIndices.insert(sortedIndices.begin()+j,i);
                        inserted = true;
                        break;
                    }
                }
                
                //insert element to end of vector if smaller than all current values in sorted array
                if(inserted==false){
                    sortedCost.push_back(wholesale[i]);
                    sortedIndices.push_back(i);
                }
            }
        }
    }
    
    //prompt user input for date of report
    string date;
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\tInventory Quantity\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    cout << setw(15) << left << "Title" << setw(16) << left << "ISBN" << setw(5)<< left << "Qty" << setw(7) << right << "Cost" << endl;
    cout << "___________________________________________" << endl;
    
    //create table of book information sorted from highest to lowest unit cost
    for(int i:sortedIndices){
        cout << fixed << showpoint << setprecision(2) << left;
        cout << setw(15) << left << bookTitleInv[i] << setw(16) << left << isbnInv[i] << setw(5)<< left << qtyOnHand[i] << "$" << setw(6) << right << wholesale[i] << endl;
    }
    
    //pause screen
    cout << "\nPress Enter to Continue";
    cin.ignore();
    reports();
}

void repAge(){
    vector<int> sortedIndices;
    vector<string> sortedAge;
    
    //loop through date added array
    for(int i=0;i<20;i++){
        //skip null/default values
        if(dateAdded[i][0]=='\0'){
            continue;
        }else{
            //add date element to sorted array
            if(sortedAge.size()==0){
                sortedAge.push_back(dateAdded[i]);
                sortedIndices.push_back(i);
            }else{
                bool inserted = false;
                //loop through sorted array to determine where to insert next date element
                for(int j=0;j<sortedAge.size();j++){
                    //insert date element in front of the first element that is smaller than it (descending order vector)
                    if(dateAdded[i]>sortedAge[j]){
                        sortedAge.insert(sortedAge.begin()+j, dateAdded[i]);
                        sortedIndices.insert(sortedIndices.begin()+j,i);
                        inserted = true;
                        break;
                    }
                }
                //push element to end if date is the oldest
                if(inserted==false){
                    sortedAge.push_back(dateAdded[i]);
                    sortedIndices.push_back(i);
                }
            }
        }
    }
    
    //prompt user for date of report
    string date;
    cout << "\nEnter today's date:";
    cin.ignore();
    getline(cin,date);
    cout << "\n\t\tSerendipity Booksellers" << endl;
    cout << "\t\tInventory Quantity\n" << endl;
    cout << "Date: " << date << "\n" << endl;
    cout << setw(15) << left << "Title" << setw(16) << left << "ISBN" << setw(5)<< left << "Qty" << setw(15) << right << "Date Added" << endl;
    cout << "___________________________________________________" << endl;
    //loop through vector of sorted indices to output book information sorted by date
    for(int i:sortedIndices){
        cout << fixed << showpoint << setprecision(2) << left;
        cout << setw(15) << left << bookTitleInv[i] << setw(16) << left << isbnInv[i] << setw(5)<< left << qtyOnHand[i] << setw(15) << right << dateAdded[i] << endl;
    }
    
    //pause screen
    cout << "\nPress Enter to Continue";
    cin.ignore();
    reports();
    
}

void strUpper(char* strPt){
    if(strPt == nullptr){
        return;
    }
    //change character to uppercase and point to next character in string
    while (*strPt!='\0') {
        *strPt = toupper(*strPt);
        strPt++;
    }
}

void strUpper(char* strPt){
    if(strPt == nullptr){
        return;
    }
    //change character to uppercase and point to next character in string
    while (*strPt!='\0') {
        *strPt = toupper(*strPt);
        strPt++;
    }
}

void setTitle(char* titlePt,int bookInd){
    strUpper(titlePt);
    strcpy(bookInv[bookInd].bookTitle, titlePt);
}
void setISBN(char* isbnPt,int bookInd){
    strcpy(bookInv[bookInd].isbn, isbnPt);
}
void setAuthor(char* authPt,int bookInd){
    strUpper(authPt);
    strcpy(bookInv[bookInd].bookTitle, authPt);
}
void setPub(char* pubPt,int bookInd){
    strUpper(pubPt);
    strcpy(bookInv[bookInd].bookTitle, pubPt);
}
void setDateAdded(char* datePt,int bookInd){
    strUpper(datePt);
    strcpy(bookInv[bookInd].bookTitle, datePt);
}
void setQty(int qty,int bookInd){
    bookInv[bookInd].qtyOnHand = qty;
}
void setWholesale(double whole,int bookInd){
    bookInv[bookInd].wholesale = whole;
}
void setRetail(double retail,int bookInd){
    bookInv[bookInd].retail = retail;
}
int isEmpty(int bookInd){
    if(bookInv[bookInd].bookTitle[0] == '\0'){
        return 1;
    }else{
        return 0;
    }
}
void removeBook(int bookInd){
    bookInv[bookInd].bookTitle[0] = '\0';
}



